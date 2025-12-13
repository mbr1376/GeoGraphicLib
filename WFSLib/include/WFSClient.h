#pragma once
#include <string>
#include <vector>

struct WFSLayer {
    std::string name;
    std::string title;
};

class WFSClient {
public:
    WFSClient(const std::string& baseUrl,
              const std::string& user = "",
              const std::string& password = "");

    std::vector<WFSLayer> getLayers();
    std::string getLayerAsJSON(const std::string& layerTitle);

private:
    std::string baseUrl;
    std::string user;
    std::string password;

    std::string httpGet(const std::string& url);
};
