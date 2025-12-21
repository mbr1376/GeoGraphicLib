#pragma once

#include <memory>
#include <string>
#include "../datum/datum.h"
#include "../projection/projection.h"

namespace libprojection {

enum class CRSKind {
    Geographic,
    Projected
};

class CRS {
public:
    static CRS FromEPSG(int epsg);

    int epsg() const;
    CRSKind kind() const;
    const Datum& datum() const;
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
