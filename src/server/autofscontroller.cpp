#include "autofscontroller.h"
#include "apppaths.h"

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



    _tempFile = AppPaths::autoMasterPath + ".tmp";

    fstream stream (AppPaths::autoMasterPath.c_str(), ios::in | ios::out);
    string line;
    while(stream.good())
        {
            getline(stream, line);
            //outstream << line << endl;

            if(line.compare(startSection) == 0 )
            {
                //contains = true;
                //stream.setstate(ios::eofbit);
                stream.close();

            }

        }

    if(stream.is_open())
    {
        stream.clear();
        stream << startSection << endl <<  endSection << endl;
        stream.close();
    }

    //stream.seekp(0,ios::beg);


    //instream.close();
    //outstream.close();

    //rename(tempFile.c_str(), AppPaths::autoMasterPath.c_str());

}

void AutofsController::startParse()
{

    _instream.open(AppPaths::autoMasterPath.c_str(), ios::in );
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
    rename(_tempFile.c_str(), AppPaths::autoMasterPath.c_str());

}

void AutofsController::addEntry(std::string user)
{
    this->startParse();
    _outstream << "/home/virtual/" << user << " /etc/vsftpd/maps/auto." << user << " --ghost"<<endl;
    this->endParse();

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

            //cout<<"!!!!!!"<< line.substr (14,user.size()) <<endl ;
            int msize = 14 + user.size();  // "/home/virtual/" -> 14
            if(msize < line.size())
                if(line.compare(14,user.size(), user) != 0)
                    _outstream << line << endl;

        }

    this->endParse();

}
