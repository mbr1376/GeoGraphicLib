#include "libprojection/projection/utmprojection.h"
#include <cmath>

namespace libprojection {

UTMProjection::UTMProjection(int zone, bool northp, const Ellipsoid& ellipsoid)
    : TransverseMercator(ellipsoid, (zone - 1) * 6 - 180 + 3, 0.9996),
      zone_(zone),
      northp_(northp) {}

int UTMProjection::LatLonToZone(double lat, double lon) {
    return int(std::floor((lon + 180.0) / 6.0)) + 1;
}

} // namespace libprojection
