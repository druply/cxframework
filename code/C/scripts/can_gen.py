#import library
import pandas as pd
import handler_gen as hdlr_gen
import rte_gen
import ecucan_gen as ecu_gen
import simulink

file1_body = ''

def ecuTxRxgen(sig_dataframe, msg_dataframe, interface, CANChannel, suffix):
    file = '#include "cxdtypes.h"\n'
    file = file + '#include "cxcan_types.h"\n'
    file = file + '#include "can_struct.h"\n'
    file = file + '#include "candrv.h"\n'
    file = file + '#include "ecucan.h"\n'
    file = file + '#include "rte_comm.h"\n'
    file = file + '#include "' + interface.lower() + '.h"\n'
    file = file + '\n'        
    for msg_idx in range(len(message_df['Name'].index)):        
        msg_name    = message_df['Name'][msg_idx]
        msg_dir    = message_df['Direction'][msg_idx]      

        #file = file + name_gen.get_datatype(dtype, dlength) + name_gen.get_varName(signal_name)
        file = file + hdlr_gen.get_msgHandler(msg_dir, msg_name, Interface, signal_df, suffix, CANChannel)
    return file
        
def rteGen(sig_dataframe, msg_dataframe, interface, suffix):
    return rte_gen.get_rteHandlers(sig_dataframe, msg_dataframe, interface, suffix)

def rteProtos(signal_df, message_df, Interface, SUFFFIX):
    return rte_gen.getRteProtos(signal_df, message_df, Interface, SUFFFIX)

def getRxTxProtos(sig_dataframe, msg_dataframe, interface, suffix):
    body = ''
    for msg_idx in range(len(message_df['Name'].index)):        
        msg_name    = msg_dataframe['Name'][msg_idx]        
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):   
            body = body + hdlr_gen.get_TxProtos(msg_name, interface)
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):   
            body = body + hdlr_gen.get_RxProtos(msg_name, interface)
    return body
    
def ecucanGenerate(signal_df, message_df, Interface, CANChannel, SUFFFIX):
    #open file
    f = open(Interface.lower() + '.c', 'a')
    #get file content
    ecu_body = ecuTxRxgen(signal_df, message_df, Interface, CANChannel, SUFFFIX)
    #write content to file
    f.write(ecu_body)
    f.close()
    
    ecu_gen.populateTxHandler(message_df, Interface, SUFFFIX, CANChannel)
    ecu_gen.populateRxHandler(message_df, Interface, SUFFFIX, CANChannel)
    ecu_gen.populateCyclicHandlers(message_df, Interface, SUFFFIX, CANChannel)
    ecu_gen.populateEnums(message_df, Interface)
    ecu_gen.populateHeaders(Interface)
    ecu_gen.populateIds(message_df)
    ecu_gen.populateecucanInit(message_df, Interface)
    ecu_gen.populateecucanTimeOut(message_df, SUFFFIX, Interface)
    
    ##populate matlab script for inputs and outputs
    simulink.populateScript(message_df, signal_df, Interface, SUFFFIX, CANChannel)
    
    #open file
    f = open(Interface.lower() + '.h', 'a')
    #get file content
    ecu_proto = getRxTxProtos(signal_df, message_df, Interface, SUFFFIX)
    #write content to file
    f.write(ecu_proto)
    f.close()
    
    #open file
    f = open('rte_' + Interface.lower() + '.c', 'a')
    rte_body = rteGen(signal_df, message_df, Interface, SUFFFIX)
    f.write(rte_body)
    f.close()
    
        #open file
    f = open('rte_' + Interface.lower() + '.h', 'a')
    rte_proto = rteProtos(signal_df, message_df, Interface, SUFFFIX)
    f.write(rte_proto)
    f.close()
    

        
########repeat this code for every interface you wish to generate
#open message csv file
message_df = pd.read_csv('nt4_pce_messages.csv')
#open signal csv file
signal_df = pd.read_csv('nt4_pce_signals.csv')
#assign name to file
Interface = 'NT4_ECUA'
SUFFFIX = 'F'
#assign channel which this interace uses
CANChannel = 'CANDRV_CAN1'
ecucanGenerate(signal_df, message_df, Interface, CANChannel, SUFFFIX)
##################################################################


########repeat this code for every interface you wish to generate
#open message csv file
message_df = pd.read_csv('nt4_phs_messages.csv')
#open signal csv file
signal_df = pd.read_csv('nt4_phs_signals.csv')
#assign name to file
Interface = 'NT4_ECUB'
SUFFFIX = 'F'
#assign channel which this interace uses
CANChannel = 'CANDRV_CAN2'
ecucanGenerate(signal_df, message_df, Interface, CANChannel, SUFFFIX)
##################################################################


########repeat this code for every interface you wish to generate
#open message csv file
message_df = pd.read_csv('vehicle_messages.csv')
#open signal csv file
signal_df = pd.read_csv('vehicle_signals.csv')
#assign name to file
Interface = 'VEHICLE'
SUFFFIX = 'VEH'
#assign channel which this interace uses
CANChannel = 'CANDRV_CAN0'
ecucanGenerate(signal_df, message_df, Interface, CANChannel, SUFFFIX)
##################################################################


########repeat this code for every interface you wish to generate
#open message csv file
message_df = pd.read_csv('gw_messages.csv')
#open signal csv file
signal_df = pd.read_csv('gw_signals.csv')
#assign name to file
Interface = 'Gateway'
SUFFFIX = 'GW'
#assign channel which this interace uses
CANChannel = 'CANDRV_CAN1'
ecucanGenerate(signal_df, message_df, Interface, CANChannel, SUFFFIX)
##################################################################

#finish by executin gthis function
f = open('ecucan.c', 'a')
ecuca_body = ecu_gen.generateECUCan()
f.write(ecuca_body)
f.close()

f = open('ecucan.h', 'a')
ecuca_body = ecu_gen.ecucanProtos()
f.write(ecuca_body)
f.close()

#generate matlab script
f = open('bus.m', 'a')
script_content = simulink.getScriptContent()
f.write(script_content)
f.close()


#generate rte output writes
f = open('outputs.txt', 'a')
content = simulink.getOutputWrites()
f.write(content)
f.close()

#generate rte output writes
f = open('inputs.txt', 'a')
content = simulink.getInputReads()
f.write(content)
f.close()

