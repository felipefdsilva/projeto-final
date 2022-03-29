compile-test:
	g++ -Wall -c messages/field.cpp messages/message.cpp tests/http_client.c tests/main.cpp

linkedit-test:
	g++ -Wall -o localTest *.o

run:
	./localTest

clean:
	rm -rf *.o