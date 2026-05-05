#pragma once
#include "projection.h"
#include "../datum/ellipsoid.h"

namespace libprojection {

/**
 * @brief Web Mercator projection implementation.
 */
class WebMercator : public Projection {
public:
    /**
     * @brief Construct a Web Mercator projection.
     * @param ellipsoid Reference ellipsoid used to derive the projection radius.
     */
    explicit WebMercator(const Ellipsoid& ellipsoid);

    /**
     * @brief Forward project geographic coordinates to Web Mercator.
     * @param p Geographic coordinate.
     * @return Projected coordinate.
     */
    ProjectedPoint Forward(const GeoPoint& p) const override;

    /**
     * @brief Inverse Web Mercator projection to geographic coordinates.
     * @param p Projected coordinate.
     * @return Geographic coordinate.
     */
    GeoPoint Inverse(const ProjectedPoint& p) const override;

private:
    double R_; ///< sphere radius (WGS84 semi-major axis)
};

} 