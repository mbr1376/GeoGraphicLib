#include "GeoWrapper.h"
#include <GeographicLib/PolygonArea.hpp>

using namespace GeographicLib;

double GeoWrapper::Distance(double lat1, double lon1, double lat2, double lon2) {
    const Geodesic& geod = Geodesic::WGS84();
    double s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12; // فاصله بر حسب متر
}

void GeoWrapper::Azimuth(double lat1, double lon1, double lat2, double lon2,
                         double& azi1, double& azi2) {
    const Geodesic& geod = Geodesic::WGS84();
    double s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

double GeoWrapper::polygonArea(const std::vector<double>& lats, const std::vector<double>& lons) {
    const Geodesic& geod = Geodesic::WGS84();
    PolygonArea poly(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        poly.AddPoint(lats[i], lons[i]);
    double perimeter, area;
    poly.Compute(false, true, perimeter, area);
    return area; // متر مربع
}
