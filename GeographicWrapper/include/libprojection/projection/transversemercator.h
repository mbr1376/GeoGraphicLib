#pragma once
#include "projection.h"
#include "../datum/ellipsoid.h"

namespace libprojection {

class TransverseMercator : public Projection {
public:
    TransverseMercator(const Ellipsoid& ellipsoid,
                       double lon0 = 0.0,   // λ0 in degrees
                       double k0 = 0.9996); // scale factor

    ProjectedPoint Forward(const GeoPoint& p) const override;
    GeoPoint Inverse(const ProjectedPoint& p) const override;

private:
    Ellipsoid ellipsoid_;
    double lon0_; // central meridian (deg)
    double k0_;   // scale factor
};

} // namespace libprojection
