#include "libprojection/GeoWrapper.h"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/PolygonArea.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/Georef.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <GeographicLib/Math.hpp>
#include <GeographicLib/GeodesicLine.hpp>
using namespace GeographicLib;

static const Geodesic& geod = Geodesic::WGS84();

// ================= GEODESIC =================
double GeoWrapper::Distance(double lat1, double lon1, double lat2, double lon2) {
    double s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12;
}

void GeoWrapper::Inverse(double lat1, double lon1,
                         double lat2, double lon2,
                         double& s12, double& azi1, double& azi2) {
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

void GeoWrapper::Direct(double lat1, double lon1, double azi1, double s12,
                        double& lat2, double& lon2, double& azi2) {
    geod.Direct(lat1, lon1, azi1, s12, lat2, lon2, azi2);
}

void GeoWrapper::MidPoint(double lat1, double lon1,
                          double lat2, double lon2,
                          double& latm, double& lonm){
    double s12, azi1, azi2;
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
    auto line = geod.Line(lat1, lon1, azi1);
    double azi;
    line.Position(s12 / 2, latm, lonm, azi);
}

// ================= POLYGON =================
double GeoWrapper::PolygonArea(const std::vector<double>& lats,
                               const std::vector<double>& lons) {
    GeographicLib::PolygonArea p(geod,false);
    for (size_t i = 0; i < lats.size(); ++i)
        p.AddPoint(lats[i], lons[i]);
    double per, area;
    p.Compute(false, true, per, area);
    return area;
}

double GeoWrapper::PolygonPerimeter(const std::vector<double>& lats,
                                    const std::vector<double>& lons) {
    GeographicLib::PolygonArea p(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        p.AddPoint(lats[i], lons[i]);
    double per, area;
    p.Compute(false, true, per, area);
    return per;
}

bool GeoWrapper::PointInPolygon(double lat, double lon,
                                const std::vector<double>& lats,
                                const std::vector<double>& lons) {
    GeographicLib::PolygonArea p(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        p.AddPoint(lats[i], lons[i]);
    p.AddPoint(lat, lon);
    double per, area;
    p.Compute(false, true, per, area);
    return area < 0;
}

// ================= COORD =================
void GeoWrapper::LatLonToUTM(double lat, double lon,
                             int& zone, bool& northp,
                             double& e, double& n) {
    UTMUPS::Forward(lat, lon, zone, northp, e, n);
}

void GeoWrapper::UTMToLatLon(int zone, bool northp,
                             double e, double n,
                             double& lat, double& lon) {
    UTMUPS::Reverse(zone, northp, e, n, lat, lon);
}

std::string GeoWrapper::LatLonToMGRS(double lat, double lon, int prec) {
    int zone; bool northp; double e, n;
    UTMUPS::Forward(lat, lon, zone, northp, e, n);
    std::string mgrs;
    MGRS::Forward(zone, northp, e, n, prec, mgrs);
    return mgrs;
}

bool GeoWrapper::MGRSToLatLon(const std::string& mgrs,
                              double& lat, double& lon) {
    int zone, prec; bool northp; double e, n;
    MGRS::Reverse(mgrs, zone, northp, e, n, prec);
    UTMUPS::Reverse(zone, northp, e, n, lat, lon);
    return true;
}

std::string GeoWrapper::LatLonToGEOREF(double lat, double lon, int prec) {
    std::string g;
    Georef::Forward(lat, lon, prec, g);
    return g;
}

void GeoWrapper::GEOREFToLatLon(const std::string& georef,
                                double& lat, double& lon, int& prec) {
    Georef::Reverse(georef, lat, lon, prec);
}

// ================= LOCAL =================
void GeoWrapper::GeodeticToECEF(double lat, double lon, double h,
                                double& X, double& Y, double& Z) {
    Geocentric::WGS84().Forward(lat, lon, h, X, Y, Z);
}

void GeoWrapper::ECEFToGeodetic(double X, double Y, double Z,
                                double& lat, double& lon, double& h) {
    Geocentric::WGS84().Reverse(X, Y, Z, lat, lon, h);
}

void GeoWrapper::GeodeticToENU(double lat0, double lon0, double h0,
                               double lat, double lon, double h,
                               double& e, double& n, double& u) {
    LocalCartesian lc(lat0, lon0, h0);
    lc.Forward(lat, lon, h, e, n, u);
}

void GeoWrapper::ENUToGeodetic(double lat0, double lon0, double h0,
                               double e, double n, double u,
                               double& lat, double& lon, double& h) {
    LocalCartesian lc(lat0, lon0, h0);
    lc.Reverse(e, n, u, lat, lon, h);
}

// ================= NAV =================
void GeoWrapper::RhumbInverse(double lat1, double lon1,
                              double lat2, double lon2,
                              double& s12, double& azi1, double& azi2) {
    Rhumb r(Constants::WGS84_a(), Constants::WGS84_f());
    r.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

void GeoWrapper::CrossTrack(double lat, double lon,
                            double lat1, double lon1,
                            double lat2, double lon2,
                            double& xtrack, double& along) {
    double s12, azi1, azi2;
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
    auto line = geod.Line(lat1, lon1, azi1);

    double s, azi;
    line.Position(lat, lon, s, azi);
    along = s;
    double d;
    geod.Inverse(lat, lon,
                 lat1, lon1,
                 d);
    xtrack = d;
}

bool GeoWrapper::IntersectGeodesics(double lat1, double lon1, double azi1,
                                    double lat2, double lon2, double azi2,
                                    double& lat, double& lon) {
    LocalCartesian lc(lat1, lon1, 0);
    double x1, y1, z1, x2, y2, z2;

    lc.Forward(lat2, lon2, 0, x2, y2, z2);

    double a1 = tan(DegToRad(azi1));
    double a2 = tan(DegToRad(azi2));

    if (fabs(a1 - a2) < 1e-12) return false;

    double xi = (a1 * x2 - y2) / (a1 - a2);
    double yi = a2 * xi;

    lc.Reverse(xi, yi, 0, lat, lon, z1);
    return true;
}

// ================= UTILS =================
double GeoWrapper::DegToRad(double d) {
    return d * Constants::degree();
}

double GeoWrapper::RadToDeg(double r) {
    return r / Constants::degree();
}

double GeoWrapper::NormalizeLon(double lon) {
    return Math::AngNormalize(lon);
}

double GeoWrapper::NormalizeAzimuth(double azi) {
    return Math::AngNormalize(azi);
}

