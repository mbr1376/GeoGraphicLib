#pragma once
#include "../core/type.h"
#include "../datum/datum.h"
#include "utmprojection.h"
#include <string>

namespace libprojection {

class ProjectionFacade {
public:
    static ProjectedPoint Forward(const GeoPoint& p,
                                  const std::string& projName = "UTM",
                                  int utmZone = 0,
                                  bool northp = true);

    static GeoPoint Inverse(const ProjectedPoint& p,
                            const std::string& projName = "UTM",
                            int utmZone = 0,
                            bool northp = true);

private:
    static Datum datum_;
};

} // namespace libprojection
