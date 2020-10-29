import naming_gen as name_gen

def get_TxHandler(msg_name, interface, signals, suffix, CANChannel):
    body = '// transmit message for' + interface + '_' + msg_name + '\n'
    body = body + ('Std_ReturnType ' +  name_gen.get_TxHandlerName(msg_name, interface) + '(void) {\n')
    body = body + '    Std_ReturnType res;\n'
    body = body + '    cxcan_msg_t msg;\n'
    body = body + '    uint8_t i;\n' #temporary
        
    #variabel declaration
    for i in range(len(signals['Name'].index)):    
        if(signals['Message'][i] == msg_name):
            if(signals['Type'][i] == 'signal'):
                body = body + '    ' + name_gen.get_datatype(signals['Value Type'][i], signals['Length [Bit]'][i]) + ' ' + name_gen.get_sigName(signals['Name'][i]) + ';\n'
            else:
                body = body + '    ' + name_gen.get_datatype(signals['Type'][i],0) + ' ' + name_gen.get_sigName(signals['Name'][i]) + ';\n'            
    
    body =  body + '\n'
        
    #rte read dunctions
    for i in range(len(signals['Name'].index)):
        if((signals['Message'][i] == msg_name) and (signals['Type'][i] == 'signal')):    
            body = body + '    '+ name_gen.get_sigName(signals['Name'][i])+ ' = ' + name_gen.get_rteReadFn(msg_name, signals['Name'][i], suffix) + '();\n'
    
    body =  body + '\n'
            
    for i in range(len(signals['Name'].index)):
        if((signals['Message'][i] == msg_name) and (signals['Type'][i] == 'rolling_counter')):    
            body =  body + '    cxCalculateRC(&' + name_gen.get_sigName(signals['Name'][i]) + ');\n'    
            #body = body + '    '  + name_gen.get_sigName(signals['Name'][i]) + '++;\n\n'
            #body = body + '    if(' +  name_gen.get_sigName(signals['Name'][i]) + '> MAX_ROLL_COUNTER) {\n'
            #body = body + '            ' +  name_gen.get_sigName(signals['Name'][i]) + ' = 0;\n'
            #body = body + '     }\n'    
        if((signals['Message'][i] == msg_name) and (signals['Type'][i] == 'checksum')):
            body =  body + '    cxCalculateChecksum(&' + name_gen.get_sigName(signals['Name'][i]) + ', &msg);\n'
    ##### ADD data normalization
    body = body + get_TxNormalization(msg_name, interface, signals, suffix, CANChannel)
    ##############################
    
    body =  body + '\n'
    
    body =  body + '    // configure message\n'
    body =  body + '    msg.id = (uint16_t)' + msg_name +'_id;\n'
    body =  body + '    msg.hw_channel = (uint8_t)' + CANChannel +';\n'
    body =  body + '    msg.dlc = (uint8_t)8;\n'
    body =  body + '    // send message and get response\n'
    body =  body + '    res = candrvSendMsg(&msg);\n'
    body =  body + '    return res;\n'
    body = body + '}\n'
    return body    
    
def get_RxHandler(msg_name, interface, signals, suffix, CANChannel):
    
    body = '// Receive message for' + interface + '_' + msg_name + '\n' 
    body = body + ('void ' + name_gen.get_RxHandlerName(msg_name, interface) + '(cxcan_msg_t *msg) {\n')
    #variabel declaration    
    for i in range(len(signals['Name'].index)):    
        if(signals['Message'][i] == msg_name):
            if(signals['Type'][i] == 'signal'):
                body = body + '    ' + name_gen.get_datatype(signals['Value Type'][i], signals['Length [Bit]'][i]) + ' ' + name_gen.get_sigName(signals['Name'][i]) + ';\n'
            if(signals['Type'][i] == 'checksum'):            
                body = body + '    ' + name_gen.get_datatype(signals['Type'][i],0) + ' ' + name_gen.get_sigName(signals['Name'][i]) + ';\n'
                body = body + '    ' + name_gen.get_datatype('checksum_check',0) + ' ' + name_gen.get_sigName(signals['Name'][i]) + '_chk;\n'
            if(signals['Type'][i] == 'rolling_counter'):            
                body = body + '    ' + name_gen.get_datatype(signals['Type'][i],0) + ' ' + name_gen.get_sigName(signals['Name'][i]) + ';\n'
                body = body + '    ' + name_gen.get_datatype('rolling_counter_check',0) + ' ' + name_gen.get_sigName(signals['Name'][i]) + '_chk;\n'
                

    ##### ADD data normalization    
    body = body + '    uint8_t i;\n'
    body = body + '\n'
    body = body + get_RxNormalization(msg_name, interface, signals, suffix, CANChannel)
    ##################################
    
    for i in range(len(signals['Name'].index)):
        if((signals['Message'][i] == msg_name) and (signals['Type'][i] == 'rolling_counter')):    
            body =  body + '    ' + name_gen.get_sigName(signals['Name'][i]) + '_chk = ' + 'cxverifyRC(&' + name_gen.get_sigName(signals['Name'][i]) + ');\n'    
            #body = body + '    '  + name_gen.get_sigName(signals['Name'][i]) + '++;\n\n'
            #body = body + '    if(' +  name_gen.get_sigName(signals['Name'][i]) + '> MAX_ROLL_COUNTER) {\n'
            #body = body + '            ' +  name_gen.get_sigName(signals['Name'][i]) + ' = 0;\n'
            #body = body + '     }\n'    
        if((signals['Message'][i] == msg_name) and (signals['Type'][i] == 'checksum')):
            body =  body +  '    ' +name_gen.get_sigName(signals['Name'][i]) + '_chk = ' + 'cxverifyChecksum(&' + name_gen.get_sigName(signals['Name'][i]) + ', &msg);\n'
    body = body + '\n'
            
    #rte write dunctions
    for i in range(len(signals['Name'].index)):    
        if(signals['Message'][i] == msg_name):
            if(signals['Type'][i] == 'signal'):
                body = body + '    ' + name_gen.get_rteWriteFn(msg_name, signals['Name'][i], suffix) + '(' + name_gen.get_sigName(signals['Name'][i]) + ');\n'
            if(signals['Type'][i] == 'checksum'):
                body = body + '    ' + name_gen.get_rteCrcWriteFn(msg_name, suffix) + '(' +  name_gen.get_sigName(signals['Name'][i]) + '_chk);\n'
            if(signals['Type'][i] == 'rolling_counter'):
                body = body + '    ' + name_gen.get_rteRollCounterWriteFn(msg_name, suffix) + '(' +  name_gen.get_sigName(signals['Name'][i]) + '_chk);\n'
    body = body + '}\n'
    return body
        
def get_RxNormalization(msg_name, interface, signals, suffix, CANChannel):    
    body = '    // normalize data\n'
    body = body + '    //for (i = 8; i>0; i--) {\n'
    body = body + '        //'+ msg_name +'_msg.data[i - 1] = msg->data[i - 1];\n'
    body = body + '    //}\n'
    body = body + '    /*********Add normalization here*****/\n'
    body = body + '\n    /************************************/\n' 
    return body
    
def get_TxNormalization(msg_name, interface, signals, suffix, CANChannel):
    body = '    // normalize data\n'
    body = body + '    /*********Add normalization here*****/\n'
    body = body + '    //for (i = 8; i>0; i--) {\n'
    body = body + '        //msg->data[i - 1] = ' + msg_name +'_msg.data[i - 1];\n'
    body = body + '    //}\n'
    return body
    
def get_TxProtos(msg_name, interface):
    body = ''
    body = body + ('Std_ReturnType ' +  name_gen.get_TxHandlerName(msg_name, interface) + '(void);\n')
    return body
        
def get_RxProtos(msg_name, interface):
    body = ''
    body = body + ('void ' + name_gen.get_RxHandlerName(msg_name, interface) + '(cxcan_msg_t *msg);\n')
    return body
    
def get_msgHandler(direction, msg_name, interface, signals, suffix, CANChannel):
    result = ''    
    if(direction == 'Tx'):
        result = get_TxHandler(msg_name, interface, signals, suffix, CANChannel)
    if(direction == 'Rx'):
        result = get_RxHandler(msg_name, interface, signals, suffix, CANChannel)    
    return result