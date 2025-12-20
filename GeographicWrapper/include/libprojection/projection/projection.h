#pragma once
#include "../core/type.h"

namespace libprojection {

class Projection {
public:
    virtual ~Projection() = default;

    virtual ProjectedPoint Forward(const GeoPoint& p) const = 0;
    virtual GeoPoint Inverse(const ProjectedPoint& p) const = 0;
};

} // namespace libprojection
