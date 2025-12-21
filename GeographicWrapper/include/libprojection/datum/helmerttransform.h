#pragma once
#include "helmert.h"

namespace libprojection {

struct Vec3 {
    double x, y, z;
};

class HelmertTransform {
public:
    static Vec3 Apply(const Vec3& v, const Helmert& h);
};

} // namespace libprojection
