#pragma once
#include <GeographicLib/Geodesic.hpp>
#include <vector>
enum CoordinateSystem {
    WGS84,
    UTM,
    UPS,
    MGRS,
    EGM,
    WMM,
    IGRF
};
class GeoWrapper {
public:
    explicit GeoWrapper(CoordinateSystem cs = WGS84);
    // فاصله بین دو نقطه (lat1, lon1) و (lat2, lon2)
    static double Distance(double lat1, double lon1, double lat2, double lon2);

    // زاویه اولیه و نهایی مسیر بین دو نقطه
    static void Azimuth(double lat1, double lon1, double lat2, double lon2,
                        double& azi1, double& azi2);

    // مساحت چندضلعی روی زمین
    static double polygonArea(const std::vector<double>& lats, const std::vector<double>& lons);
private:
    CoordinateSystem coordSystem;
    const GeographicLib::Geodesic& geod ; // استفاده از WGS84 به عنوان سیستم مختصات پیش‌فرض

};
