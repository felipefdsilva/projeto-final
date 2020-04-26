#include <string>

#ifndef _COORDINATE_H_
#define _COORDINATE_H_ "coordinate.h"

#define LAT_MIN	42900000
#define LNG_MIN 22380000
#define DELTA_MAX_LAT 17001
#define DELTA_MAX_LNG 23001

using namespace std;

int generateCoordinate(int, int);
void compressCoordinate(string, unsigned short []);
long decompressCoordinate(uint16_t, long);
string generateLocation ();

#endif