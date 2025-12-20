#pragma once

#include <GeographicLib/Geodesic.hpp>

namespace libprojection {

class GeodesicEngine {
public:
    // Construct with WGS84 by default
    GeodesicEngine();

    // Construct with custom ellipsoid
    GeodesicEngine(double a, double f);

    double Distance(double lat1, double lon1,
                    double lat2, double lon2) const;

    void Inverse(double lat1, double lon1,
                 double lat2, double lon2,
                 double& s12,
                 double& azi1,
                 double& azi2) const;

    void Direct(double lat1, double lon1,
                double azi1,
                double s12,
                double& lat2,
                double& lon2,
                double& azi2) const;

    void MidPoint(double lat1, double lon1,
                  double lat2, double lon2,
                  double& latm,
                  double& lonm) const;

private:
    GeographicLib::Geodesic geod_;
};

} // namespace libprojection
