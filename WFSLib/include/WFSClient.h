#pragma once
#include <string>
#include <vector>

/**
 * @brief Represents a Web Feature Service layer.
 */
struct WFSLayer {
    std::string name;
    std::string title;
};

/**
 * @brief Lightweight client for WFS access.
 *
 * Supports listing layers and exporting layer content as JSON.
 */
class WFSClient {
public:
    /**
     * @brief Construct a WFS client.
     * @param baseUrl Base URL of the WFS endpoint.
     * @param user Optional username for HTTP authentication.
     * @param password Optional password for HTTP authentication.
     */
    WFSClient(const std::string& baseUrl,
              const std::string& user = "",
              const std::string& password = "");

    /**
     * @brief Retrieve available WFS layers.
     * @return List of layers exposed by the service.
     */
    std::vector<WFSLayer> getLayers();

    /**
     * @brief Retrieve a layer as JSON.
     * @param layerTitle Title of the layer to fetch.
     * @return JSON representation of the layer.
     */
    std::string getLayerAsJSON(const std::string& layerTitle);

private:
    std::string baseUrl;
    std::string user;
    std::string password;

    /**
     * @brief Perform an HTTP GET request.
     * @param url Target URL.
     * @return Response body.
     */
    std::string httpGet(const std::string& url);
};
