#include <iostream>
#include <time.h>
#include <math.h>       /* pow */
#include <iomanip>
#include <vector>
#include <string.h> //stoi
//#include "message.h"

#define DEVICE_ID 2
#define MESSAGE_SIZE 40

#define MSG_TYPE_SIZE 3
#define DEVICE_ID_SIZE 5
#define COORDINATES_SIZE 32

#define DELTA_MAX_LAT 17001
#define DELTA_MAX_LNG 23001
#define LAT_MIN	42900000
#define LNG_MIN 22380000

using namespace std;

void splitString (string, char, vector<string> &);
int generate_coordinate(int, int);
void compress_coordinate(string, unsigned short []);
string generate_location ();
uint8_t append_bits(uint8_t, int, unsigned);
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

int generate_coordinate(int coord_min, int delta_max){
	srand(unsigned(time(NULL)));
	int rand_num = (rand() % delta_max);
	cout << "rand num: " << rand_num << endl;
	return (coord_min + rand_num)*-1; 
}

void compress_coordinate(string coordinates, unsigned short compressed_coord[]){
	vector <string> splited_coord;

	splitString(coordinates, ';', splited_coord);

	compressed_coord[0] = stoi(splited_coord[0])*(-1) - LAT_MIN;
	compressed_coord[1] = stoi(splited_coord[1])*(-1) - LNG_MIN;
}
uint16_t decompress_coordinate(uint8_t coord1, uint8_t coord2){
	uint16_t coord;
	
	coord = coord1;
	coord <<= 8;
	coord += coord2; 

	return coord;
}

string generate_location (){
	string location;
	
	location += to_string(generate_coordinate(LAT_MIN, DELTA_MAX_LAT));
	location += ';';
	location += to_string(generate_coordinate(LNG_MIN, DELTA_MAX_LNG));

	return location;
}

uint8_t append_bits(uint8_t message_byte, int appendix, unsigned appendix_size){
  message_byte <<= appendix_size;
  message_byte += appendix;

  return message_byte;
}

int extractField(uint8_t message_byte, unsigned position, unsigned fieldSize){ 
    return ((message_byte >> (position - 1)) & ((1 << fieldSize) - 1)); 
}

int main (int argc, char **argv){
	uint8_t message[MESSAGE_SIZE/8];
	string location = generate_location();
	unsigned short compressed_coord[2];
	char messageType = '5';

	cout << location << endl;

	//Compressing Coordinates
	compress_coordinate(location, compressed_coord);
	cout << "delta_lat before transm: " << compressed_coord[0] << endl;
	cout << "delta_lng before transm: " << compressed_coord[1] << endl;

	message[4] = append_bits(message[4], messageType, MSG_TYPE_SIZE);
	message[4] = append_bits(message[4], DEVICE_ID, DEVICE_ID_SIZE);

	message[3] = (compressed_coord[0] >> 8) & 0xFF;
	message[2] = compressed_coord[0] & 0xFF;
	message[1] = (compressed_coord[1] >> 8) & 0xFF;
	message[0] = compressed_coord[1] & 0xFF;

	//Transmission
	cout << "Message to send: " << message << endl;

	//Reception
	cout << "Retrieved Device ID: " << extractField(message[4], 1, DEVICE_ID_SIZE) << endl;
	cout << "Retrieved Message Type: " << extractField(message[4], 1+DEVICE_ID_SIZE, MSG_TYPE_SIZE) << endl;
    
	cout << "Retrieved Latitude: " << (decompress_coordinate(message[3], message[2]) + LAT_MIN)*-1 << endl;
	cout << "Retrieved Longitude: " << (decompress_coordinate(message[1], message[0]) + LNG_MIN)*-1 << endl;
	
	return 0;
}