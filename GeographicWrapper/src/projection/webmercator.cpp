#include "libprojection/projection/webmercator.h"
#include "libprojection/core/type.h"
#include "libprojection/datum/ellipsoid.h"
#include <cmath>
#include <algorithm>

namespace libprojection {

static constexpr double MAX_LAT = 85.05112878;
static constexpr double DEG_TO_RAD = M_PI / 180.0;
static constexpr double RAD_TO_DEG = 180.0 / M_PI;

WebMercator::WebMercator(const Ellipsoid& ellipsoid)
    : R_(ellipsoid.a()) {}

ProjectedPoint WebMercator::Forward(const GeoPoint& p) const {
    double lat = std::clamp(p.lat, -MAX_LAT, MAX_LAT);

    double x = R_ * p.lon * DEG_TO_RAD;
    double y = R_ * std::log(std::tan(M_PI / 4.0 + lat * DEG_TO_RAD / 2.0));

    return { x, y };
}

GeoPoint WebMercator::Inverse(const ProjectedPoint& p) const {
    double lon = (p.x / R_) * RAD_TO_DEG;
    double lat = (2.0 * std::atan(std::exp(p.y / R_)) - M_PI / 2.0) * RAD_TO_DEG;

    return { lat, lon };
}

} // namespace libprojection
