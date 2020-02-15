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
        bool        saveConfig(std::string filePath);

        std::string getConfigEntry(std::string key);
        void        putConfigEntry(std::string key, std::string value);
    };

#endif