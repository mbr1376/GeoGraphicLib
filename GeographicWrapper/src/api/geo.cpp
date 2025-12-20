#include "libprojection/api/geo.h"

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/PolygonArea.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/Georef.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Math.hpp>
#include "libprojection/projection/utmprojection.h"
#include "libprojection/datum/datum.h"

using namespace GeographicLib;

namespace libprojection {

static const Geodesic& geod = Geodesic::WGS84();

// ================= GEODESIC =================
double Geo::Distance(double lat1, double lon1,
                     double lat2, double lon2) {
    double s12;
    return geodesic.Distance(lat1, lon1, lat2, lon2);;
}

void Geo::Inverse(double lat1, double lon1,
                  double lat2, double lon2,
                  double& s12,
                  double& azi1,
                  double& azi2) {
        geodesic.Inverse(lat1, lon1, lat2, lon2, s12, azi1, azi2);
}

void Geo::Direct(double lat1, double lon1,
                 double azi1, double s12,
                 double& lat2,
                 double& lon2,
                 double& azi2) {
        geodesic.Direct(lat1, lon1, azi1, s12, lat2, lon2, azi2);
}

void Geo::MidPoint(double lat1, double lon1,
                   double lat2, double lon2,
                   double& latm,
                   double& lonm) {
        geodesic.MidPoint(lat1, lon1, lat2, lon2, latm, lonm);
}

// ================= POLYGON =================
double Geo::PolygonArea(const std::vector<double>& lats,
                        const std::vector<double>& lons) {
    GeographicLib::PolygonArea p(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        p.AddPoint(lats[i], lons[i]);

    double per, area;
    p.Compute(false, true, per, area);
    return area;
}

double Geo::PolygonPerimeter(const std::vector<double>& lats,
                             const std::vector<double>& lons) {
    GeographicLib::PolygonArea p(geod, false);
    for (size_t i = 0; i < lats.size(); ++i)
        p.AddPoint(lats[i], lons[i]);

    double per, area;
    p.Compute(false, true, per, area);
    return per;
}

bool Geo::PointInPolygon(double lat, double lon,
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

std::string Geo::LatLonToMGRS(double lat, double lon, int prec) {
    int zone;
    bool northp;
    double e, n;

    UTMUPS::Forward(lat, lon, zone, northp, e, n);

    std::string mgrs;
    MGRS::Forward(zone, northp, e, n, prec, mgrs);
    return mgrs;
}

bool Geo::MGRSToLatLon(const std::string& mgrs,
                       double& lat, double& lon) {
    int zone, prec;
    bool northp;
    double e, n;

    MGRS::Reverse(mgrs, zone, northp, e, n, prec);
    UTMUPS::Reverse(zone, northp, e, n, lat, lon);
    return true;
}

std::string Geo::LatLonToGEOREF(double lat, double lon, int prec) {
    std::string g;
    Georef::Forward(lat, lon, prec, g);
    return g;
}

void Geo::GEOREFToLatLon(const std::string& georef,
                         double& lat, double& lon, int& prec) {
    Georef::Reverse(georef, lat, lon, prec);
}

// ================= LOCAL =================
void Geo::GeodeticToECEF(double lat, double lon, double h,
                         double& X, double& Y, double& Z) {
    Geocentric::WGS84().Forward(lat, lon, h, X, Y, Z);
}

void Geo::ECEFToGeodetic(double X, double Y, double Z,
                         double& lat, double& lon, double& h) {
    Geocentric::WGS84().Reverse(X, Y, Z, lat, lon, h);
}

void Geo::GeodeticToENU(double lat0, double lon0, double h0,
                        double lat, double lon, double h,
                        double& e, double& n, double& u) {
    LocalCartesian lc(lat0, lon0, h0);
    lc.Forward(lat, lon, h, e, n, u);
}

void Geo::ENUToGeodetic(double lat0, double lon0, double h0,
                        double e, double n, double u,
                        double& lat, double& lon, double& h) {
    LocalCartesian lc(lat0, lon0, h0);
    lc.Reverse(e, n, u, lat, lon, h);
}

// ================= UTILS =================
double Geo::DegToRad(double d) {
    return d * Constants::degree();
}

double Geo::RadToDeg(double r) {
    return r / Constants::degree();
}

double Geo::NormalizeLon(double lon) {
    return Math::AngNormalize(lon);
}

double Geo::NormalizeAzimuth(double azi) {
    return Math::AngNormalize(azi);
}
        void Geo::LatLonToUTM(double lat, double lon,
                          int& zone, bool& northp,
                          double& e, double& n) {
        libprojection::GeoPoint p{lat, lon};
        libprojection::ProjectedPoint proj = ProjectionFacade::Forward(p, "UTM");
        e = proj.x;
        n = proj.y;
        zone = UTMProjection::LatLonToZone(lat, lon);
        northp = (lat >= 0);
    }

    void Geo::UTMToLatLon(int zone, bool northp,
                          double e, double n,
                          double& lat, double& lon) {
        libprojection::ProjectedPoint p{e, n};
        libprojection::GeoPoint g = ProjectionFacade::Inverse(p, "UTM", zone, northp);
        lat = g.lat;
        lon = g.lon;
    }

    void Geo::LatLonToWebMercator(double lat, double lon,
                                  double& x, double& y) {
        libprojection::GeoPoint p{lat, lon};
        libprojection::ProjectedPoint proj = ProjectionFacade::Forward(p, "WebMercator");
        x = proj.x;
        y = proj.y;
    }

    void Geo::WebMercatorToLatLon(double x, double y,
                                  double& lat, double& lon) {
        libprojection::ProjectedPoint p{x, y};
        libprojection::GeoPoint g = ProjectionFacade::Inverse(p, "WebMercator");
        lat = g.lat;
        lon = g.lon;
    }



} // namespace libprojection
