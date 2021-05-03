//#include <SPI.h>
//#include <RH_RF95.h>
//#include <time.h>
//#include <string.h>
//#include <RTCZero.h>
#include <ctime>
#include<unistd.h>

#include "field.h"
#include "message.h"
#include "../maquina_de_estados/terminal_machine.h"

unsigned sec = 1*1000*1000;

void setup() {

}
void loop(){
    usleep(2*sec);//sleeps for 3 second
    
    TerminalMachine terminalMachine;
    terminalMachine.run();
}