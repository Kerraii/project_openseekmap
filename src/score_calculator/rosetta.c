#include <math.h>
#include "rosetta.h"

// Straal van de aarde in km
#define R 6371
#define TO_RAD (3.1415926536 / 180)
double d_geo(double lat1, double lon1, double lat2, double lon2)
{
    double dx, dy, dz;
    lon1 = lon1 - lon2;
    lon1 *= TO_RAD, lat1 *= TO_RAD, lat2 *= TO_RAD;

    dz = sin(lat1) - sin(lat2);
    dx = cos(lon1) * cos(lat1) - cos(lat2);
    dy = sin(lon1) * cos(lat1);
    return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R; // km
}

