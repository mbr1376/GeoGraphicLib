#pragma once

#include "../crs/crs.h"
#include "../core/type.h"

namespace libprojection {

/**
 * @brief Transformer for converting between coordinate reference systems.
 */
class Transformer {
public:
    /**
     * @brief Construct a transformer between source and destination CRS.
     * @param src Source coordinate reference system.
     * @param dst Destination coordinate reference system.
     */
    Transformer(const CRS& src, const CRS& dst);

    /**
     * @brief Project a geographic point from source CRS to destination CRS.
     * @param p Geographic coordinate.
     * @return Projected coordinate in destination CRS.
     */
    ProjectedPoint Forward(const GeoPoint& p) const;

    /**
     * @brief Inverse-project a projected point from destination CRS to source CRS.
     * @param p Projected coordinate.
     * @return Geographic coordinate in source CRS.
     */
    GeoPoint Inverse(const ProjectedPoint& p) const;
        
    /**
     * @brief Transform a projected point from source CRS to destination CRS.
     * @param p Projected coordinate in source CRS.
     * @return Projected coordinate in destination CRS.
     */
    ProjectedPoint Transform(const ProjectedPoint& p) const;

private:
     const CRS& src_;
    const CRS& dst_;
};

} // namespace libprojection
