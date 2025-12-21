#include "libprojection/datum/HelmertTransform.h"
#include <cmath>

namespace libprojection {

static constexpr double ARCSEC_TO_RAD = M_PI / (180.0 * 3600.0);

Vec3 HelmertTransform::Apply(const Vec3& v, const Helmert& h) {
    // rotations to radians
    double rx = h.rx * ARCSEC_TO_RAD;
    double ry = h.ry * ARCSEC_TO_RAD;
    double rz = h.rz * ARCSEC_TO_RAD;

    // scale ppm → unitless
    double m = h.s * 1e-6;

    Vec3 out;
    out.x = h.tx + (1 + m) * ( v.x - rz * v.y + ry * v.z );
    out.y = h.ty + (1 + m) * ( rz * v.x + v.y - rx * v.z );
    out.z = h.tz + (1 + m) * ( -ry * v.x + rx * v.y + v.z );

    return out;
}

} // namespace libprojection
