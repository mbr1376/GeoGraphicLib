#include "libprojection/geodesy/geodesicengine.h"
#include <GeographicLib/GeodesicLine.hpp>

namespace libprojection {

GeodesicEngine::GeodesicEngine()
    : geod_(GeographicLib::Geodesic::WGS84()) {}

GeodesicEngine::GeodesicEngine(double a, double f)
    : geod_(a, f) {}

double GeodesicEngine::Distance(double lat1, double lon1,
                                double lat2, double lon2) const {
    double s12;
    geod_.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12;
}

void GeodesicEngine::Inverse(double lat1, double lon1,
                             double lat2, double lon2,
                             double& s12,
                             double& azi1,
                             double& azi2) const {
    geod_.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

void GeodesicEngine::Direct(double lat1, double lon1,
                            double azi1,
                            double s12,
                            double& lat2,
                            double& lon2,
                            double& azi2) const {
    geod_.Direct(lat1, lon1, azi1, s12, lat2, lon2, azi2);
}

void GeodesicEngine::MidPoint(double lat1, double lon1,
                              double lat2, double lon2,
                              double& latm,
                              double& lonm) const {
    double s12, azi1, azi2;
    geod_.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);

    auto line = geod_.Line(lat1, lon1, azi1);
    double azi;
    line.Position(s12 / 2, latm, lonm, azi);
}

} // namespace libprojection
