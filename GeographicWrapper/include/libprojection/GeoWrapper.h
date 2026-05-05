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

/**
 * @brief Wrapper for GeographicLib projections and geodesic calculations.
 *
 * This class exposes a simplified interface for distance, coordinate
 * transformations, polygon utilities, and navigation routines.
 */
class GeoWrapper {
public:
    explicit GeoWrapper();
    ~GeoWrapper() = default;

    /**
     * @brief Geographic computation tool selection.
     */
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

    /**
     * @brief Set the active geographic tool.
     * @param t Tool value to select.
     */
    void setTool(Tool t) { tool = t; }

    /**
     * @brief Get the active geographic tool.
     * @return Currently selected tool.
     */
    Tool getTool() const { return tool; }

    // ================== GEODESIC CORE ==================

    /**
     * @brief Compute the geodesic distance between two coordinates.
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @return Distance in meters.
     */
    static double Distance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Solve the inverse geodesic problem.
     * @param lat1 Latitude of point 1 in degrees.
     * @param lon1 Longitude of point 1 in degrees.
     * @param lat2 Latitude of point 2 in degrees.
     * @param lon2 Longitude of point 2 in degrees.
     * @param s12 Output distance between points in meters.
     * @param azi1 Output forward azimuth at point 1 in degrees.
     * @param azi2 Output reverse azimuth at point 2 in degrees.
     */
    static void Inverse(double lat1, double lon1,
                        double lat2, double lon2,
                        double& s12, double& azi1, double& azi2);

    /**
     * @brief Solve the direct geodesic problem.
     * @param lat1 Latitude of the start point in degrees.
     * @param lon1 Longitude of the start point in degrees.
     * @param azi1 Forward azimuth at the start point in degrees.
     * @param s12 Distance to travel from the start point in meters.
     * @param lat2 Output latitude of the end point in degrees.
     * @param lon2 Output longitude of the end point in degrees.
     * @param azi2 Output azimuth at the end point in degrees.
     */
    static void Direct(double lat1, double lon1, double azi1, double s12,
                       double& lat2, double& lon2, double& azi2);

    /**
     * @brief Compute the midpoint between two geographic coordinates.
     * @param lat1 Latitude of point 1 in degrees.
     * @param lon1 Longitude of point 1 in degrees.
     * @param lat2 Latitude of point 2 in degrees.
     * @param lon2 Longitude of point 2 in degrees.
     * @param latm Output midpoint latitude in degrees.
     * @param lonm Output midpoint longitude in degrees.
     */
    static void MidPoint(double lat1, double lon1,
                         double lat2, double lon2,
                         double& latm, double& lonm);

    // ================== POLYGON / GIS ==================

    /**
     * @brief Compute the area of a polygon defined by latitude/longitude vertices.
     * @param lats Vector of vertex latitudes in degrees.
     * @param lons Vector of vertex longitudes in degrees.
     * @return Polygon area in square meters.
     */
    static double PolygonArea(const std::vector<double>& lats,
                              const std::vector<double>& lons);

    /**
     * @brief Compute the perimeter of a polygon defined by latitude/longitude vertices.
     * @param lats Vector of vertex latitudes in degrees.
     * @param lons Vector of vertex longitudes in degrees.
     * @return Polygon perimeter in meters.
     */
    static double PolygonPerimeter(const std::vector<double>& lats,
                                   const std::vector<double>& lons);

    /**
     * @brief Test whether a point lies inside a polygon.
     * @param lat Latitude of the point in degrees.
     * @param lon Longitude of the point in degrees.
     * @param lats Vector of polygon vertex latitudes in degrees.
     * @param lons Vector of polygon vertex longitudes in degrees.
     * @return True if the point is inside the polygon.
     */
    static bool PointInPolygon(double lat, double lon,
                               const std::vector<double>& lats,
                               const std::vector<double>& lons);

    // ================== COORD SYSTEMS ==================

    /**
     * @brief Convert latitude/longitude to UTM coordinates.
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param zone Output UTM zone.
     * @param northp Output hemisphere flag (true for northern hemisphere).
     * @param e Output easting in meters.
     * @param n Output northing in meters.
     */
    static void LatLonToUTM(double lat, double lon,
                            int& zone, bool& northp,
                            double& e, double& n);

    /**
     * @brief Convert UTM coordinates to latitude/longitude.
     * @param zone UTM zone.
     * @param northp Hemisphere flag (true for northern hemisphere).
     * @param e Easting in meters.
     * @param n Northing in meters.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     */
    static void UTMToLatLon(int zone, bool northp,
                            double e, double n,
                            double& lat, double& lon);

    /**
     * @brief Convert latitude/longitude to an MGRS string.
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param prec Precision level (1-5).
     * @return MGRS coordinate string.
     */
    static std::string LatLonToMGRS(double lat, double lon, int prec = 5);

    /**
     * @brief Convert an MGRS string to latitude/longitude.
     * @param mgrs MGRS coordinate string.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @return True if conversion succeeded.
     */
    static bool MGRSToLatLon(const std::string& mgrs, double& lat, double& lon);

    /**
     * @brief Convert latitude/longitude to GEOREF coordinates.
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param prec Precision level.
     * @return GEOREF coordinate string.
     */
    static std::string LatLonToGEOREF(double lat, double lon, int prec);

    /**
     * @brief Convert GEOREF coordinates to latitude/longitude.
     * @param georef GEOREF coordinate string.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param prec Output precision used.
     */
    static void GEOREFToLatLon(const std::string& georef,
                               double& lat, double& lon, int& prec);

    // ================== GEOCENTRIC / LOCAL ==================

    /**
     * @brief Convert geodetic coordinates to ECEF.
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @param h Height above ellipsoid in meters.
     * @param X Output ECEF X coordinate in meters.
     * @param Y Output ECEF Y coordinate in meters.
     * @param Z Output ECEF Z coordinate in meters.
     */
    static void GeodeticToECEF(double lat, double lon, double h,
                               double& X, double& Y, double& Z);

    /**
     * @brief Convert ECEF coordinates to geodetic coordinates.
     * @param X ECEF X coordinate in meters.
     * @param Y ECEF Y coordinate in meters.
     * @param Z ECEF Z coordinate in meters.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param h Output height above ellipsoid in meters.
     */
    static void ECEFToGeodetic(double X, double Y, double Z,
                               double& lat, double& lon, double& h);

    /**
     * @brief Convert geodetic coordinates to local ENU coordinates.
     * @param lat0 Reference latitude in degrees.
     * @param lon0 Reference longitude in degrees.
     * @param h0 Reference height above ellipsoid in meters.
     * @param lat Latitude of the point in degrees.
     * @param lon Longitude of the point in degrees.
     * @param h Height of the point above ellipsoid in meters.
     * @param e Output east coordinate in meters.
     * @param n Output north coordinate in meters.
     * @param u Output up coordinate in meters.
     */
    static void GeodeticToENU(double lat0, double lon0, double h0,
                              double lat, double lon, double h,
                              double& e, double& n, double& u);

    /**
     * @brief Convert local ENU coordinates to geodetic coordinates.
     * @param lat0 Reference latitude in degrees.
     * @param lon0 Reference longitude in degrees.
     * @param h0 Reference height above ellipsoid in meters.
     * @param e East coordinate in meters.
     * @param n North coordinate in meters.
     * @param u Up coordinate in meters.
     * @param lat Output latitude in degrees.
     * @param lon Output longitude in degrees.
     * @param h Output height above ellipsoid in meters.
     */
    static void ENUToGeodetic(double lat0, double lon0, double h0,
                              double e, double n, double u,
                              double& lat, double& lon, double& h);

    // ================== NAVIGATION ==================

    /**
     * @brief Solve the inverse Rhumb line problem.
     * @param lat1 Latitude of point 1 in degrees.
     * @param lon1 Longitude of point 1 in degrees.
     * @param lat2 Latitude of point 2 in degrees.
     * @param lon2 Longitude of point 2 in degrees.
     * @param s12 Output rhumb line distance in meters.
     * @param azi1 Output forward azimuth in degrees.
     * @param azi2 Output reverse azimuth in degrees.
     */
    static void RhumbInverse(double lat1, double lon1,
                             double lat2, double lon2,
                             double& s12, double& azi1, double& azi2);

    /**
     * @brief Compute the cross-track error from a great circle path.
     * @param lat Latitude of the point in degrees.
     * @param lon Longitude of the point in degrees.
     * @param lat1 Latitude of the start point in degrees.
     * @param lon1 Longitude of the start point in degrees.
     * @param lat2 Latitude of the end point in degrees.
     * @param lon2 Longitude of the end point in degrees.
     * @param xtrack Output cross-track distance in meters.
     * @param along Output along-track distance in meters.
     */
    static void CrossTrack(double lat, double lon,
                           double lat1, double lon1,
                           double lat2, double lon2,
                           double& xtrack, double& along);

    /**
     * @brief Intersect two geodesics and compute their intersection point.
     * @param lat1 Latitude of the first geodesic origin in degrees.
     * @param lon1 Longitude of the first geodesic origin in degrees.
     * @param azi1 Azimuth of the first geodesic in degrees.
     * @param lat2 Latitude of the second geodesic origin in degrees.
     * @param lon2 Longitude of the second geodesic origin in degrees.
     * @param azi2 Azimuth of the second geodesic in degrees.
     * @param lat Output intersection latitude in degrees.
     * @param lon Output intersection longitude in degrees.
     * @return True if an intersection point was found.
     */
    static bool IntersectGeodesics(double lat1, double lon1, double azi1,
                                   double lat2, double lon2, double azi2,
                                   double& lat, double& lon);

    // ================== UTILS ==================

    /**
     * @brief Convert degrees to radians.
     * @param d Angle in degrees.
     * @return Angle in radians.
     */
    static double DegToRad(double d);

    /**
     * @brief Convert radians to degrees.
     * @param r Angle in radians.
     * @return Angle in degrees.
     */
    static double RadToDeg(double r);

    /**
     * @brief Normalize longitude to the range [-180, 180].
     * @param lon Longitude in degrees.
     * @return Normalized longitude in degrees.
     */
    static double NormalizeLon(double lon);

    /**
     * @brief Normalize an azimuth to the range [0, 360).
     * @param azi Azimuth in degrees.
     * @return Normalized azimuth in degrees.
     */
    static double NormalizeAzimuth(double azi);

private:
    Tool tool = Tool::WGS84;
};

