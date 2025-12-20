#include "libprojection/projection/projectionfacade.h"
#include "libprojection/projection/transversemercator.h"
#include <stdexcept>

namespace libprojection {

Datum ProjectionFacade::datum_ = Datum::WGS84();

ProjectedPoint ProjectionFacade::Forward(const GeoPoint& p,
                                         const std::string& projName,
                                         int utmZone,
                                         bool northp) {
    if(projName == "UTM") {
        if(utmZone == 0)
            utmZone = UTMProjection::LatLonToZone(p.lat, p.lon);
        northp = (p.lat >= 0);
        UTMProjection utm(utmZone, northp, datum_.ellipsoid());
        return utm.Forward(p);
    }
    else if(projName == "WebMercator") {
        // بعداً اضافه شود
        throw std::runtime_error("WebMercator not implemented yet");
    }
    else {
        throw std::runtime_error("Unknown projection: " + projName);
    }
}

GeoPoint ProjectionFacade::Inverse(const ProjectedPoint& p,
                                   const std::string& projName,
                                   int utmZone,
                                   bool northp) {
    if(projName == "UTM") {
        UTMProjection utm(utmZone, northp, datum_.ellipsoid());
        return utm.Inverse(p);
    }
    else if(projName == "WebMercator") {
        throw std::runtime_error("WebMercator not implemented yet");
    }
    else {
        throw std::runtime_error("Unknown projection: " + projName);
    }
}

} // namespace libprojection
