#pragma once
#include "../core/type.h"

namespace libprojection {

/**
 * @brief Base projection interface.
 */
class Projection {
public:
    virtual ~Projection() = default;

    /**
     * @brief Forward projection from geographic to projected coordinates.
     * @param p Geographic coordinate.
     * @return Projected coordinate.
     */
    virtual ProjectedPoint Forward(const GeoPoint& p) const = 0;

    /**
     * @brief Inverse projection from projected to geographic coordinates.
     * @param p Projected coordinate.
     * @return Geographic coordinate.
     */
    virtual GeoPoint Inverse(const ProjectedPoint& p) const = 0;
};

} // namespace libprojection
