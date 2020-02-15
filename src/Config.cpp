#include "Config.h"

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <vector>

//Split prototype
std::vector<std::string> split(const std::string& string, char delimeter);

bool Config::loadConfig(std::string filePath)
{
    //Clear previous config entries
    _configEntries.clear();

    //Open configuration file
    std::ifstream configFile(filePath);
    if (!configFile.is_open())
    {
        printf("[Error] Configuration file '%s' does not exist!\n", filePath.c_str());
        return false;
    }

    //Read configuration
    std::string currentLine;
    while (getline(configFile, currentLine))
    {
        //Delete leading and trailing whitespaces and tabs
        currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
        currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), '\t'), currentLine.end());

        //Skip empty lines or comments
        if (currentLine.length() == 0 || currentLine.at(0) == '#')
            continue;

        //Split lines at '='
        std::vector<std::string> splitLine = split(currentLine, '=');
        _configEntries.insert({ splitLine.at(0), splitLine.at(1) });
    }

    printf("[Info] Configuration '%s' loaded successfully.\n", filePath.c_str());
    configFile.close();

    return true;
}

bool Config::saveConfig(std::string filePath)
{

    return true;
}

std::vector<std::string> split(const std::string& string, char delimeter)
{
    std::vector<std::string> split_string;
    std::string currentString;

    std::istringstream stringStream(string);
    while (std::getline(stringStream, currentString, delimeter))
    {
        split_string.push_back(currentString);
    }

    return split_string;
}