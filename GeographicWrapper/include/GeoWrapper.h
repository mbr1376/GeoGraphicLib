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
    // ================== GEODESIC CORE ==================
    static double Distance(double lat1, double lon1, double lat2, double lon2);

    static void Inverse(double lat1, double lon1,
                        double lat2, double lon2,
                        double& s12, double& azi1, double& azi2);

    static void Direct(double lat1, double lon1, double azi1, double s12,
                       double& lat2, double& lon2, double& azi2);

    static void MidPoint(double lat1, double lon1,
                         double lat2, double lon2,
                         double& latm, double& lonm);

    // ================== POLYGON / GIS ==================
    static double PolygonArea(const std::vector<double>& lats,
                              const std::vector<double>& lons);

    static double PolygonPerimeter(const std::vector<double>& lats,
                                   const std::vector<double>& lons);

    static bool PointInPolygon(double lat, double lon,
                               const std::vector<double>& lats,
                               const std::vector<double>& lons);

    // ================== COORD SYSTEMS ==================
    static void LatLonToUTM(double lat, double lon,
                            int& zone, bool& northp,
                            double& e, double& n);

    static void UTMToLatLon(int zone, bool northp,
                            double e, double n,
                            double& lat, double& lon);

    static std::string LatLonToMGRS(double lat, double lon, int prec = 5);
    static bool MGRSToLatLon(const std::string& mgrs, double& lat, double& lon);

    static std::string LatLonToGEOREF(double lat, double lon, int prec);
    static void GEOREFToLatLon(const std::string& georef,
                               double& lat, double& lon, int& prec);

    // ================== GEOCENTRIC / LOCAL ==================
    static void GeodeticToECEF(double lat, double lon, double h,
                               double& X, double& Y, double& Z);

    static void ECEFToGeodetic(double X, double Y, double Z,
                               double& lat, double& lon, double& h);

    static void GeodeticToENU(double lat0, double lon0, double h0,
                              double lat, double lon, double h,
                              double& e, double& n, double& u);

    static void ENUToGeodetic(double lat0, double lon0, double h0,
                              double e, double n, double u,
                              double& lat, double& lon, double& h);

    // ================== NAVIGATION ==================
    static void RhumbInverse(double lat1, double lon1,
                             double lat2, double lon2,
                             double& s12, double& azi1, double& azi2);

    static void CrossTrack(double lat, double lon,
                           double lat1, double lon1,
                           double lat2, double lon2,
                           double& xtrack, double& along);

    static bool IntersectGeodesics(double lat1, double lon1, double azi1,
                                   double lat2, double lon2, double azi2,
                                   double& lat, double& lon);

    // ================== UTILS ==================
    static double DegToRad(double d);
    static double RadToDeg(double r);
    static double NormalizeLon(double lon);
    static double NormalizeAzimuth(double azi);

    private:
    Tool tool = Tool::WGS84;

};

