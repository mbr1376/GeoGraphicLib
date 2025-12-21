#include "libprojection/crs/crs.h"
#include "libprojection/projection/webmercator.h"
#include "libprojection/projection/utmprojection.h"
#include <stdexcept>

namespace libprojection {

CRS::CRS(int epsg,
         CRSKind kind,
         Datum datum,
         std::unique_ptr<Projection> proj)
    : epsg_(epsg),
      kind_(kind),
      datum_(std::move(datum)),
      projection_(std::move(proj)) {}

CRS CRS::FromEPSG(int epsg) {
    // EPSG:4326 - WGS84 Geographic
    if (epsg == 4326) {
        return CRS(
            4326,
            CRSKind::Geographic,
            Datum::WGS84(),
            nullptr
        );
    }

    // EPSG:3857 - WebMercator
    if (epsg == 3857) {
        return CRS(
            3857,
            CRSKind::Projected,
            Datum::WGS84(),
            std::make_unique<WebMercator>(Datum::WGS84().ellipsoid())
        );
    }

    // EPSG:326xx / 327xx - UTM
    if (epsg >= 32601 && epsg <= 32660) {
        int zone = epsg - 32600;
        return CRS(
            epsg,
            CRSKind::Projected,
            Datum::WGS84(),
            std::make_unique<UTMProjection>(zone, true, Datum::WGS84().ellipsoid())
        );
    }

    if (epsg >= 32701 && epsg <= 32760) {
        int zone = epsg - 32700;
        return CRS(
            epsg,
            CRSKind::Projected,
            Datum::WGS84(),
            std::make_unique<UTMProjection>(zone, false, Datum::WGS84().ellipsoid())
        );
    }

    throw std::runtime_error("Unsupported EPSG code");
}

int CRS::epsg() const { return epsg_; }
CRSKind CRS::kind() const { return kind_; }
const Datum& CRS::datum() const { return datum_; }
const Projection* CRS::projection() const { return projection_.get(); }

} // namespace libprojection
