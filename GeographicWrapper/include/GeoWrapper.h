#pragma once
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/TransverseMercator.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <string>
#include <vector>

class GeoWrapper {
public:
    explicit GeoWrapper();
    ~GeoWrapper()= default;
    enum class Tool {
        WGS84,
        UTMUPS,
        MGRS,
        TransverseMercator,
        Geocentric,
        LocalCartesian,
        Rhumb,
        Intersect,
        TriaxialStub
    };

    // Mode
    void setTool(Tool t) { tool = t; }
    Tool getTool() const { return tool; }
    // فاصله بین دو نقطه (lat1, lon1) و (lat2, lon2)
    static double Distance(double lat1, double lon1, double lat2, double lon2);

    // زاویه اولیه و نهایی مسیر بین دو نقطه
    static void Azimuth(double lat1, double lon1, double lat2, double lon2,
                        double& azi1, double& azi2);

    // مساحت چندضلعی روی زمین
    static double polygonArea(const std::vector<double>& lats, const std::vector<double>& lons);
    static std::string latLonToGEOREF (double lon, double  lat,  int prec);
    static void decodeGEOREF(std::string georef,double& lat,double& lon,  int& prec);
    // UTM/UPS conversions
    static void LatLonToUTM(double lat, double lon, int& zone, bool& northp,
                            double& easting, double& northing);
    static void UTMToLatLon(int zone, bool northp, double easting, double northing,
                            double& lat, double& lon);

    // MGRS conversions
    static std::string LatLonToMGRS(double lat, double lon, int precision = 5);
    static bool MGRSToLatLon(const std::string& mgrs, double& lat, double& lon);

    // Geodesic direct
    static void GeodDirect(double lat1, double lon1, double azi1, double s12,
                           double& lat2, double& lon2, double& azi2);

    // Transverse Mercator (forward/inverse) using the simple interface
    static void TMForward(double lat, double lon, double lon0, double& x, double& y);
    static void TMInverse(double x, double y, double lon0, double& lat, double& lon);

    // Geocentric/local conversions
    static void GeodeticToGeocentric(double lat, double lon, double h,
                                     double& X, double& Y, double& Z);
    static void GeocentricToGeodetic(double X, double Y, double Z,
                                     double& lat, double& lon, double& h);

    // Local cartesian (local origin)
    static void GeodeticToLocalCartesian(double lat0, double lon0, double h0,
                                         double lat, double lon, double h,
                                         double& x, double& y, double& z);
    static void LocalCartesianToGeodetic(double lat0, double lon0, double h0,
                                         double x, double y, double z,
                                         double& lat, double& lon, double& h);

    // Rhumb line (loxodrome) helpers
    static void RhumbInverse(double lat1, double lon1, double lat2, double lon2,
                             double& s12, double& azi1, double& azi2);

    // Intersection of two geodesics (simple wrapper)
    static bool IntersectGeodesics(double lat1, double lon1, double azi1,
                                   double lat2, double lon2, double azi2,
                                   double& lat, double& lon);
private:
    Tool tool = Tool::WGS84;

};

