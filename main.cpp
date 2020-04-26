#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include <string.h> //stoi

#define OK	0

#define DEVICE_ID 4095
#define MESSAGE_SIZE 48
#define GROUP_FLAG 0

#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 12
#define GROUP_FLAG_SIZE 1

#define DELTA_MAX_LAT 17001
#define DELTA_MAX_LNG 23001
#define LAT_MIN	42900000
#define LNG_MIN 22380000

using namespace std;

void splitString (string, char, vector<string> &);
int generateCoordinate(int, int);
void compressCoordinate(string, unsigned short []);
string generateLocation ();
uint8_t insertField(uint8_t, int, unsigned);
int extractField(uint8_t, unsigned, unsigned);

void splitString (string str, char delimiter, vector<string> &v){
  unsigned position = str.find(delimiter);

  while (position < str.size()){
    v.push_back(str.substr(0, position));
    str.erase(0, position+1);//+delimiter.size());
    position = str.find(delimiter);
  }
  if (str.size())
    v.push_back(str);
}

int generateCoordinate(int coord_min, int delta_max){
	srand(unsigned(time(NULL)));
	int rand_num = (rand() % delta_max);
	return (coord_min + rand_num)*-1; 
}

void compressCoordinate(string coordinates, unsigned short compressedCoord[]){
	vector <string> splited_coord;

	splitString(coordinates, ';', splited_coord);

	compressedCoord[0] = stoi(splited_coord[0])*(-1) - LAT_MIN;
	compressedCoord[1] = stoi(splited_coord[1])*(-1) - LNG_MIN;
}

long decompressCoordinate(uint16_t coord, long offset){
	return (coord + offset)*-1;
}

string generateLocation (){
	string location;
	
	location += to_string(generateCoordinate(LAT_MIN, DELTA_MAX_LAT));
	location += ';';
	location += to_string(generateCoordinate(LNG_MIN, DELTA_MAX_LNG));

	return location;
}

void insertField(uint16_t *messageChunk, uint16_t field, uint16_t fieldSize){
  *messageChunk <<= fieldSize;
  *messageChunk += field;
}

uint16_t extractField(uint16_t *messageChunk, uint16_t fieldSize){
	uint16_t value;
	value = *messageChunk & ((1 << fieldSize)-1);
	*messageChunk >>= fieldSize;
	return value;
}

generateBeacon(&message, Fields *, fieldCount)

int main (int argc, char **argv){
	uint16_t message[MESSAGE_SIZE/16];
	string location = generateLocation();
	unsigned short compressedCoord[2];
	uint16_t messageType = 5;

	cout << "Coordenada: " << location << endl;

	//Compressing Coordinates
	compressCoordinate(location, compressedCoord);

	insertField(&message[0], messageType, MSG_TYPE_SIZE);
	insertField(&message[0], (uint16_t) GROUP_FLAG, GROUP_FLAG_SIZE);
	insertField(&message[0], (uint16_t) DEVICE_ID, DEVICE_ID_SIZE);
	insertField(&message[1], compressedCoord[0], 16);
	insertField(&message[2], compressedCoord[1], 16);

	//Transmission
	cout << "\nMessage to send: " << message[0] << " " << message[1] << " " << message[2] << endl;

	//Reception
	cout << "Retrieved Device ID: " << extractField(&message[0], DEVICE_ID_SIZE) << endl;
	cout << "Retrieved Group Flag: " << extractField(&message[0], GROUP_FLAG_SIZE) << endl;
	cout << "Retrieved Message Type: " << extractField(&message[0], MSG_TYPE_SIZE) << endl;
	cout << "Retrieved Latitude: " << decompressCoordinate(message[1], LAT_MIN) << endl;
	cout << "Retrieved Longitude: " << decompressCoordinate(message[2], LNG_MIN) << endl;
	
	return OK;
}