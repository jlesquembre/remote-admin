#ifndef OPTIONMAP_H
#define OPTIONMAP_H

#include <string>
#include <map>

class OptionMap
{
public:
    OptionMap(std::string);
    void read(std::string);
    void save();
    void update(std::string, std::string);
    bool exist();
    void deleteConfFile();
    void printMap();
private:
    std::map<std::string,std::string> container;
    std::string _path;
};

#endif // OPTIONMAP_H
