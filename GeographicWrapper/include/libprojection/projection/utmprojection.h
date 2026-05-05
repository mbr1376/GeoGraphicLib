#pragma once
#include "transversemercator.h"

namespace libprojection {

/**
 * @brief UTM projection implementation.
 *
 * Extends TransverseMercator with UTM zone and hemisphere awareness.
 */
class UTMProjection : public TransverseMercator {
public:
    /**
     * @brief Construct a UTM projection.
     * @param zone UTM zone [1..60].
     * @param northp True for northern hemisphere.
     * @param ellipsoid Reference ellipsoid.
     */
    UTMProjection(int zone, bool northp, const Ellipsoid& ellipsoid);

    /**
     * @brief Compute the UTM zone for a latitude/longitude coordinate.
     * @param lat Latitude in degrees.
     * @param lon Longitude in degrees.
     * @return UTM zone number.
     */
    static int LatLonToZone(double lat, double lon);

private:
    int zone_;
    bool northp_;
};

} // namespace libprojection
