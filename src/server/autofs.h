#ifndef AUTOFS_H
#define AUTOFS_H

#include <string>
#include <map>

class AutoFs
{
public:
    AutoFs(std::string);
    std::map<std::string, bool> getFolders();
    void addFolder(std::string, bool);
    void removeFolder(std::string);

private:

    static const std::string wmode;
    static const std::string rmode;

    std::string _autoFile;
    std::map<std::string, bool> _folders;

    std::pair<std::string,bool>getPathFromAutofs(std::string);




};

#endif // AUTOFS_H
