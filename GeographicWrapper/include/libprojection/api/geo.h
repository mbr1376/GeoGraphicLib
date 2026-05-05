#pragma once

#include <string>
#include <vector>

#include "libprojection/geodesy/geodesicengine.h"
#include "libprojection/projection/projectionfacade.h"

namespace libprojection {

/// Global geodesic engine used by `Geo` helpers.
static const GeodesicEngine geodesic;

/**
 * @brief Utility wrapper for geodesic, projection, and coordinate operations.
 *
 * `Geo` provides convenience functions for distance and bearing calculations,
 * polygon metrics, coordinate conversions, local ENU/ECEF transforms, UTM/
 * Web Mercator conversions, and EPSG transformations.
 */
class Geo {
public:
    /// @name Geodesic operations
    /// @{

    /**
     * @brief Compute the geodesic distance between two points.
     *
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @return Distance between the points in meters.
     */
    static double Distance(double lat1, double lon1,
                           double lat2, double lon2);

    /**
     * @brief Solve the inverse geodesic problem.
     *
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @param s12 Output distance between the points in meters.
     * @param azi1 Output forward azimuth at the first point in degrees.
     * @param azi2 Output reverse azimuth at the second point in degrees.
     */
    static void Inverse(double lat1, double lon1,
                        double lat2, double lon2,
                        double& s12,
                        double& azi1,
                        double& azi2);

    /**
     * @brief Solve the direct geodesic problem.
     *
     * @param lat1 Latitude of the start point in degrees.
     * @param lon1 Longitude of the start point in degrees.
     * @param azi1 Forward azimuth at the start point in degrees.
     * @param s12 Distance to travel along the geodesic in meters.
     * @param lat2 Output latitude of the end point in degrees.
     * @param lon2 Output longitude of the end point in degrees.
     * @param azi2 Output forward azimuth at the end point in degrees.
     */
    static void Direct(double lat1, double lon1,
                       double azi1, double s12,
                       double& lat2,
                       double& lon2,
                       double& azi2);

    /**
     * @brief Compute the midpoint of two geographic points.
     *
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @param latm Output latitude of the midpoint in degrees.
     * @param lonm Output longitude of the midpoint in degrees.
     */
    static void MidPoint(double lat1, double lon1,
                         double lat2, double lon2,
                         double& latm,
                         double& lonm);

    /// @}

    /// @name Polygon utilities
    /// @{

    /**
     * @brief Compute the area of a polygon defined by latitude/longitude vertices.
     *
     * @param lats Vector of vertex latitudes in degrees.
     * @param lons Vector of vertex longitudes in degrees.
     * @return Polygon area in square meters.
     */
    static double PolygonArea(const std::vector<double>& lats,
                              const std::vector<double>& lons);

    /**
     * @brief Compute the perimeter of a polygon defined by latitude/longitude vertices.
     *
     * @param lats Vector of vertex latitudes in degrees.
     * @param lons Vector of vertex longitudes in degrees.
     * @return Polygon perimeter in meters.
     */
    static double PolygonPerimeter(const std::vector<double>& lats,
                                   const std::vector<double>& lons);

    /**
     * @brief Determine whether a point lies inside a polygon.
     *
     * @param lat Latitude of the test point in degrees.
     * @param lon Longitude of the test point in degrees.
     * @param lats Vector of polygon vertex latitudes in degrees.
     * @param lons Vector of polygon vertex longitudes in degrees.
     * @return True if the point is inside the polygon.
     */
    static bool PointInPolygon(double lat, double lon,
                               const std::vector<double>& lats,
                               const std::vector<double>& lons);

    /// @}

    /// @name Coordinate conversions
    /// @{

    /**
     * @brief Convert geographic coordinates to an MGRS string.
     *
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param prec Precision level (number of digits).
     * @return MGRS coordinate string.
     */
    static std::string LatLonToMGRS(double lat, double lon, int prec);

    /**
     * @brief Convert an MGRS string to geographic coordinates.
     *
     * @param mgrs Input MGRS string.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @return True if the conversion succeeded.
     */
    static bool MGRSToLatLon(const std::string& mgrs,
                             double& lat, double& lon);

    /**
     * @brief Convert geographic coordinates to a GEOREF string.
     *
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param prec Precision level.
     * @return GEOREF coordinate string.
     */
    static std::string LatLonToGEOREF(double lat, double lon, int prec);

    /**
     * @brief Convert a GEOREF string to geographic coordinates.
     *
     * @param georef Input GEOREF string.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param prec Output precision level.
     */
    static void GEOREFToLatLon(const std::string& georef,
                               double& lat, double& lon, int& prec);

    /// @}

    /// @name Local coordinate transforms
    /// @{

    /**
     * @brief Convert geodetic coordinates to ECEF.
     *
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param h Ellipsoidal height in meters.
     * @param X Output ECEF X coordinate.
     * @param Y Output ECEF Y coordinate.
     * @param Z Output ECEF Z coordinate.
     */
    static void GeodeticToECEF(double lat, double lon, double h,
                               double& X, double& Y, double& Z);

    /**
     * @brief Convert ECEF coordinates to geodetic.
     *
     * @param X ECEF X coordinate.
     * @param Y ECEF Y coordinate.
     * @param Z ECEF Z coordinate.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param h Output ellipsoidal height in meters.
     */
    static void ECEFToGeodetic(double X, double Y, double Z,
                               double& lat, double& lon, double& h);

    /**
     * @brief Convert geodetic coordinates to local ENU coordinates.
     *
     * @param lat0 Reference latitude in degrees.
     * @param lon0 Reference longitude in degrees.
     * @param h0 Reference ellipsoidal height in meters.
     * @param lat Latitude of the point in degrees.
     * @param lon Longitude of the point in degrees.
     * @param h Ellipsoidal height of the point in meters.
     * @param e Output east coordinate in meters.
     * @param n Output north coordinate in meters.
     * @param u Output up coordinate in meters.
     */
    static void GeodeticToENU(double lat0, double lon0, double h0,
                              double lat, double lon, double h,
                              double& e, double& n, double& u);

    /**
     * @brief Convert local ENU coordinates to geodetic.
     *
     * @param lat0 Reference latitude in degrees.
     * @param lon0 Reference longitude in degrees.
     * @param h0 Reference ellipsoidal height in meters.
     * @param e East coordinate in meters.
     * @param n North coordinate in meters.
     * @param u Up coordinate in meters.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param h Output ellipsoidal height in meters.
     */
    static void ENUToGeodetic(double lat0, double lon0, double h0,
                              double e, double n, double u,
                              double& lat, double& lon, double& h);

    /// @}

    /// @name Utility functions
    /// @{

    /**
     * @brief Convert degrees to radians.
     *
     * @param d Angle in degrees.
     * @return Angle in radians.
     */
    static double DegToRad(double d);

    /**
     * @brief Convert radians to degrees.
     *
     * @param r Angle in radians.
     * @return Angle in degrees.
     */
    static double RadToDeg(double r);

    /**
     * @brief Normalize longitude to the range [-180, 180].
     *
     * @param lon Longitude in degrees.
     * @return Normalized longitude in degrees.
     */
    static double NormalizeLon(double lon);

    /**
     * @brief Normalize azimuth to the range [0, 360).
     *
     * @param azi Azimuth in degrees.
     * @return Normalized azimuth in degrees.
     */
    static double NormalizeAzimuth(double azi);

    /// @}

    /// @name UTM and web projection helpers
    /// @{

    /**
     * @brief Convert geographic coordinates to UTM.
     *
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param zone Output UTM zone.
     * @param northp Output hemisphere flag.
     * @param e Output easting in meters.
     * @param n Output northing in meters.
     */
    static void LatLonToUTM(double lat, double lon,
                            int& zone, bool& northp,
                            double& e, double& n);

    /**
     * @brief Convert UTM coordinates to geographic coordinates.
     *
     * @param zone UTM zone.
     * @param northp Hemisphere flag.
     * @param e Easting in meters.
     * @param n Northing in meters.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     */
    static void UTMToLatLon(int zone, bool northp,
                            double e, double n,
                            double& lat, double& lon);

    /**
     * @brief Convert geographic coordinates to Web Mercator.
     *
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param x Output Web Mercator X coordinate.
     * @param y Output Web Mercator Y coordinate.
     */
    static void LatLonToWebMercator(double lat, double lon,
                                    double& x, double& y);

    /**
     * @brief Convert Web Mercator coordinates to geographic coordinates.
     *
     * @param x Web Mercator X coordinate.
     * @param y Web Mercator Y coordinate.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     */
    static void WebMercatorToLatLon(double x, double y,
                                    double& lat, double& lon);

    /**
     * @brief Transform coordinates between EPSG projections.
     *
     * @param srcEpsg Source EPSG code.
     * @param dstEpsg Destination EPSG code.
     * @param x Input X coordinate.
     * @param y Input Y coordinate.
     * @param ox Output X coordinate in destination CRS.
     * @param oy Output Y coordinate in destination CRS.
     */
    static void TransformEPSG(int srcEpsg, int dstEpsg,
                              double x, double y,
                              double& ox, double& oy);

    /// @}
};

} // namespace libprojection
