#include "libprojection/datum/ellipsoid.h"

namespace libprojection {

Ellipsoid::Ellipsoid(double a, double f, const std::string& name)
    : a_(a), f_(f), name_(name) {}

double Ellipsoid::a() const { return a_; }
double Ellipsoid::f() const { return f_; }
const std::string& Ellipsoid::name() const { return name_; }

Ellipsoid Ellipsoid::WGS84() {
    return Ellipsoid(6378137.0, 1.0 / 298.257223563, "WGS84");
}

Ellipsoid Ellipsoid::GRS80() {
    return Ellipsoid(6378137.0, 1.0 / 298.257222101, "GRS80");
}

} // namespace libprojection
