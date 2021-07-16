import naming_gen as name_gen


def get_variableDeclarationr(signals, msg_dataframe, interface, suffix):
    body = ''
    ##variable declaration
    for idx in range(len(signals['Name'].index)):        
        if(signals['Type'][idx] == 'signal'):
            body = body + ( name_gen.get_datatype(signals['Value Type'][idx], signals['Length [Bit]'][idx]) +  ' ' + signals['Message'][idx] + signals['Name'][idx] + '_' +  suffix + ';\n')
    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):
            body = body + name_gen.get_datatype('allow_tx', '1') + ' ' + name_gen.get_AllowTxVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'#name_gen.get_datatype('Unsigned', '1') + ' ' +  msg_dataframe['Name'][msg_idx] +  '_' +  'AllowTx' + '_' + suffix + ';\n'
            #body = body + name_gen.get_datatype('Unsigned', 1) + ' ' +  msg_dataframe['Name'][msg_idx] +  '_' +  suffix + ';\n')
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):            
            body = body +  name_gen.get_datatype('checksum_check', '0') + ' ' + name_gen.get_CrcVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'#name_gen.get_datatype('rolling_counter', '0') +  ' ' + msg_dataframe['Name'][msg_idx] + '_' +  'RollCounter' + '_' + suffix + ';\n'
            body = body +  name_gen.get_datatype('rolling_counter_check', '0') + ' ' + name_gen.get_RollCountVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'#name_gen.get_datatype('rolling_counter', '0') +  ' ' + msg_dataframe['Name'][msg_idx] + '_' +  'TimeOut' + '_' +suffix + ';\n'
            body = body +  name_gen.get_datatype('Unsigned', '1') + ' ' + name_gen.get_TimeOutVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'
            
    return body    

def get_RteFn(signals, msg_dataframe, interface, suffix):
    body = ''    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        for sig_idx in range(len(signals['Name'].index)):
            ##read fn1
            if(signals['Message'][sig_idx] == msg_dataframe['Name'][msg_idx]):
                if(signals['Type'][sig_idx] == 'signal'):
                    body = body + name_gen.get_datatype(signals['Value Type'][sig_idx], signals['Length [Bit]'][sig_idx]) + ' ' + name_gen.get_rteReadFn(msg_dataframe['Name'][msg_idx], signals['Name'][sig_idx], suffix) + '(void) {\n'
                    body = body + '    return ' +  signals['Message'][sig_idx] + signals['Name'][sig_idx] + '_' +  suffix + ';\n'
                    body = body + '}\n'
                    body = body + 'void ' + name_gen.get_rteWriteFn(msg_dataframe['Name'][msg_idx], signals['Name'][sig_idx], suffix) + '(' + name_gen.get_datatype(signals['Value Type'][sig_idx], signals['Length [Bit]'][sig_idx]) + ' value) {\n'
                    body = body + '    ' +  ' ' + signals['Message'][sig_idx] + signals['Name'][sig_idx] + '_' +  suffix + ' = value;\n'
                    body = body + '}\n'    

        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):
            ##AllowTx rte read
            body = body + name_gen.get_datatype('allow_tx', signals['Length [Bit]'][sig_idx]) + ' ' + name_gen.get_rteAllowTxReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void) {\n'
            body = body + '    return ' +   name_gen.get_AllowTxVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'
            body = body + '}\n'
            ##AllowTx rte write
            body = body +  'void ' + name_gen.get_rteAllowTxWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('allow_tx', signals['Length [Bit]'][sig_idx]) +' value) {\n'
            body = body + '    '+ name_gen.get_AllowTxVariableName(msg_dataframe['Name'][msg_idx], suffix) + ' = value;\n'
            body = body + '}\n'
            
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):
            ## Time out rte read
            body = body + name_gen.get_datatype('Unsigned', 1) + ' ' + name_gen.get_rteTimeOutReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void) {\n'
            body = body + '    return ' +  name_gen.get_TimeOutVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'
            body = body + '}\n'
            
            ## Time out rte write
            body = body +  'void ' + name_gen.get_rteTimeOutWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('Unsigned', 1) +' value) {\n'
            body = body + '    '+ name_gen.get_TimeOutVariableName(msg_dataframe['Name'][msg_idx], suffix) + ' = value;\n'
            body = body + '}\n'
            
            ## Crc rte read
            body = body + name_gen.get_datatype('checksum_check', 0) + ' ' + name_gen.get_rteCrcReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void) {\n'
            body = body + '    return ' +  name_gen.get_CrcVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'
            body = body + '}\n'
            
            ## Crc rte write
            body = body +  'void ' + name_gen.get_rteCrcWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('checksum_check', 0) +' value) {\n'
            body = body + '    '+ name_gen.get_CrcVariableName(msg_dataframe['Name'][msg_idx], suffix) + ' = value;\n'
            body = body + '}\n'
            
            ## rolling counter rte read
            body = body + name_gen.get_datatype('rolling_counter_check', 8) + ' ' + name_gen.get_rteRollCounterReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void) {\n'
            body = body + '    return ' +  name_gen.get_RollCountVariableName(msg_dataframe['Name'][msg_idx], suffix) + ';\n'
            body = body + '}\n'
            
            ## rolling counter rte write
            body = body +  'void ' + name_gen.get_rteRollCounterWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('rolling_counter_check', 8) +' value) {\n'
            body = body + '    '+ name_gen.get_RollCountVariableName(msg_dataframe['Name'][msg_idx], suffix) + ' = value;\n'
            body = body + '}\n'
            
    return body

def getRteProtos(signals, msg_dataframe, interface, suffix):
    body = ''
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        for sig_idx in range(len(signals['Name'].index)):
            ##read fn1
            if(signals['Message'][sig_idx] == msg_dataframe['Name'][msg_idx]):
                if(signals['Type'][sig_idx] == 'signal'):
                    body = body + name_gen.get_datatype(signals['Value Type'][sig_idx], signals['Length [Bit]'][sig_idx]) + ' ' + name_gen.get_rteReadFn(msg_dataframe['Name'][msg_idx], signals['Name'][sig_idx], suffix) + '(void);\n'
                    body = body + 'void ' + name_gen.get_rteWriteFn(msg_dataframe['Name'][msg_idx], signals['Name'][sig_idx], suffix) + '(' + name_gen.get_datatype(signals['Value Type'][sig_idx], signals['Length [Bit]'][sig_idx]) + ' value);\n'
    
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):
            ##AllowTx rte read
            body = body + name_gen.get_datatype('allow_tx', signals['Length [Bit]'][sig_idx]) + ' ' + name_gen.get_rteAllowTxReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void);\n'

            ##AllowTx rte write
            body = body +  'void ' + name_gen.get_rteAllowTxWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('allow_tx', signals['Length [Bit]'][sig_idx]) +' value);\n'
            
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):
            ## Time out rte read
            body = body + name_gen.get_datatype('Unsigned', 1) + ' ' + name_gen.get_rteTimeOutReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void);\n'
            
            ## Time out rte write
            body = body +  'void ' + name_gen.get_rteTimeOutWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('Unsigned', 1) +' value);\n'
            
            ## Crc rte read
            body = body + name_gen.get_datatype('checksum_check', 0) + ' ' + name_gen.get_rteCrcReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void);\n'
            
            ## Crc rte write
            body = body +  'void ' + name_gen.get_rteCrcWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('checksum_check', 0) +' value);\n'

            ## rolling counter rte read
            body = body + name_gen.get_datatype('rolling_counter_check', 8) + ' ' + name_gen.get_rteRollCounterReadFn(msg_dataframe['Name'][msg_idx], suffix) + '(void);\n'

            ## rolling counter rte write
            body = body +  'void ' + name_gen.get_rteRollCounterWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(' + name_gen.get_datatype('rolling_counter_check', 8) +' value);\n'

    return body
 
def get_rteHandlers(signals, msg_dataframe, interface, suffix):
    body = ''
    body = '#include "cxdtypes.h"\n'
    body = body + '#include "cxcan_types.h"\n'    
    body = body + '#include "rte_comm.h"\n'
    body = body + get_variableDeclarationr(signals, msg_dataframe, interface, suffix)
    body = body + '\n'
    body = body + get_RteFn(signals, msg_dataframe, interface, suffix)
    
    return body
    