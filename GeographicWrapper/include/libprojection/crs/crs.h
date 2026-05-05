#pragma once

#include <memory>
#include <string>
#include "../datum/datum.h"
#include "../projection/projection.h"

namespace libprojection {

/**
 * @brief Describes the kind of CRS.
 */
enum class CRSKind {
    Geographic, ///< Geographic coordinate system
    Projected   ///< Projected coordinate system
};

/**
 * @brief Coordinate reference system wrapper.
 */
class CRS {
public:
    /**
     * @brief Create a CRS from an EPSG code.
     * @param epsg EPSG identifier.
     * @return CRS instance.
     */
    static CRS FromEPSG(int epsg);

    /**
     * @brief Return the EPSG code.
     * @return EPSG identifier.
     */
    int epsg() const;

    /**
     * @brief Return the coordinate system kind.
     * @return Geographic or projected.
     */
    CRSKind kind() const;

    /**
     * @brief Return the associated datum.
     * @return Datum reference.
     */
    const Datum& datum() const;

    /**
     * @brief Return the projection implementation.
     * @return Projection pointer, or nullptr for geographic CRS.
     */
    const Projection* projection() const;

private:
    CRS(int epsg,
        CRSKind kind,
        Datum datum,
        std::unique_ptr<Projection> proj);

    int epsg_;
    CRSKind kind_;
    Datum datum_;
    std::unique_ptr<Projection> projection_;
};

} // namespace libprojection
