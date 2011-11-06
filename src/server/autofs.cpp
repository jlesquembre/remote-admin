#include "autofs.h"
#include "apppaths.h"
#include "../services/daemonsmanager.h"

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <map>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

using namespace std;

const string AutoFs::rmode = "-fstype=fuse,ro,perms=0444:a+rD,owner=virtual,group=virtual";
const string AutoFs::wmode = "-fstype=fuse,rw,perms=0444:a+rD:u+w,owner=virtual,group=virtual";

typedef boost::tokenizer<boost::char_separator<char> >
tokenizer;


AutoFs::AutoFs(string userName)
{
    //_name = userName;
    _autoFile = AppPaths::autoUsersPath + "/auto." + userName;

    ifstream stream(_autoFile.c_str(), ifstream::in);

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
                _folders.insert(getPathFromAutofs(line));
            }
        }
    }
    stream.close();
}

void AutoFs::deleteFile()
{
    boost::filesystem::remove(_autoFile);

}


std::map<std::string, bool> AutoFs::getFolders()
{
    return _folders;

}

void AutoFs::addFolder(std::string folder, bool writable)
{



    if(_folders.find(folder) == _folders.end())
    {
        int pos = folder.find_last_of("/");
        string name = folder.substr(pos+1,folder.npos);



        ofstream stream(_autoFile.c_str(), ios::app );
        /*if(writable)
            stream << name << " " << wmode << " :bindfs#" << folder << endl;
        else
            stream << name << " " << rmode << " :bindfs#" << folder << endl;*/

        //If is this first entry, don't write a end of line
        if(_folders.size() != 0)
            stream << endl;

        stream << name << " " << (writable?wmode:rmode) << " :bindfs#" << folder;


        _folders[folder] = writable;

    }

    DaemonsManager::reloadAutofs();

}

void AutoFs::removeFolder(std::string folder)
{
    string tmp = _autoFile + ".tmp";

    ifstream inpstream(_autoFile.c_str(), ios::in );
    ofstream outstream(tmp.c_str(), ios::out );

    string line;
    while(inpstream.good())
    {
        getline(inpstream, line);
        if(!line.empty())
        {
            int pos = line.find(":bindfs#");
            string path = line.substr(pos+8, string::npos);
            //cout<<"AAA-> " << line.substr(pos+8,string::npos)<<endl;
            //cout<<"BBB-> " << folder<<endl;
            if(path != folder )
                outstream << line << endl;



            //if(line.find(folder) == string::npos && !line.empty())
        //   outstream << line << endl;
        }
    }
    inpstream.close();
    outstream.close();
    rename(tmp.c_str(), _autoFile.c_str());

    _folders.erase(folder);

    DaemonsManager::reloadAutofs();

}

pair<string,bool> AutoFs::getPathFromAutofs(string line)
{
    int pos1 = line.find(" ");
    int pos2 = line.find(" ", pos1+1 );

    string options = line.substr( pos1+1, pos2-1 );
    string path = line.substr( pos2+1 , line.npos);

    bool writable;

    boost::char_separator<char> sep(",");
    tokenizer tokens(options, sep);
    BOOST_FOREACH(string t, tokens)
    {
        if(t.compare("ro") == 0)
        {
            writable = false;
            break;
        }
        else if (t.compare("rw") == 0)
        {
            writable = true;
            break;
        }
    }
    path = path.substr(path.find("/"),path.npos);

    return pair<string,bool>(path,writable);




}
