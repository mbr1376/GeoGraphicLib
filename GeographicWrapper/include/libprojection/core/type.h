#pragma once

namespace libprojection {

/**
 * @brief Geographic coordinate in degrees.
 */
struct GeoPoint {
    double lat; ///< latitude in degrees
    double lon; ///< longitude in degrees
};

/**
 * @brief Projected coordinate in planar space.
 */
struct ProjectedPoint {
    double x; ///< x coordinate in projection units
    double y; ///< y coordinate in projection units
};

} // namespace libprojection
