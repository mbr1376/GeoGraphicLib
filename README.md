# GeoGraphicLib

GeoGraphicLib is a small C++ wrapper/project that provides convenient helpers around GeographicLib
and other geospatial utilities. It contains two primary components:

- `WFSLib`: A small client for WFS services (uses libcurl and tinyxml2).
- `GeographicWrapper`: A wrapper around GeographicLib functionality with a `GeoWrapper` class.

This repository is intended as a focused library for geodesy-related helpers and small example
programs that demonstrate how to perform coordinate conversions, geodesic solves, area
calculations, and more.

## Features

- Distance and azimuth calculation (Geodesic / WGS84)
- Polygon area (Geodesic PolygonArea)
- UTM/UPS and MGRS conversions
- Geodesic direct (forward) solving
- Transverse Mercator projection wrappers
- Geocentric and local Cartesian conversions
- Rhumb line inverse (loxodrome)
- Basic geodesic intersection helper (naive sampler — can be improved)

Stubs and planned features (not yet fully implemented): Geoid lookup, gravity & magnetic
models (EGM/WMM/IGRF), triaxial ellipsoid features.

## Building

Requirements:

- C++17 compatible compiler (GCC/Clang)
- CMake >= 3.16
- GeographicLib (development headers & libraries)
- libcurl and tinyxml2 (for `WFSLib`)

On Debian/Ubuntu, install dependencies:

```bash
sudo apt update
sudo apt install build-essential cmake libgeographic-dev libcurl4-openssl-dev libtinyxml2-dev
```

Build:

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

## Example

`GeographicWrapper/example` contains a small demo program that shows UTM/MGRS conversion,
distance/azimuth and polygon area calculation. After building, run:

```bash
./GeographicWrapper/example/example
```

## Development notes

- New features are intended to be added inside a `Ki` toolkit as a separate component and
	then called from `GeoWrapper` (planning ongoing).
- Geoid, gravity and magnetic field tools require external model files — these will be
	loaded optionally at runtime; see `docs/` (planned) for details if/when added.

## Contributing

Contributions welcome — open an issue or a PR. Please follow standard C++ style and add
tests for new functionality.

---

If you'd like, I can also add a more complete `docs/` folder and unit tests (GoogleTest),
and create a small CLI so you can run conversions from the command line. Want me to add those next?
