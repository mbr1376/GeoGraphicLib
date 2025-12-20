#pragma once
#include <string>

namespace libprojection {

class Ellipsoid {
public:
    Ellipsoid(double a, double f, const std::string& name = "");

    double a() const;
    double f() const;
    const std::string& name() const;

    // Common ellipsoids
    static Ellipsoid WGS84();
    static Ellipsoid GRS80();

private:
    double a_;       // semi-major axis
    double f_;       // flattening
    std::string name_;
};

} // namespace libprojection
