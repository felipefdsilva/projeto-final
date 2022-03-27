compile-test:
	g++ -c -Wall messages/* tests/main.cpp

linkedit-test:
	g++ -Wall -o localTest *.o

run:
	./localTest

clean:
	rm *.o