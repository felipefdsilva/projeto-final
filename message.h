#ifndef _MESSAGE_H_
#define _MESSAGE_H_ "message.h"

typedef struct {
    String id;
    String type;
    String lat;
    String lng;
} Message;

Message processMessage(char *, unsigned);

#endif
