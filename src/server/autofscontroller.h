#ifndef AUTOFSCONTROLLER_H
#define AUTOFSCONTROLLER_H

#include <string>
#include <fstream>

class AutofsController
{
public:
    AutofsController();
    void addEntry(std::string user);
    void deleteEntry(std::string user);


private:
    void startParse();
    void endParse();

    std::string _tempFile;
    std::ifstream _instream;
    std::ofstream _outstream;

};

#endif // AUTOFSCONTROLLER_H
