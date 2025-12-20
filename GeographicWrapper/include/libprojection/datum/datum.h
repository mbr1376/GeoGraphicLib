#pragma once
#include <string>
#include "ellipsoid.h"

namespace libprojection {

class Datum {
public:
    Datum(const std::string& name, const Ellipsoid& ellipsoid);

    const std::string& name() const;
    const Ellipsoid& ellipsoid() const;

    // Common datums
    static Datum WGS84();
    static Datum NAD83();

private:
    std::string name_;
    Ellipsoid ellipsoid_;
};

} // namespace libprojection
