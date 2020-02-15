#ifndef __CONFIG_H
#define __CONFIG_H

#include <map>
#include <string>

class Config
{
    private:
        std::map<std::string, std::string> _configEntries;

    public:
        bool        loadConfig(std::string filePath);
        std::string getConfigEntry(std::string key);
    };

#endif