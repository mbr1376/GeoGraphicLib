#include "libprojection/projection/transversemercator.h"
#include <GeographicLib/TransverseMercatorExact.hpp>
#include <GeographicLib/Constants.hpp>

using namespace GeographicLib;

namespace libprojection {

TransverseMercator::TransverseMercator(const Ellipsoid& ellipsoid,
                                       double lon0,
                                       double k0)
    : ellipsoid_(ellipsoid), lon0_(lon0), k0_(k0) {}

ProjectedPoint TransverseMercator::Forward(const GeoPoint& p) const {
    TransverseMercatorExact tm(ellipsoid_.a(), ellipsoid_.f(), k0_);
    double x, y;
    tm.Forward(lon0_, p.lat, p.lon, x, y);
    return { x, y };
}

GeoPoint TransverseMercator::Inverse(const ProjectedPoint& p) const {
    TransverseMercatorExact tm(ellipsoid_.a(), ellipsoid_.f(), k0_);
    double lat, lon;
    tm.Reverse(lon0_, p.x, p.y, lat, lon);
    return { lat, lon };
}

} // namespace libprojection
