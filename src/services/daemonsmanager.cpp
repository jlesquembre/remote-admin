#include "daemonsmanager.h"

#include <string>
#include <stdlib.h>


using namespace std;

string DaemonsManager::_autofs = "service autofs";
string DaemonsManager::_vsftpd = "service vsftpd";


void DaemonsManager::reloadAutofs()
{
    string cmd = _autofs + " reload";
    system(cmd.c_str());
}

void DaemonsManager::reloadVsftpd()
{
    string cmd = _vsftpd + " reload";
    system(cmd.c_str());

}

void DaemonsManager::reloadAll()
{
    DaemonsManager::reloadAutofs();
    DaemonsManager::reloadVsftpd();
}

/*
DaemonsManager::DaemonsManager()
{
}*/
