/*
* Deals with protocol message types
* Felipe Ferreira
* Fev/2020
*/
#include <Arduino.h>
#include "message.h"

using namespace std;

Message processMessage(char *msg, unsigned lenMessage){
    String message(msg);
    Message stMessage;

    if((unsigned)message[0] == 1){
        stMessage.type = message[0];
        stMessage.id = message.substring(1, 2);
        stMessage.lat = message.substring(3, 10);
        stMessage.lng = message.substring(13, 10);  
    }
    return stMessage;
}
