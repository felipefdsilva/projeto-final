#include <time.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h> //stoi

#include "coordinate.h"

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