#include "SLDClient.h"
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

// ---------------- write callback ----------------
static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// ---------------- download without auth ----------------
bool SLDClient::downloadSLD(const std::string& url,
                            const std::string& outputFile)
{
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream file(outputFile, std::ios::binary);
    if (!file.is_open()) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

// ---------------- download with auth ----------------
bool SLDClient::downloadSLD(const std::string& url,
                            const std::string& user,
                            const std::string& password,
                            const std::string& outputFile)
{
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream file(outputFile, std::ios::binary);
    if (!file.is_open()) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, user.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

// ---------------- parse SLD ----------------
bool SLDClient::parseSLD(const std::string& sldFile)
{
    colors_.clear();

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(sldFile.c_str()) != XML_SUCCESS)
        return false;

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root) return false;

    // extract layer name
    tinyxml2::XMLElement* namedLayer = root->FirstChildElement("NamedLayer");
    if (namedLayer) {
        tinyxml2::XMLElement* nameEl = namedLayer->FirstChildElement("Name");
        if (nameEl && nameEl->GetText())
            layerName_ = nameEl->GetText();
    }

    // extract CSS parameters recursively
    extractCssParameters(root, "");

    return true;
}

void SLDClient::downloadIcon(const std::string &url, const std::string &outputFile)
{
    CURL* curl = curl_easy_init();
    if (!curl) return;

    std::ofstream file(outputFile, std::ios::binary);
    if (!file.is_open()) return;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
        std::cout << "✅ Icon downloaded to: " << outputFile << "\n";
    } else {
        std::cout << "❌ Failed to download icon from: " << url << "\n";
    }
}

// ---------------- recursive extraction ----------------
void SLDClient::extractCssParameters(tinyxml2::XMLElement* element,
                                     const std::string& prefix)
{
    if (!element) return;

    std::string elName = element->Name();

    // ✅ استخراج CssParameter
    if (elName == "CssParameter") {
        const char* name = element->Attribute("name");
        const char* value = element->GetText();

        if (name && value) {
            std::string type = prefix + name;
            colors_.push_back({type, value});

            if (std::string(name) == "stroke")
                strokeColor_ = value;
            else if (std::string(name) == "stroke-width")
                strokeWidth_ = std::stod(value);
        }
    }

    // ✅ استخراج PropertyName
    if (elName == "ogc:PropertyName" || elName == "PropertyName") {
        const char* value = element->GetText();
        if (value)
            propertyNames_.push_back(value);
    }

    // ✅ استخراج ExternalGraphic و دانلود آیکن
    if (elName == "ExternalGraphic") {
        const char* url = element->FirstChildElement("OnlineResource")
        ->Attribute("xlink:href");
        if (url) {
            std::cout << "🔗 Icon found: " << url << "\n";
            std::string iconFileName = "icon_" + std::string(url).substr(std::string(url).find_last_of("/") + 1);
            downloadIcon(url, iconFileName);
        }
    }

    // recurse into children
    for (tinyxml2::XMLElement* child = element->FirstChildElement();
         child; child = child->NextSiblingElement())
    {
        extractCssParameters(child, prefix);
    }

}

// ---------------- getters ----------------
std::string SLDClient::getLayerName() const { return layerName_; }
const std::vector<SLDColor>& SLDClient::getColors() const { return colors_; }
std::string SLDClient::getStrokeColor() const { return strokeColor_; }
double SLDClient::getStrokeWidth() const { return strokeWidth_; }
const std::vector<std::string>& SLDClient::getPropertyNames() const {
    return propertyNames_;
}
