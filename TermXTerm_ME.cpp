bool sleep(){
    bool radio_status = false; //Turn radio OFF

    return radio_status;
}

bool waitForTerminalBeacon(){
    while(t < listening_period){
        //listening to channel until beacon
        if (beacon){
            return true;
        }
    }
    return false;
}

void registerTerminal(uint8_t terminalID){
    //registra ID do terminal
}
void sendRegistries(registries){
    //lora.send(registries)
}