#pragma once
#include "projection.h"
#include "../datum/ellipsoid.h"

namespace libprojection {

/**
 * @brief Transverse Mercator projection implementation.
 */
class TransverseMercator : public Projection {
public:
    /**
     * @brief Construct a Transverse Mercator projection.
     * @param ellipsoid Reference ellipsoid.
     * @param lon0 Central meridian in degrees.
     * @param k0 Scale factor.
     */
    TransverseMercator(const Ellipsoid& ellipsoid,
                       double lon0 = 0.0,   ///< central meridian in degrees
                       double k0 = 0.9996); ///< scale factor

    /**
     * @brief Project geographic coordinates to Transverse Mercator space.
     * @param p Geographic coordinate.
     * @return Projected coordinate.
     */
    ProjectedPoint Forward(const GeoPoint& p) const override;

    /**
     * @brief Inverse Transverse Mercator projection.
     * @param p Projected coordinate.
     * @return Geographic coordinate.
     */
    GeoPoint Inverse(const ProjectedPoint& p) const override;

private:
    Ellipsoid ellipsoid_;
    double lon0_; ///< central meridian in degrees
    double k0_;   ///< scale factor
};

} // namespace libprojection
