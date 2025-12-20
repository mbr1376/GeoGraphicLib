#include "libprojection/datum/datum.h"

namespace libprojection {

Datum::Datum(const std::string& name, const Ellipsoid& ellipsoid)
    : name_(name), ellipsoid_(ellipsoid) {}

const std::string& Datum::name() const { return name_; }
const Ellipsoid& Datum::ellipsoid() const { return ellipsoid_; }

Datum Datum::WGS84() {
    return Datum("WGS84", Ellipsoid::WGS84());
}

Datum Datum::NAD83() {
    return Datum("NAD83", Ellipsoid::GRS80());
}

} // namespace libprojection
