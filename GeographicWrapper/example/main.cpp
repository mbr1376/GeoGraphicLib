#include <iostream>
#include "GeoWrapper.h"
int main() {
    // Simple demo: print UTM and MGRS for a sample point and distance between two points
    double lat = 35.6892, lon = 51.3890; // Tehran
    int zone; bool northp; double easting, northing;
    GeoWrapper::LatLonToUTM(lat, lon, zone, northp, easting, northing);
    std::cout << "Point: " << lat << ", " << lon << " -> UTM zone " << zone << (northp?"N":"S")
              << " E=" << easting << " N=" << northing << "\n";

    std::string mgrs = GeoWrapper::LatLonToMGRS(lat, lon, 5);
    std::cout << "MGRS: " << mgrs << "\n";

    double lat2 = 35.7000, lon2 = 51.4000;
    double d = GeoWrapper::Distance(lat, lon, lat2, lon2);
    double azi1, azi2;
    GeoWrapper::Azimuth(lat, lon, lat2, lon2, azi1, azi2);
    std::cout << "Distance: " << d << " m, Azimuth: " << azi1 << " deg\n";

    // polygon area demo (approx small square)
    std::vector<double> lats = {35.6892, 35.6892, 35.7000, 35.7000};
    std::vector<double> lons = {51.3890, 51.4000, 51.4000, 51.3890};
    double area = GeoWrapper::polygonArea(lats, lons);
    std::cout << "Polygon area: " << area << " m^2\n";

    return 0;
}
