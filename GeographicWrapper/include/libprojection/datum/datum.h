#pragma once
#include "ellipsoid.h"
#include "helmert.h"

namespace libprojection {

class Datum {
public:
    static Datum WGS84();
    static Datum ED50();   // مثال

    const Ellipsoid& ellipsoid() const;
    const Helmert& toWGS84() const;

private:
    Datum(Ellipsoid e, Helmert h);

    Ellipsoid ellipsoid_;
    Helmert toWGS84_;
};

} // namespace libprojection
