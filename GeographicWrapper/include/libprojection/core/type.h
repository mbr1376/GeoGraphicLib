#pragma once

namespace libprojection {

struct GeoPoint {
    double lat; // latitude (deg)
    double lon; // longitude (deg)
};

struct ProjectedPoint {
    double x;
    double y;
};

} // namespace libprojection
