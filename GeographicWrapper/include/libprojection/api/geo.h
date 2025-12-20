#pragma once

#include <vector>
#include <string>
#include "libprojection/geodesy/geodesicengine.h"
#include "libprojection/projection/projectionfacade.h"
namespace libprojection {
    static const GeodesicEngine geodesic;
class Geo {
public:
    // ================= GEODESIC =================
    static double Distance(double lat1, double lon1,
                           double lat2, double lon2);

    static void Inverse(double lat1, double lon1,
                        double lat2, double lon2,
                        double& s12,
                        double& azi1,
                        double& azi2);

    static void Direct(double lat1, double lon1,
                       double azi1, double s12,
                       double& lat2,
                       double& lon2,
                       double& azi2);

    static void MidPoint(double lat1, double lon1,
                         double lat2, double lon2,
                         double& latm,
                         double& lonm);

    // ================= POLYGON =================
    static double PolygonArea(const std::vector<double>& lats,
                              const std::vector<double>& lons);

    static double PolygonPerimeter(const std::vector<double>& lats,
                                   const std::vector<double>& lons);

    static bool PointInPolygon(double lat, double lon,
                               const std::vector<double>& lats,
                               const std::vector<double>& lons);

    // ================= COORD =================

    static std::string LatLonToMGRS(double lat, double lon, int prec);

    static bool MGRSToLatLon(const std::string& mgrs,
                             double& lat, double& lon);

    static std::string LatLonToGEOREF(double lat, double lon, int prec);

    static void GEOREFToLatLon(const std::string& georef,
                               double& lat, double& lon, int& prec);

    // ================= LOCAL =================
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

    // ================= UTILS =================
    static double DegToRad(double d);
    static double RadToDeg(double r);
    static double NormalizeLon(double lon);
    static double NormalizeAzimuth(double azi);

        // ================= UTM =================
    static void LatLonToUTM(double lat, double lon,
                            int& zone, bool& northp,
                            double& e, double& n);

    static void UTMToLatLon(int zone, bool northp,
                            double e, double n,
                            double& lat, double& lon);
    
    static void LatLonToWebMercator(double lat, double lon,
                                    double& x, double& y);

    static void WebMercatorToLatLon(double x, double y,
                                    double& lat, double& lon);
};
}
