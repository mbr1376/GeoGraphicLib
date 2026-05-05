#pragma once
#include "helmert.h"

namespace libprojection {

/**
 * @brief Three-dimensional vector.
 */
struct Vec3 {
    double x; ///< X component
    double y; ///< Y component
    double z; ///< Z component
};

/**
 * @brief Applies Helmert datum transformation parameters.
 */
class HelmertTransform {
public:
    /**
     * @brief Apply a Helmert transformation to a 3D vector.
     * @param v Input vector.
     * @param h Helmert transformation parameters.
     * @return Transformed vector.
     */
    static Vec3 Apply(const Vec3& v, const Helmert& h);
};

} // namespace libprojection
