#include "WFSClient.h"
#include <iostream>
#include <curl/curl.h>
#include <tinyxml2.h>

using namespace tinyxml2;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

WFSClient::WFSClient(const std::string& baseUrl, const std::string& user, const std::string& password)
    : baseUrl(baseUrl), user(user), password(password) {}

std::string WFSClient::httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        if (!user.empty())
            curl_easy_setopt(curl, CURLOPT_USERPWD, (user + ":" + password).c_str());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

std::vector<WFSLayer> WFSClient::getLayers() {
    std::string url = baseUrl + "?service=WFS&acceptversions=2.0.0&request=GetCapabilities";
    std::string xml = httpGet(url);
    std::vector<WFSLayer> layers;

    XMLDocument doc;
    if (doc.Parse(xml.c_str()) != XML_SUCCESS) {
        std::cerr << "Error parsing WFS capabilities XML\n";
        return layers;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* featureTypeList = root->FirstChildElement("wfs:FeatureTypeList");
    if (!featureTypeList)
        featureTypeList = root->FirstChildElement("FeatureTypeList");

    if (!featureTypeList) return layers;

    for (XMLElement* ft = featureTypeList->FirstChildElement();
         ft != nullptr;
         ft = ft->NextSiblingElement()) {
        const char* name = nullptr;
        const char* title = nullptr;

        XMLElement* n = ft->FirstChildElement("wfs:Name");
        if (!n) n = ft->FirstChildElement("Name");
        XMLElement* t = ft->FirstChildElement("wfs:Title");
        if (!t) t = ft->FirstChildElement("Title");

        if (n) name = n->GetText();
        if (t) title = t->GetText();

        if (name)
            layers.push_back({name, title ? title : ""});
    }

    return layers;
}

std::string WFSClient::getLayerAsJSON(const std::string &layerTitle)
{
    auto layers = getLayers();
    std::string typenameValue;

    for (const auto& layer : layers) {
        if (layer.title == layerTitle) {
            typenameValue = layer.name;
            break;
        }
    }

    if (typenameValue.empty()) {
        std::cerr << "❌ Layer with title '" << layerTitle << "' not found.\n";
        return "{}";
    }

    std::string url = baseUrl +
                      "?service=WFS&version=2.0.0&request=GetFeature&typename=" +
                      typenameValue + "&outputFormat=application/json";

    std::cout << "🔗 Requesting GeoJSON from: " << url << std::endl;

    std::string json = httpGet(url);
    if (json.empty()) {
        std::cerr << "❌ No data returned from GeoServer.\n";
        return "{}";
    }

    return json;
}
