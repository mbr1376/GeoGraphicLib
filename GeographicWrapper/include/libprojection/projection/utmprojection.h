#pragma once
#include "transversemercator.h"

namespace libprojection {

class UTMProjection : public TransverseMercator {
public:
    // zone: 1..60, northp: true=Northern Hemisphere
    UTMProjection(int zone, bool northp, const Ellipsoid& ellipsoid);

    static int LatLonToZone(double lat, double lon);

private:
    int zone_;
    bool northp_;
};

} // namespace libprojection
