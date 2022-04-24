.PHONY: messages sender receiver local-test clean

CC = g++
LD = g++
CFLAGS = -Wall -std=c++11
LFLAGS = -Wall -std=c++11

MESSAGE_SRC = messages/message.cpp messages/field.cpp
MESSAGE_OBJS = field.o message.o

HTTP_SRC = tests/http.cpp
HTTP_OBJS = http.o

SENDER_SRC = $(MESSAGE_SRC) $(HTTP_SRC) tests/sender.cpp
SENDER_OBJS = $(MESSAGE_OBJS) $(HTTP_OBJS) sender.o

RECEIVER_SRC = $(MESSAGE_SRC) $(HTTP_SRC) tests/receiver.cpp
RECEIVER_OBJS = $(MESSAGE_OBJS) $(HTTP_OBJS) receiver.o

EXECS = sender receiver

clean-objs:
	rm -f *.o

clean-execs:
	rm -f $(EXECS)

clean: clean-objs clean-execs

sender:
	$(CC) $(CFLAGS) -c $(SENDER_SRC)
	$(LD) $(LFLAGS) -o $@ $(SENDER_OBJS)

receiver:
	$(CC) $(CFLAGS) -c $(RECEIVER_SRC)
	$(LD) $(LFLAGS) -o $@ $(RECEIVER_OBJS)

all: $(EXECS)