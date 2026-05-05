#pragma once

#include <GeographicLib/Geodesic.hpp>

namespace libprojection {

/**
 * @brief Wrapper around GeographicLib geodesic computations.
 */
class GeodesicEngine {
public:
    /**
     * @brief Construct with WGS84 ellipsoid.
     */
    GeodesicEngine();

    /**
     * @brief Construct with a custom ellipsoid.
     * @param a Semi-major axis in meters.
     * @param f Flattening.
     */
    GeodesicEngine(double a, double f);

    /**
     * @brief Compute the geodesic distance.
     * @param lat1 Latitude of first point in degrees.
     * @param lon1 Longitude of first point in degrees.
     * @param lat2 Latitude of second point in degrees.
     * @param lon2 Longitude of second point in degrees.
     * @return Geodesic distance in meters.
     */
    double Distance(double lat1, double lon1,
                    double lat2, double lon2) const;

    /**
     * @brief Solve the inverse geodesic problem.
     * @param lat1 Latitude of point 1 in degrees.
     * @param lon1 Longitude of point 1 in degrees.
     * @param lat2 Latitude of point 2 in degrees.
     * @param lon2 Longitude of point 2 in degrees.
     * @param s12 Distance between the two points in meters.
     * @param azi1 Forward azimuth at point 1 in degrees.
     * @param azi2 Reverse azimuth at point 2 in degrees.
     */
    void Inverse(double lat1, double lon1,
                 double lat2, double lon2,
                 double& s12,
                 double& azi1,
                 double& azi2) const;

    /**
     * @brief Solve the direct geodesic problem.
     * @param lat1 Latitude of the start point in degrees.
     * @param lon1 Longitude of the start point in degrees.
     * @param azi1 Forward azimuth in degrees.
     * @param s12 Distance to travel in meters.
     * @param lat2 Output latitude of the end point in degrees.
     * @param lon2 Output longitude of the end point in degrees.
     * @param azi2 Output azimuth at the end point in degrees.
     */
    void Direct(double lat1, double lon1,
                double azi1,
                double s12,
                double& lat2,
                double& lon2,
                double& azi2) const;

    /**
     * @brief Compute the midpoint between two geographic points.
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @param latm Output midpoint latitude in degrees.
     * @param lonm Output midpoint longitude in degrees.
     */
    void MidPoint(double lat1, double lon1,
                  double lat2, double lon2,
                  double& latm,
                  double& lonm) const;

private:
    GeographicLib::Geodesic geod_;
};

} // namespace libprojection
