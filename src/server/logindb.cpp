#include "logindb.h"
#include "apppaths.h"
#include <db_cxx.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

LoginDB::LoginDB()
{



}

void LoginDB::openDb()
{

    db = new Db (NULL,0);               // Instantiate the Db object
    //db->set_encrypt();

    u_int32_t oFlags = DB_CREATE; // Open flags;    

    // Open the database
    db->open(NULL,                // Transaction pointer
             AppPaths::ftpDBFile.c_str(),          // Database file name
             NULL,                // Optional logical database name
             DB_HASH,            // Database access method
             oFlags,              // Open flags
             0);

}

void LoginDB::closeDb()
{
    db->close(0);
    delete(db);
}

vector<string> LoginDB::getKeys()
{

    LoginDB::openDb();

    vector<string> keys;// = new vector<string>;

    Dbc *cursorp;
    Dbt key, data;

    //key.set_flags(DB_DBT_USERMEM);
    // data.set_flags(DB_DBT_USERMEM);

    // Get a cursor
    db->cursor(NULL, &cursorp, 0);

    string name;

    int ret;
    // Iterate over the database, retrieving each record in turn.
    while ((ret = cursorp->get(&key, &data, DB_NEXT)) == 0) {
        // Do interesting things with the Dbts here.

        char* tmp = static_cast<char*> (key.get_data());
        name.resize(key.get_size());
        copy(tmp, tmp+key.get_size(), name.begin());
        //name += '\0';
        keys.push_back( name);
        cout<<"name is "<<name<<" ---  "<<name.size()<<" ---  " <<key.get_size() <<endl;

    }

    cursorp->close();

    //cout << "Value in DB-> " << name << endl;


    LoginDB::closeDb();    


    return keys;
}

bool LoginDB::contains(string str)
{
    vector<string> v = this->getKeys();
    vector<string>::iterator result;
    result = find(v.begin(), v.end(), str);

    if (result == v.end())
        return false;
     else
        return true;


}

void LoginDB::add(string key, string value)
{

    LoginDB::openDb();

    //string temp = new string(key);//(key.begin(),key.end());

    cout<< "Saving -> " << key.data() << "("<< key.size() << ")    -  " << value << endl;

    //char *temp = const_cast<char*> (key.c_str());

    Dbt name(const_cast<char*> (key.data()), key.size());
    //name.set_flags(DB_DBT_USERMEM);
    /*name.set_dlen(3);
    name.set_doff(3);
    name.set_size(3);
    name.set_ulen(3);*/
    //Dbt name(temp, sizeof(temp));
    Dbt pass(const_cast<char*> (value.data()), value.size());

    /* name.set_data(const_cast<char*>(key.data()));
    name.set_ulen(key.size()*sizeof(char));
    name.set_flags(DB_DBT_USERMEM);

    pass.set_data(const_cast<char*>(value.data()));
    pass.set_ulen(value.size()*sizeof(char));
    pass.set_flags(DB_DBT_USERMEM);
*/

    //    name.set_flags(DB_DBT_USERMEM);
    //    pass.set_flags(DB_DBT_USERMEM);



    db->put(NULL,&name,&pass,0);

    //db->sync(0);

    LoginDB::closeDb();

}

void LoginDB::del(string str)
{
    openDb();
/*
    Dbc *cursorp;
    Dbt key, data;
    int ret;
    string name;

    // Get a cursor
    db->cursor(NULL, &cursorp, 0);

    // Iterate over the database, retrieving each record in turn.
    while ((ret = cursorp->get(&key, &data, DB_NEXT)) == 0)
        {
            char* tmp = static_cast<char*> (key.get_data());
            name.resize(key.get_size());
            copy(tmp, tmp+key.get_size(), name.begin());

            if(name==str)
                cursorp->del(0);
        }

    if (cursorp != NULL)
        cursorp->close();

    */

    Dbt key(const_cast<char*> (str.data()), str.size());

    db->del(NULL, &key, 0);


    closeDb();

}

void LoginDB::change(string user, string pass)
{
    openDb();

    Dbc *cursorp;
    Dbt key(const_cast<char*> (user.data()), user.size());
    Dbt data;

    // Get a cursor
    db->cursor(NULL, &cursorp, 0);

    // Position the cursor
    int ret = cursorp->get(&key, &data, DB_SET);
    if (ret == 0)
        {
            data.set_data(const_cast<char*>(pass.data()));
            data.set_size(pass.size());
            cursorp->put(&key, &data, DB_CURRENT);
        }
    if (cursorp != NULL)
        cursorp->close();

    closeDb();

}
