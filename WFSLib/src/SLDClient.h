#pragma once

#include <string>
#include <map>

class SLDClient
{
public:
    bool downloadSLD(const std::string& url,
                     const std::string& user,
                     const std::string& password,
                     const std::string& outputFile);

    bool parseSLD(const std::string& sldFile);

    std::string getStrokeColor() const;
    double getStrokeWidth() const;

private:
    std::string strokeColor_;
    double strokeWidth_ = 0.0;
};
