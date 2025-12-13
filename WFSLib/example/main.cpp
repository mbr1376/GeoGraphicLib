#include "WFSClient.h"
#include <iostream>

int main() {
    WFSClient client("http://192.168.80.204:8080/geoserver/ows");

    auto layers = client.getLayers();

    std::cout << "📜 Layers found:\n";
    for (auto& l : layers) {
        std::cout << " - " << l.name << " (" << l.title << ")\n";
    }

    std::string title = "ATS";  // عنوان لایه مورد نظر
    std::string geojson = client.getLayerAsJSON(title);

    if (geojson != "{}") {
        std::cout << "✅ GeoJSON for layer '" << title << "':\n";
        std::cout << geojson << std::endl;
    }
}
