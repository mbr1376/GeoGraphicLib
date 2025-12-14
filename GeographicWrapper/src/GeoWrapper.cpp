#include "GeoWrapper.h"
#include <GeographicLib/PolygonArea.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/TransverseMercator.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <iostream>

using namespace GeographicLib;

GeoWrapper::GeoWrapper(){}
double GeoWrapper::Distance(double lat1, double lon1, double lat2, double lon2) {
    double s12;
     const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84();
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12; // فاصله بر حسب متر
}

void GeoWrapper::Azimuth(double lat1, double lon1, double lat2, double lon2,
                         double& azi1, double& azi2) {
    double s12;
     const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84();
    geod.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

double GeoWrapper::polygonArea(const std::vector<double>& lats, const std::vector<double>& lons) {
     const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84();
    PolygonArea poly(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        poly.AddPoint(lats[i], lons[i]);
    double perimeter, area;
    poly.Compute(false, true, perimeter, area);
    return area; // متر مربع
}

void GeoWrapper::LatLonToUTM(double lat, double lon, int& zone, bool& northp,
                            double& easting, double& northing) {
    GeographicLib::UTMUPS::Forward(lat, lon, zone, northp, easting, northing);
}

void GeoWrapper::UTMToLatLon(int zone, bool northp, double easting, double northing,
                            double& lat, double& lon) {
    GeographicLib::UTMUPS::Reverse(zone, northp, easting, northing, lat, lon);
}

std::string GeoWrapper::LatLonToMGRS(double lat, double lon, int precision) {
    int zone; bool northp; double easting, northing;
    GeographicLib::UTMUPS::Forward(lat, lon, zone, northp, easting, northing);
    std::string mgrs;
    GeographicLib::MGRS::Forward(zone, northp, easting, northing, precision, mgrs);
    return mgrs;
}

bool GeoWrapper::MGRSToLatLon(const std::string& mgrs, double& lat, double& lon) {
    try {
        int zone; bool northp; double easting, northing; int prec;
        GeographicLib::MGRS::Reverse(mgrs, zone, northp, easting, northing, prec);
        GeographicLib::UTMUPS::Reverse(zone, northp, easting, northing, lat, lon);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "MGRS parse error: " << e.what() << std::endl;
        return false;
    }
}

void GeoWrapper::GeodDirect(double lat1, double lon1, double azi1, double s12,
                           double& lat2, double& lon2, double& azi2) {
    const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84();
    geod.Direct(lat1, lon1, azi1, s12, lat2, lon2, azi2);
}

void GeoWrapper::TMForward(double lat, double lon, double lon0, double& x, double& y) {
    double a = GeographicLib::Constants::WGS84_a();
    double f = GeographicLib::Constants::WGS84_f();
    GeographicLib::TransverseMercator tm(a, f, lon0);
    double gamma, k;
    // TransverseMercator::Forward expects (lon0, lat, lon, x, y, gamma, k)
    tm.Forward(lon0, lat, lon, x, y, gamma, k);
}

void GeoWrapper::TMInverse(double x, double y, double lon0, double& lat, double& lon) {
    double a = GeographicLib::Constants::WGS84_a();
    double f = GeographicLib::Constants::WGS84_f();
    GeographicLib::TransverseMercator tm(a, f, lon0);
    double gamma, k;
    // TransverseMercator::Reverse expects (lon0, x, y, lat, lon, gamma, k)
    tm.Reverse(lon0, x, y, lat, lon, gamma, k);
}

void GeoWrapper::GeodeticToGeocentric(double lat, double lon, double h,
                                     double& X, double& Y, double& Z) {
    GeographicLib::Geocentric earth = GeographicLib::Geocentric::WGS84();
    earth.Forward(lat, lon, h, X, Y, Z);
}

void GeoWrapper::GeocentricToGeodetic(double X, double Y, double Z,
                                     double& lat, double& lon, double& h) {
    GeographicLib::Geocentric earth = GeographicLib::Geocentric::WGS84();
    earth.Reverse(X, Y, Z, lat, lon, h);
}

void GeoWrapper::GeodeticToLocalCartesian(double lat0, double lon0, double h0,
                                         double lat, double lon, double h,
                                         double& x, double& y, double& z) {
    GeographicLib::LocalCartesian proj(lat0, lon0, h0, GeographicLib::Geocentric::WGS84());
    proj.Forward(lat, lon, h, x, y, z);
}

void GeoWrapper::LocalCartesianToGeodetic(double lat0, double lon0, double h0,
                                         double x, double y, double z,
                                         double& lat, double& lon, double& h) {
    GeographicLib::LocalCartesian proj(lat0, lon0, h0, GeographicLib::Geocentric::WGS84());
    proj.Reverse(x, y, z, lat, lon, h);
}

void GeoWrapper::RhumbInverse(double lat1, double lon1, double lat2, double lon2,
                             double& s12, double& azi1, double& azi2) {
    double a = GeographicLib::Constants::WGS84_a();
    double f = GeographicLib::Constants::WGS84_f();
    GeographicLib::Rhumb rh(a, f);
    double s12_local, azi1_local, azi2_local;
    rh.Inverse(lat1, lon1, lat2, lon2, s12_local, azi1_local, azi2_local);
    s12 = s12_local;
    azi1 = azi1_local;
    azi2 = azi2_local;
}

bool GeoWrapper::IntersectGeodesics(double lat1, double lon1, double azi1,
                                   double lat2, double lon2, double azi2,
                                   double& lat, double& lon) {
    const GeographicLib::Geodesic& geod = GeographicLib::Geodesic::WGS84();
    GeographicLib::GeodesicLine l1 = geod.Line(lat1, lon1, azi1);
    // naive sampling along first geodesic to find closest point to second geodesic
    double bestd = 1e300;
    bool found = false;
    for (double s = 0; s < 200000; s += 1000) {
        double latx, lonx, azi;
        l1.Position(s, latx, lonx, azi);
        double s2, azi21, azi12;
        geod.Inverse(latx, lonx, lat2, lon2, s2, azi21, azi12);
        if (s2 < bestd) {
            bestd = s2;
            lat = latx; lon = lonx; found = true;
        }
    }
    return found;
}
