#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>

struct SLDColor {
    std::string type;   // fill, stroke, text-fill
    std::string value;  // #RRGGBB
};

class SLDClient {
public:
    // دانلود SLD
    bool downloadSLD(const std::string& url,
                     const std::string& outputFile);

    bool downloadSLD(const std::string& url,
                     const std::string& user,
                     const std::string& password,
                     const std::string& outputFile);

    // parse SLD
    bool parseSLD(const std::string& sldFile);
    void downloadIcon(const std::string& url, const std::string& outputFile);
    // getter
    std::string getLayerName() const;
    const std::vector<SLDColor>& getColors() const;

    std::string getStrokeColor() const;
    double getStrokeWidth() const;
    const std::vector<std::string> &getPropertyNames() const;
private:
    void extractCssParameters(struct tinyxml2::XMLElement* element,
                              const std::string& prefix);

    std::string layerName_;
    std::vector<SLDColor> colors_;
    std::vector<std::string> propertyNames_; // ✅ اضافه شد
    std::string strokeColor_;
    double strokeWidth_ = 0.0;
};

