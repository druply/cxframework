import naming_gen as name_gen
import pandas as pd

input_body = ''
outputs_signals = ''
input_signals =''
output_body = ''
input_body = ''
script_body = ''
output_itr = 1
input_itr = 1

input_read =  ''
output_write =  ''

output_name = 'main_app_Y'
input_name = 'main_app_U'

def populateInput(signal_name, signal_type, length):
    print('')
    global input_signals
    global input_itr
    input_signals = input_signals + 'elemens(' + str(input_itr) + ') = Simulink.BusElement;\n'
    input_signals = input_signals + 'elemens(' + str(input_itr) + ').Name = \'' + signal_name + '\'' + ';\n' 
    input_signals = input_signals + 'elemens(' + str(input_itr) + ').DataType = \'' + name_gen.getSimdataType(signal_type, length) + '\'' + ';\n\n'
    
    input_itr = input_itr + 1
    
def populateOutput(signal_name, signal_type, length):
    global outputs_signals
    global output_itr
    outputs_signals = outputs_signals + 'elemens(' + str(output_itr) + ') = Simulink.BusElement;\n'
    outputs_signals = outputs_signals + 'elemens(' + str(output_itr) + ').Name = \'' + signal_name + '\'' + ';\n' 
    outputs_signals = outputs_signals + 'elemens(' + str(output_itr) + ').DataType = \'' + name_gen.getSimdataType(signal_type, length) + '\'' + ';\n\n'
    
    output_itr = output_itr + 1  

def populateOutWrite(signal_name, msg_name, suffix):
    global output_write
    output_write = output_write + name_gen.get_rteWriteFn(msg_name, signal_name, suffix) + '(' + output_name + '.' + msg_name +'.' + signal_name + ');\n' 

def populateInRead(signal_name, msg_name, suffix):
    global input_read
    input_read = input_read + input_name + '.' + msg_name + '.' + signal_name + ' = ' + name_gen.get_rteReadFn(msg_name, signal_name, suffix) + '();\n'
    
def populateScript(msg_dataframe, signals_df,interface, suffix, can_channel):
    global output_itr
    global input_itr
    global output_body    
    global input_body    
    global outputs_signals
    global input_signals
    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):            
            for sig_idx in range(len(signals_df['Name'].index)):                
                if(signals_df['Message'][sig_idx] == msg_dataframe['Name'][msg_idx]):
                    if(signals_df['Type'][sig_idx] == 'signal'):                        
                        populateOutput(signals_df['Name'][sig_idx], signals_df['Value Type'][sig_idx], signals_df['Length [Bit]'][sig_idx])
                        populateOutWrite(signals_df['Name'][sig_idx], msg_dataframe['Name'][msg_idx], suffix)
            
            output_body = output_body + outputs_signals
            #add allow tx signals
            output_body = output_body + 'elemens(' + str(output_itr) + ') = Simulink.BusElement;\n'   
            output_body = output_body + 'elemens(' + str(output_itr) + ').Name = \'' + name_gen.get_AllowTxVariableName( msg_dataframe['Name'][msg_idx], suffix) + '\';\n'
            output_body = output_body + 'elemens(' + str(output_itr) + ').Datatype = \'' + name_gen.getSimdataType('allow_tx', 0) + '\';\n'
            
            populateOutWrite(name_gen.get_AllowTxVariableName(msg_dataframe['Name'][msg_idx], suffix), msg_dataframe['Name'][msg_idx], suffix)
            
            output_body = output_body +  msg_dataframe['Name'][msg_idx] + '_out = Simulink.Bus;\n'
            output_body = output_body + msg_dataframe['Name'][msg_idx] + '_out.Elements = elemens;\n\n'
            output_body = output_body + 'clear elemens\n'
            outputs_signals = ''
            output_itr = 1
            
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):            
            for sig_idx in range(len(signals_df['Name'].index)):                
                if(signals_df['Message'][sig_idx] == msg_dataframe['Name'][msg_idx]):
                    if(signals_df['Type'][sig_idx] == 'signal'):                        
                        populateInput(signals_df['Name'][sig_idx], signals_df['Value Type'][sig_idx], signals_df['Length [Bit]'][sig_idx])
                        populateInRead(signals_df['Name'][sig_idx], msg_dataframe['Name'][msg_idx], suffix)
                    
                    if(signals_df['Type'][sig_idx] == 'checksum'):
                        #add crc msg handlers
                        input_body = input_body + 'elemens(' + str(input_itr) + ') = Simulink.BusElement;\n'
                        input_body = input_body + 'elemens(' + str(input_itr) + ').Name = \'' + name_gen.get_CrcVariableName( msg_dataframe['Name'][msg_idx], suffix) + '\';\n'
                        input_body = input_body + 'elemens(' + str(input_itr) + ').Datatype = \'' + name_gen.getSimdataType('checksum_check', 8) + '\';\n'            
                        populateInRead(name_gen.get_CrcVariableName(msg_dataframe['Name'][msg_idx], suffix), msg_dataframe['Name'][msg_idx], suffix)
                        
                    if(signals_df['Type'][sig_idx] == 'rolling_counter'):
                        #add rc msg handlers
                        input_body = input_body + 'elemens(' + str(input_itr) + ') = Simulink.BusElement;\n'
                        input_body = input_body + 'elemens(' + str(input_itr) + ').Name = \'' + name_gen.get_RollCountVariableName( msg_dataframe['Name'][msg_idx], suffix) + '\';\n'
                        input_body = input_body + 'elemens(' + str(input_itr) + ').Datatype = \'' + name_gen.getSimdataType('rolling_counter_check', 8) + '\';\n'            
                        populateInRead(name_gen.get_RollCountVariableName(msg_dataframe['Name'][msg_idx], suffix), msg_dataframe['Name'][msg_idx], suffix)
            
            input_body = input_body + input_signals
            #add timeout msg handlers
            input_body = input_body + 'elemens(' + str(input_itr) + ') = Simulink.BusElement;\n'
            input_body = input_body + 'elemens(' + str(input_itr) + ').Name = \'' + name_gen.get_TimeOutVariableName( msg_dataframe['Name'][msg_idx], suffix) + '\';\n'
            input_body = input_body + 'elemens(' + str(input_itr) + ').Datatype = \'' + name_gen.getSimdataType('Unsigned', 8) + '\';\n'            
            populateInRead(name_gen.get_TimeOutVariableName(msg_dataframe['Name'][msg_idx], suffix), msg_dataframe['Name'][msg_idx], suffix)
            
            
            
            input_body = input_body +  msg_dataframe['Name'][msg_idx] + '_in = Simulink.Bus;\n'
            input_body = input_body + msg_dataframe['Name'][msg_idx] + '_in.Elements = elemens;\n\n'
            input_body = input_body + 'clear elemens\n'
            input_signals = ''
            input_itr = 1
            

            
            
def getOutputWrites():
    global output_write
    return output_write

def getInputReads():
    global input_read
    return input_read
            
def getScriptContent():
    global script_body
    script_body = output_body + input_body
    return script_body