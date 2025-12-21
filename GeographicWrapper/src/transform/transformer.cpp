#include "libprojection/transform/transformer.h"
#include <stdexcept>

namespace libprojection {

Transformer::Transformer(const CRS& src, const CRS& dst)
    : src_(src), dst_(dst) {}

ProjectedPoint Transformer::Forward(const GeoPoint& p) const {
    // Geographic -> Projected
    if (src_.kind() == CRSKind::Geographic &&
        dst_.kind() == CRSKind::Projected) {
        return dst_.projection()->Forward(p);
    }

    throw std::runtime_error("Unsupported CRS transformation");
}

GeoPoint Transformer::Inverse(const ProjectedPoint& p) const {
    // Projected -> Geographic
    if (src_.kind() == CRSKind::Projected &&
        dst_.kind() == CRSKind::Geographic) {
        return src_.projection()->Inverse(p);
    }

    throw std::runtime_error("Unsupported CRS transformation");
}
ProjectedPoint Transformer::Transform(const ProjectedPoint& p) const {
    // Projected → Projected
    if (src_.kind() == CRSKind::Projected &&
        dst_.kind() == CRSKind::Projected) {

        // 1️⃣ src projected → geographic
        GeoPoint g = src_.projection()->Inverse(p);

        // 2️⃣ geographic → dst projected
        return dst_.projection()->Forward(g);
    }

    // Geographic → Geographic (فعلاً passthrough)
    if (src_.kind() == CRSKind::Geographic &&
        dst_.kind() == CRSKind::Geographic) {
        return { p.x, p.y }; // rarely used
    }

    throw std::runtime_error("Unsupported CRS transformation");
}
} // namespace libprojection
