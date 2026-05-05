#pragma once
#include "../core/type.h"
#include "../datum/datum.h"
#include "utmprojection.h"
#include <string>

namespace libprojection {

/**
 * @brief Facade for common projection operations.
 *
 * Provides a simplified projection interface for forward and inverse
 * transformations using named projections such as UTM.
 */
class ProjectionFacade {
public:
    /**
     * @brief Project geographic coordinates into projected space.
     * @param p Geographic point to project.
     * @param projName Projection name, e.g. "UTM".
     * @param utmZone UTM zone used for UTM projection.
     * @param northp True for northern hemisphere.
     * @return Projected coordinate.
     */
    static ProjectedPoint Forward(const GeoPoint& p,
                                  const std::string& projName = "UTM",
                                  int utmZone = 0,
                                  bool northp = true);

    /**
     * @brief Unproject a projected coordinate into geographic space.
     * @param p Projected coordinate to invert.
     * @param projName Projection name, e.g. "UTM".
     * @param utmZone UTM zone used for UTM projection.
     * @param northp True for northern hemisphere.
     * @return Geographic coordinate.
     */
    static GeoPoint Inverse(const ProjectedPoint& p,
                            const std::string& projName = "UTM",
                            int utmZone = 0,
                            bool northp = true);

private:
    static Datum datum_;
};

} // namespace libprojection
