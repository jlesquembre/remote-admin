/*
 * WriteConf.cpp
 *
 *  Created on: 19/04/2011
 *      Author: Jose Luis Lafuente
 */

#include "WriteConf.h"
#include <db_cxx.h>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>



namespace fs = boost::filesystem;

using namespace
std;
//using namespace boost;


WriteConf::WriteConf ()
{


  file.open ("/home/jlle/Descargas/aaa_test.txt");
  //file.p
  fs::exists ("qwwq");
  fs::path full_path (fs::initial_path < fs::path > ());
  full_path = fs::system_complete ("aa");
  DB *dbp;
  int ret;
  if ( (ret = db_create (&dbp, NULL, 0))!=0 )
    {
      cout << "db_create: " << db_strerror (ret);
    }
}

WriteConf::~WriteConf ()
{
  file.close ();
}

void
WriteConf::writeLog ()
{
  file << text << endl << "this is  alasjjd djsndjsd  dsjndsj"<<"srdfmroitmriot"<<"sdkmsdkmsdkomds";
}

void
WriteConf::setText (string str)
{
  text = str;
}
