#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "GeoWrapper.h"

namespace py = pybind11;

PYBIND11_MODULE(pygeowrapper, m) {
    m.doc() = "Python bindings for GeoWrapper (GeographicLib)";

    py::class_<GeoWrapper>(m, "GeoWrapper")
        .def(py::init<>())

        .def_static("distance", &GeoWrapper::Distance)
        .def_static("azimuth", &GeoWrapper::Azimuth)
        .def_static("polygon_area", &GeoWrapper::polygonArea)

        .def_static("latlon_to_utm", &GeoWrapper::LatLonToUTM)
        .def_static("utm_to_latlon", &GeoWrapper::UTMToLatLon)

        .def_static("latlon_to_mgrs", &GeoWrapper::LatLonToMGRS,
                    py::arg("lat"), py::arg("lon"), py::arg("precision") = 5)

        .def_static("mgrs_to_latlon", &GeoWrapper::MGRSToLatLon)

        .def_static("geod_direct", &GeoWrapper::GeodDirect)
        .def_static("tm_forward", &GeoWrapper::TMForward)
        .def_static("tm_inverse", &GeoWrapper::TMInverse)

        .def_static("geodetic_to_geocentric", &GeoWrapper::GeodeticToGeocentric)
        .def_static("geocentric_to_geodetic", &GeoWrapper::GeocentricToGeodetic)

        .def_static("geodetic_to_local", &GeoWrapper::GeodeticToLocalCartesian)
        .def_static("local_to_geodetic", &GeoWrapper::LocalCartesianToGeodetic)

        .def_static("rhumb_inverse", &GeoWrapper::RhumbInverse)
        .def_static("intersect_geodesics", &GeoWrapper::IntersectGeodesics);
}
