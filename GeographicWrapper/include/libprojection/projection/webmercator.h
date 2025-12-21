#pragma once
#include "projection.h"
#include "../datum/ellipsoid.h"

namespace libprojection {

class WebMercator : public Projection {
public:
    explicit WebMercator(const Ellipsoid& ellipsoid);

    ProjectedPoint Forward(const GeoPoint& p) const override;
    GeoPoint Inverse(const ProjectedPoint& p) const override;

private:
    double R_; // sphere radius (WGS84 a)
};

} 