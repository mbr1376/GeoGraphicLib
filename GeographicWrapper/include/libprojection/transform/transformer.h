#pragma once

#include "../crs/crs.h"
#include "../core/type.h"

namespace libprojection {

class Transformer {
public:
    Transformer(const CRS& src, const CRS& dst);

    ProjectedPoint Forward(const GeoPoint& p) const;
    GeoPoint Inverse(const ProjectedPoint& p) const;
        
    ProjectedPoint Transform(const ProjectedPoint& p) const;

private:
     const CRS& src_;
    const CRS& dst_;
};

} // namespace libprojection
