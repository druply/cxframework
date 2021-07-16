def get_datatype(dtype, dlength):
    if (dtype == 'Unsigned'):        
        if(int(dlength) <= 8):
            return    'uint8_t'    
        if(8 < int(dlength) <= 16):
            return    'uint16_t'
        if(16 < int(dlength) <= 32):
            return    'uint32_t'
    if(dtype == 'Signed'):
        if(int(dlength) <= 8):
            return    'int8_t'
        if(8 < int(dlength) <= 16):
            return    'int16_t'
        if(16 < int(dlength) <= 32):
            return    'int32_t'
    if(dtype == 'rolling_counter'):        
            return    'static uint8_t'    
    if(dtype == 'rolling_counter_check'):        
            return    'cxRCCheck_t'
    if(dtype == 'checksum'):        
            return    'cxCrc_t'
    if(dtype == 'checksum_check'):        
            return    'cxCrcCheck_t'
    if(dtype == 'allow_tx'):        
            return    'cxAllowTx_t'

def getSimdataType(dtype, dlength):
    if (dtype == 'Unsigned'):        
        if(int(dlength) <= 8):
            return    'uint8'    
        if(8 < int(dlength) <= 16):
            return    'uint16'
        if(16 < int(dlength) <= 32):
            return    'uint32'
    if(dtype == 'Signed'):
        if(int(dlength) <= 8):
            return    'int8'
        if(8 < int(dlength) <= 16):
            return    'int16'
        if(16 < int(dlength) <= 32):
            return    'int32'    
    if(dtype == 'rolling_counter'):        
            return    'uint8'    
    if(dtype == 'rolling_counter_check'):        
            return    'cxRCCheck_t'
    if(dtype == 'checksum'):        
            return    'cxCrc_t'
    if(dtype == 'checksum_check'):        
            return    'cxCrcCheck_t'
    if(dtype == 'allow_tx'):        
            return    'cxAllowTx_t'   

def get_rteWriteFn(msg_name, signal_name, suffix):
    return ('Rte_IWrite_' + msg_name +  '_' + signal_name + '_' +  suffix)
    
def get_rteReadFn(msg_name, signal_name, suffix):
    return ('Rte_IRead_' + msg_name + '_' + signal_name + '_' +  suffix)

def get_rteCrcReadFn(msg_name,  suffix):
    return ('Rte_IRead_' + msg_name + '_Crc_' +  suffix )

def get_rteCrcWriteFn(msg_name, suffix):
    return ('Rte_IWrite_' + msg_name + '_Crc_' +  suffix )

def get_rteTimeOutReadFn(msg_name,  suffix):
    return ('Rte_IRead_' + msg_name + '_TimeOut_' +  suffix )

def get_rteTimeOutWriteFn(msg_name, suffix):
    return ('Rte_IWrite_' + msg_name + '_TimeOut_' +  suffix )

def get_rteAllowTxReadFn(msg_name, suffix):
    return ('Rte_IRead_' + msg_name + '_AllowTx_' +  suffix )

def get_rteAllowTxWriteFn(msg_name,  suffix):
    return ('Rte_IWrite_' + msg_name + '_AllowTx_' +  suffix )


def get_rteRollCounterReadFn(msg_name,  suffix):
    return ('Rte_IRead_' + msg_name + '_RollCounter_' +  suffix )

def get_rteRollCounterWriteFn(msg_name,  suffix):
    return ('Rte_IWrite_' + msg_name + '_RollCounter_' +  suffix )



def get_AllowTxVariableName(msg_name, suffix):
    return  '' + msg_name + '_' +  'AllowTx' + '_' + suffix 
    
def get_CrcVariableName(msg_name, suffix):
    return   '' + msg_name + '_' +  'Crc' + '_' + suffix 
    
def get_RollCountVariableName(msg_name, suffix):
    return   '' + msg_name + '_' +  'RollCount' + '_' + suffix 
    
def get_TimeOutVariableName(msg_name, suffix):
    return  '' + msg_name + '_' +  'TimeOut' + '_' + suffix 
    
def getIdEnumName(msg_name, interface):
    return  msg_name.lower() +  '_' + interface.lower() + '_en'


def get_sigName(signal_name):
    return ('s_' + signal_name)

def get_TxHandlerName(msg_name, interface):
    return (interface + '_' + msg_name + 'TxHandler')
    
def get_RxHandlerName(msg_name, interface):
    return (interface + '_' + msg_name + 'RxHandler')


    
