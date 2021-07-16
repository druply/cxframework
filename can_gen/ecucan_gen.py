import naming_gen as name_gen
import numpy as np

txbody = ''
headers = ''
cyclic_handlers10 = ''
cyclic_handlers20 = ''
cyclic_handlers50 = ''
cyclic_handlers100 = ''
cyclic_handlers1000 = ''
rxbody = ''
ids = ''
ecuinit = ''
ecutimeout = ''
message_enum = ''
msg_enum_itr = 0

def populateCyclicHandlers(msg_dataframe, interface, suffix, can_channel):
    global cyclic_handlers10
    global cyclic_handlers20
    global cyclic_handlers50
    global cyclic_handlers100
    global cyclic_handlers1000
    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):            
            if(msg_dataframe['Cycle Time'][msg_idx] == 10):
                cyclic_handlers10 = cyclic_handlers10 + '    msg.hw_channel = ' + can_channel + ';\n'
                cyclic_handlers10 = cyclic_handlers10 + '    msg.id = ' + msg_dataframe['Name'][msg_idx] + '_id;\n'
                #cyclic_handlers10 = cyclic_handlers10 + '    ' + 'ecucanTxHandler(' + msg_dataframe['Name'][msg_idx] + '_id);\n'                
                cyclic_handlers10 = cyclic_handlers10 + '    ' + 'ecucanTxHandler(&msg);\n\n'
            if(msg_dataframe['Cycle Time'][msg_idx] == 20):
                cyclic_handlers20 = cyclic_handlers20 + '    msg.hw_channel = ' + can_channel + ';\n'
                cyclic_handlers20 = cyclic_handlers20 + '    msg.id = ' + msg_dataframe['Name'][msg_idx] + '_id;\n'
                cyclic_handlers20 = cyclic_handlers20 + '    ' + 'ecucanTxHandler(&msg);\n\n'
                #cyclic_handlers20 = cyclic_handlers20 + '    ' + 'ecucanTxHandler(' + msg_dataframe['Name'][msg_idx] + '_id);\n'
            if(msg_dataframe['Cycle Time'][msg_idx] == 50):
                cyclic_handlers50 = cyclic_handlers50 + '    msg.hw_channel = ' + can_channel + ';\n'
                cyclic_handlers50 = cyclic_handlers50 + '    msg.id = ' + msg_dataframe['Name'][msg_idx] + '_id;\n'
                cyclic_handlers50 = cyclic_handlers50 + '    ' + 'ecucanTxHandler(&msg);\n\n'
                #cyclic_handlers50 = cyclic_handlers50 + '    ' + 'ecucanTxHandler(' + msg_dataframe['Name'][msg_idx] + '_id);\n'
            if(msg_dataframe['Cycle Time'][msg_idx] == 100):
                cyclic_handlers100 = cyclic_handlers100 + '    msg.hw_channel = ' + can_channel + ';\n'
                cyclic_handlers100 = cyclic_handlers100 + '    msg.id = ' + msg_dataframe['Name'][msg_idx] + '_id;\n'
                cyclic_handlers100 = cyclic_handlers100 + '    ' + 'ecucanTxHandler(&msg);\n\n'
                #cyclic_handlers100 = cyclic_handlers100 + '    ' + 'ecucanTxHandler(' + msg_dataframe['Name'][msg_idx] + '_id);\n'
            if(msg_dataframe['Cycle Time'][msg_idx] == 1000):
                cyclic_handlers1000 = cyclic_handlers1000 + '    msg.hw_channel = ' + can_channel + ';\n'
                cyclic_handlers1000 = cyclic_handlers1000 + '    msg.id = ' + msg_dataframe['Name'][msg_idx] + '_id;\n'
                cyclic_handlers1000 = cyclic_handlers1000 + '    ' + 'ecucanTxHandler(&msg);\n\n'
                #cyclic_handlers1000 = cyclic_handlers1000 + '    ' + 'ecucanTxHandler(' + msg_dataframe['Name'][msg_idx] + '_id);\n'
    
    
        
def populateTxHandler(msg_dataframe, interface, suffix, can_channel):
    global txbody
    txbody = txbody + '    if(msg->hw_channel == (uint8_t)' + can_channel + ') {\n'
    txbody = txbody + '        switch(msg->id) {\n'
    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Tx'):
            txbody = txbody + '            case '  + msg_dataframe['Name'][msg_idx] + '_id:\n\n'
            txbody = txbody + '                if(' + name_gen.get_rteAllowTxReadFn(msg_dataframe['Name'][msg_idx], suffix) + '() == T_ALLOW) {\n'
            txbody = txbody + '                    if(' + name_gen.get_TxHandlerName(msg_dataframe['Name'][msg_idx], interface) + '() == E_NOT_OK) {\n'
            txbody = txbody + '                        cxcanTxError(msg);\n'
            txbody = txbody + '                    }\n'
            txbody = txbody + '                 }\n'
            txbody = txbody + '                 break;\n'
    txbody = txbody + '     default:\n'
    txbody = txbody + '         break;\n'
    txbody = txbody + '            }\n'
    txbody = txbody + '        }\n'
        

def populateRxHandler(msg_dataframe, interface, suffix, CANChannel):
    global rxbody
    rxbody =   rxbody + '    if(msg->hw_channel == (uint8_t)' + CANChannel + ') {\n'
    rxbody =   rxbody + '        // handle rx messages\n'
    rxbody =   rxbody + '    switch(msg->id) {\n'
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):    
            rxbody =   rxbody + '      case ' + msg_dataframe['Name'][msg_idx] + '_id:\n'
            rxbody =   rxbody + '           can_msg_tbl[' + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface) + '].to_ctr = 0;\n'
            rxbody =   rxbody + '           //receive message data\n'
            rxbody =   rxbody + '           ' + name_gen.get_RxHandlerName(msg_dataframe['Name'][msg_idx], interface) + '(msg);\n'            
            rxbody =   rxbody + '           ' + name_gen.get_rteTimeOutWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(cxFALSE);\n'
            rxbody =   rxbody + '           break;\n'
    rxbody =   rxbody + '      default:\n'
    rxbody =   rxbody + '         break;\n'
    rxbody =   rxbody + '     };\n'
    rxbody =   rxbody + '   }\n'
    
def populateHeaders(interface):
    global headers
    headers = headers + '#include "' + interface.lower() + '.h"\n'

def populateEnums(msg_dataframe, interface):
    global message_enum    
    global msg_enum_itr
    
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):
            if(msg_enum_itr == 0):
                msg_enum_itr = msg_enum_itr + 1
                message_enum = message_enum + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface) + ' = 0,\n'          
            else:
                message_enum = message_enum + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface) + ',\n'
            

def populateIds(msg_dataframe):
    global ids
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        ids = ids  + '#define ' + msg_dataframe['Name'][msg_idx] + '_id    ' + msg_dataframe['ID'][msg_idx] + '\n'

def populateecucanInit(msg_dataframe, interface):
    global ecuinit
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):
            ecuinit = ecuinit + '    // load Id intos can msg tabl\n'
            ecuinit = ecuinit + '    can_msg_tbl[' + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface) +'].id = (cxMsgId_t)'       + msg_dataframe['Name'][msg_idx]    + '_id;\n' 
            ecuinit = ecuinit + '    // load time out limit intos can msg tabl\n'
            ecuinit = ecuinit + '    can_msg_tbl[' + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface) + '].to_limit = (uint16_t)' + str(msg_dataframe['Timeout'][msg_idx]) + '; //ms\n' 

def populateecucanTimeOut(msg_dataframe, suffix, interface):
    global ecutimeout
    for msg_idx in range(len(msg_dataframe['Name'].index)):
        if(msg_dataframe['Direction'][msg_idx] == 'Rx'):
            #ecutimeout = ecutimeout + '        case ' + msg_dataframe['Name'][msg_idx]    + '_id:\n'
            ecutimeout = ecutimeout + '        case ' + name_gen.getIdEnumName(msg_dataframe['Name'][msg_idx], interface)    + ':\n'
            ecutimeout = ecutimeout + '            ' + name_gen.get_rteTimeOutWriteFn(msg_dataframe['Name'][msg_idx], suffix) + '(cxTRUE);\n'
            ecutimeout = ecutimeout + '            break;\n' 
            
def ecucanProtos():
    body = ''
    body = body + '#ifndef DEVICE_ECUCAN_INC_ECUCAN_H_\n'
    body = body + '#define DEVICE_ECUCAN_INC_ECUCAN_H_\n'
    body = body + '\n'
    body = body + '#define   CANDRV_CAN0            0\n'
    body = body + '#define   CANDRV_CAN1            1\n'
    body = body + '#define   CANDRV_CAN2            2\n'
    body = body + '#define   CANDRV_CAN3            3\n'
    
    body = body + '\n'
    body = body + '// define rx messages\n'
    body = body + 'typedef enum {\n'
        
    body = body + message_enum
        
    body = body + '    cxCAN_MSG_MAX\n'
    body = body + '} cxcan_msg_list_t;\n'
    body = body + '\n'
    
    body = body +  'void ecucanInit(void);\n'
    body = body +  'void ecucanTxHandler(cxcan_TxBuffer_t *msg);\n'
    body = body +  'void ecucanRxHandler(cxcan_msg_t *msg);\n'
    body = body +  'void ecucan10ms(void);\n'
    body = body +  'void ecucan20ms(void);\n'
    body = body +  'void ecucan50ms(void);\n'
    body = body +  'void ecucan100ms(void);\n'
    body = body +  'void ecucan1000ms(void);\n\n'
    body = body +  'void ecucanSetTimeOut(cxcan_msg_list_t msg_id);\n\n'
    body = body +  'extern cxcan_status_msg_t  can_msg_tbl[cxCAN_MSG_MAX];\n'
    body = body + '\n'
    body = body + ids
    body = body + '\n'
    body = body +  '#define  MAX_ROLL_COUNTER  3\n'
    
    body = body + '#endif /* DEVICE_ECUCAN_INC_ECUCAN_H_ */'
    return body    
    
    
    
    
def generateECUCan():
    global txbody
    body = '#include "cxdtypes.h"\n'
    body = body + '#include "cxcan_types.h"\n'
    body = body + '#include "cxcan.h"\n'
    body = body + '#include "ecucan.h"\n'
    body = body + '#include "rte_comm.h"\n'
    body = body +  headers
    body = body + '\n'
    body = body + 'cxcan_status_msg_t  can_msg_tbl[cxCAN_MSG_MAX];\n'
    body = body + '\n'
    body = body + 'void ecucanInit(void) {\n'
    body = body +    ecuinit
    body = body + '}\n'
    body = body + '\n'
    body = body + 'void ecucanTxHandler(cxcan_TxBuffer_t *msg) {\n'
    body = body + '    //Tx messages\n'

    body = body + txbody + '\n'

    body = body + '}\n'
    body = body + 'void ecucanRxHandler(cxcan_msg_t *msg) {\n'    
    body = body + '    // Rx handlers\n'    
    body = body + rxbody
    body = body + '}\n'
    body = body + '\n'
    body = body + 'void ecucan10ms(void) {\n'    
    body = body + '    cxcan_TxBuffer_t msg;\n'
    body = body + cyclic_handlers10 
    body = body + '}\n'
    body = body + '\n'
    body = body + 'void ecucan20ms(void) {\n'
    body = body + '    cxcan_TxBuffer_t msg;\n'
    body = body + cyclic_handlers20 
    body = body + '}\n'
    body = body + '\n'
    
    body = body + 'void ecucan50ms(void) {\n'
    body = body + '    cxcan_TxBuffer_t msg;\n'
    body = body + cyclic_handlers50 
    body = body + '}\n'
    
    body = body + 'void ecucan100ms(void) {\n'
    body = body + '    cxcan_TxBuffer_t msg;\n'
    body = body + cyclic_handlers100 
    body = body + '}\n'
    
    body = body + 'void ecucan1000ms(void) {\n'
    body = body + '    cxcan_TxBuffer_t msg;\n'
    body = body + cyclic_handlers1000 
    body = body + '}\n'
    body = body + 'void ecucanSetTimeOut(cxcan_msg_list_t msg_id) {\n'
    body = body + '    switch(msg_id) {\n'
    body = body +  ecutimeout
    body = body + '            default:\n'
    body = body + '                break;\n'
    body = body + '    }\n'
    body = body + '}\n'
    body = body + '\n'
    
    
    return body
          
