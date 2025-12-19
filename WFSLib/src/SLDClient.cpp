#include "SLDClient.h"
#include <curl/curl.h>
#include <fstream>
#include "tinyxml2.h"

using namespace tinyxml2;

static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

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
bool SLDClient::downloadSLD(const std::string& url,
                                     const std::string& user,
                                     const std::string& password,
                                     const std::string& outputFile)
{
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream file(outputFile, std::ios::binary);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, user.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}
bool SLDClient::parseSLD(const std::string& sldFile)
{
    XMLDocument doc;
    if (doc.LoadFile(sldFile.c_str()) != XML_SUCCESS)
        return false;

    XMLElement* stroke =
        doc.RootElement()
           ->FirstChildElement("NamedLayer")
           ->FirstChildElement("UserStyle")
           ->FirstChildElement("FeatureTypeStyle")
           ->FirstChildElement("Rule")
           ->FirstChildElement("LineSymbolizer")
           ->FirstChildElement("Stroke");

    if (!stroke)
        return false;

    for (XMLElement* css = stroke->FirstChildElement("CssParameter");
         css;
         css = css->NextSiblingElement("CssParameter"))
    {
        const char* name = css->Attribute("name");
        const char* value = css->GetText();

        if (!name || !value) continue;

        if (std::string(name) == "stroke")
            strokeColor_ = value;
        else if (std::string(name) == "stroke-width")
            strokeWidth_ = std::stod(value);
    }

    return true;
}
std::string SLDClient::getLayerName() const { return layerName_; }
const std::vector<SLDColor>& SLDClient::getColors() const { return colors_; }
std::string SLDClient::getStrokeColor() const { return strokeColor_; }
double SLDClient::getStrokeWidth() const { return strokeWidth_; }
const std::vector<std::string>& SLDClient::getPropertyNames() const {
    return propertyNames_;
}
