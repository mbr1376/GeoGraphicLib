#pragma once
#include <string>

namespace libprojection {

/**
 * @brief Represents a reference ellipsoid.
 */
class Ellipsoid {
public:
    /**
     * @brief Construct an ellipsoid.
     * @param a Semi-major axis in meters.
     * @param f Flattening.
     * @param name Optional ellipsoid name.
     */
    Ellipsoid(double a, double f, const std::string& name = "");

    /**
     * @brief Get the semi-major axis.
     * @return Semi-major axis in meters.
     */
    double a() const;

    /**
     * @brief Get the flattening factor.
     * @return Flattening.
     */
    double f() const;

    /**
     * @brief Get the ellipsoid name.
     * @return Name string.
     */
    const std::string& name() const;

    /**
     * @brief International 1924 ellipsoid.
     * @return Ellipsoid instance.
     */
    static Ellipsoid International1924();

    // Common ellipsoids
    static Ellipsoid WGS84();
    static Ellipsoid GRS80();

private:
    double a_;       ///< semi-major axis
    double f_;       ///< flattening
    std::string name_;
};

} // namespace libprojection
