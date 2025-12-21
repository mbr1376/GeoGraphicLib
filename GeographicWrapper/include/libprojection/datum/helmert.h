#pragma once
#include <array>

namespace libprojection {

struct Helmert {
    // translations (meters)
    double tx{0}, ty{0}, tz{0};

    // rotations (arc-seconds)
    double rx{0}, ry{0}, rz{0};

    // scale (ppm)
    double s{0};

    bool isIdentity() const {
        return tx==0 && ty==0 && tz==0 &&
               rx==0 && ry==0 && rz==0 && s==0;
    }
};

} // namespace libprojection
