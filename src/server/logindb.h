#ifndef LOGINDB_H
#define LOGINDB_H

#include <db_cxx.h>
#include <string>
#include <vector>

using namespace std;

class LoginDB
{
public:
    LoginDB();
    vector<string> getKeys();
    void add(string key, string value);
    void change(string, string);
    void del(string );
    bool contains(string);
private:
    void openDb();
    void closeDb();
    Db *db;
    //Dbt user;
    //Dbt pass;
};

#endif // LOGINDB_H
