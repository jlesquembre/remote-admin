#ifndef DAEMONSMANAGER_H
#define DAEMONSMANAGER_H

#include <string>

class DaemonsManager
{
public:
    //DaemonsManager();
    static void reloadAutofs();
    static void reloadVsftpd();
    static void reloadAll();
private:
    static std::string _autofs;
    static std::string _vsftpd;

};

#endif // DAEMONSMANAGER_H
