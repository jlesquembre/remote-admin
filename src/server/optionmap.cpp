#include "optionmap.h"
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include "boost/filesystem.hpp"



using namespace std;


OptionMap::OptionMap(string path)
{

    //using namespace boost::filesystem;

    //boost::filesystem::path a(path);
    _path = path;

    if(boost::filesystem::exists(path))
        this->read(path);



}

void OptionMap::read(std::string path)
{
    container.empty();

    ifstream stream(path.c_str(), ifstream::in);

    const char comment = stream.widen('#');
    string line;
    while(stream.good())
        {
            getline(stream, line);
            if(!line.empty())
                {
                    if(line[0] == comment || line[0] == ' ' || line[0] == '\t')
                        {
                            // do nothing
                        }
                    else
                        {
                            int eqpos = line.find('=');
                            string key = line.substr(0, eqpos);
                            string data = line.substr(eqpos + 1, line.npos);

                            container[key] = data;
                        }
                }
        }
    stream.close();

}

void OptionMap::save()
{
    typedef map<string,string>::const_iterator CI;
    ofstream stream(_path.c_str(), ofstream::out);


    for(CI p = container.begin(); p!= container.end(); p++)
        {
            stream << p->first << '=' << p->second << endl;
        }
    stream.close();

}

void OptionMap::update(std::string key, std::string value)
{
    container[key] = value;
    this->save();
}

void OptionMap::printMap()
{
    typedef map<string,string>::const_iterator CI;

    for(CI p = container.begin(); p!= container.end(); p++)
        {
            cout << p->first <<" -> " << p->second << endl;
        }
}

bool OptionMap::exist()
{
    return boost::filesystem::exists(_path);
}

void OptionMap::deleteConfFile()
{
    boost::filesystem::remove(_path);
}
