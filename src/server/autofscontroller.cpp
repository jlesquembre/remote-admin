#include "autofscontroller.h"
#include "apppaths.h"
#include "../services/daemonsmanager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

//const ststring AutofsController::autoMasterPath = "";
static const string startSection = "#vsftpd section, don't edit manually!!";
static const string endSection = "#end of section";

AutofsController::AutofsController()
{



    _tempFile = AppPaths::autoMasterFile + ".tmp";

    fstream stream (AppPaths::autoMasterFile.c_str(), ios::in | ios::out);
    string line;
    while(stream.good())
        {
            getline(stream, line);            

            if(line.compare(startSection) == 0 )
            {                
                stream.close();

            }

        }

    if(stream.is_open())
    {
        stream.clear();
        stream << startSection << endl <<  endSection << endl;
        stream.close();
    }    

}

void AutofsController::startParse()
{

    _instream.open(AppPaths::autoMasterFile.c_str(), ios::in );
    _outstream.open(_tempFile.c_str(), ios::out );

    string line;
    while(_instream.good())
    {
        getline(_instream, line);
        _outstream << line << endl;
        if(line.compare(startSection) == 0 )
            return;
    }

}

void AutofsController::endParse()
{

    string line;
    while(_instream.good())
        {
            getline(_instream, line);
            _outstream << line << endl;
        }

    _instream.close();
    _outstream.close();
    rename(_tempFile.c_str(), AppPaths::autoMasterFile.c_str());

}

void AutofsController::addEntry(std::string user)
{
    this->startParse();
    _outstream << AppPaths::userVirtualHomePath << "/" << user << " "
               << AppPaths::autoUsersPath << "/auto." << user
               << " --ghost"<<endl;
    this->endParse();

    DaemonsManager::reloadAutofs();

}

void AutofsController::deleteEntry(std::string user)
{
    this->startParse();

    string line;
    while(_instream.good())
        {
            getline(_instream, line);
            if(line[0]=='#')
            {
                _outstream << line << endl;
                break;
            }            
            const int pathSize = AppPaths::userVirtualHomePath.size();
            int msize = pathSize + user.size();  // "/home/virtual/" -> 14
            if(msize < line.size())
                if(line.compare(pathSize,user.size(), user) != 0)
                    _outstream << line << endl;

        }

    this->endParse();

    DaemonsManager::reloadAutofs();

}
