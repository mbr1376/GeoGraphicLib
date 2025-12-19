#include "WFSClient.h"
#include <iostream>
#include <SLDClient.h>
void testWFSClient(){
    WFSClient client("http://localhost:8080/geoserver/ows");

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
void testSLD(){
    SLDClient client;

    std::string url =
        "http://localhost:8080/geoserver/rest/styles/line.sld";

    std::string user = "admin";
    std::string pass = "Saha@1403";
    std::string file = "line.sld";

    std::cout << "⬇ Downloading SLD...\n";
    if (!client.parseSLD(file)) {
        std::cout << "❌ Failed to parse SLD\n";

    }

    std::cout << "Layer name: " << client.getLayerName() << "\n";

    std::cout << "Colors found:\n";
    for (auto& c : client.getColors()) {
        std::cout << " - " << c.type << " = " << c.value << "\n";
    }

    std::cout << "Stroke color: " << client.getStrokeColor() << "\n";
    std::cout << "Stroke width: " << client.getStrokeWidth() << "\n";
    std::cout << "PropertyNames found:\n";
    for (auto& p : client.getPropertyNames())
        std::cout << " - " << p << "\n";


}
int main() {
    testWFSClient();
    testSLD();
    return 0;
}
