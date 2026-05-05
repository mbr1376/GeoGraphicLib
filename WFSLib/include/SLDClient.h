#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>

/**
 * @brief Color entry extracted from an SLD document.
 */
struct SLDColor {
    std::string type;   ///< fill, stroke, or text-fill
    std::string value;  ///< color value in #RRGGBB format
};

/**
 * @brief Client for downloading and parsing SLD styles.
 */
class SLDClient {
public:
    /**
     * @brief Download an SLD document from a URL.
     * @param url Source URL.
     * @param outputFile Path where the downloaded SLD will be saved.
     * @return True on success.
     */
    bool downloadSLD(const std::string& url,
                     const std::string& outputFile);

    /**
     * @brief Download an SLD document using HTTP authentication.
     * @param url Source URL.
     * @param user Username for authentication.
     * @param password Password for authentication.
     * @param outputFile Path where the downloaded SLD will be saved.
     * @return True on success.
     */
    bool downloadSLD(const std::string& url,
                     const std::string& user,
                     const std::string& password,
                     const std::string& outputFile);

    /**
     * @brief Parse an SLD document from a file.
     * @param sldFile Local SLD file path.
     * @return True if parsing succeeds.
     */
    bool parseSLD(const std::string& sldFile);

    /**
     * @brief Download an icon from a URL.
     * @param url Source icon URL.
     * @param outputFile Local output file path.
     */
    void downloadIcon(const std::string& url, const std::string& outputFile);

    /**
     * @brief Get the parsed layer name from the SLD.
     * @return Layer name.
     */
    std::string getLayerName() const;

    /**
     * @brief Get the parsed style colors.
     * @return Color definitions from the SLD.
     */
    const std::vector<SLDColor>& getColors() const;

    /**
     * @brief Get the primary stroke color.
     * @return Stroke color string.
     */
    std::string getStrokeColor() const;

    /**
     * @brief Get the stroke width extracted from the SLD.
     * @return Stroke width in pixels.
     */
    double getStrokeWidth() const;

    /**
     * @brief Get property names referenced in the SLD.
     * @return List of property name strings.
     */
    const std::vector<std::string>& getPropertyNames() const;
private:
    /**
     * @brief Extract CSS parameters from an XML element.
     * @param element Element to parse.
     * @param prefix Prefix used for CSS property names.
     */
    void extractCssParameters(struct tinyxml2::XMLElement* element,
                              const std::string& prefix);

    std::string layerName_;
    std::vector<SLDColor> colors_;
    std::vector<std::string> propertyNames_;
    std::string strokeColor_;
    double strokeWidth_ = 0.0;
};

