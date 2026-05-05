#pragma once
#include <array>

namespace libprojection {

/**
 * @brief Helmert transformation parameters.
 *
 * Defines a 7-parameter datum shift including translations,
 * rotations, and scale change.
 */
struct Helmert {
    /// translations in meters
    double tx{0};
    double ty{0};
    double tz{0};

    /// rotations in arc-seconds
    double rx{0};
    double ry{0};
    double rz{0};

    /// scale change in parts-per-million
    double s{0};

    /**
     * @brief Check whether the transformation is identity.
     * @return True when all parameters are zero.
     */
    bool isIdentity() const {
        return tx==0 && ty==0 && tz==0 &&
               rx==0 && ry==0 && rz==0 && s==0;
    }
};

} // namespace libprojection
