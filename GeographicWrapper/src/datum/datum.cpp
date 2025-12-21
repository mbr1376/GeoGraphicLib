#include "libprojection/datum/datum.h"

namespace libprojection {

Datum::Datum(Ellipsoid e, Helmert h)
    : ellipsoid_(e), toWGS84_(h) {}

Datum Datum::WGS84() {
    return Datum(Ellipsoid::WGS84(), Helmert{});
}

// نمونه معروف: ED50 → WGS84 (تقریبی)
Datum Datum::ED50() {
    Helmert h;
    h.tx = -87; h.ty = -98; h.tz = -121;
    h.rx = 0; h.ry = 0; h.rz = 0;
    h.s  = 0;
    return Datum(Ellipsoid::International1924(), h);
}

const Ellipsoid& Datum::ellipsoid() const { return ellipsoid_; }
const Helmert& Datum::toWGS84() const { return toWGS84_; }

} // namespace libprojection
