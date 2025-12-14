#include "GeoWrapper.h"
#include <GeographicLib/PolygonArea.hpp>

using namespace GeographicLib;

GeoWrapper::GeoWrapper(CoordinateSystem cs) : coordSystem(cs) {
    switch (cs) {
        case WGS84:
            geod = Geodesic::WGS84();
            break;
        case UTM:
            geod = Geodesic::UTM();
            break;
        case UPS:
            geod = Geodesic::UPS();
            break;
        case MGRS:
            geod = Geodesic::MGRS();
            break;
        case EGM:
            geod = Geodesic::EGM();
            break;
        case WMM:
            geod = Geodesic::WMM();
            break;
        case IGRF:
            geod = Geodesic::IGRF();
            break;
    }
}
double GeoWrapper::Distance(double lat1, double lon1, double lat2, double lon2) {
    double s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12; // فاصله بر حسب متر
}

void GeoWrapper::Azimuth(double lat1, double lon1, double lat2, double lon2,
                         double& azi1, double& azi2) {
    double s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

double GeoWrapper::polygonArea(const std::vector<double>& lats, const std::vector<double>& lons) {
    PolygonArea poly(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        poly.AddPoint(lats[i], lons[i]);
    double perimeter, area;
    poly.Compute(false, true, perimeter, area);
    return area; // متر مربع
}
