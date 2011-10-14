#include "apppaths.h"
#include <string>

// /etc/auto.master
const std::string AppPaths::autoMasterFile = "/home/jlle/Descargas/DB/auto.master";

// /etc/vsftpd/maps
const std::string AppPaths::autoUsersPath = "/home/jlle/Descargas/DB/maps";







// /etc/vsftpd/user_conf
const std::string AppPaths::ftpUserConfPath = "/home/jlle/Descargas/DB/user_conf";

// /etc/vsftpd/vsftpd_login.db
const std::string AppPaths::ftpDBFile = "/home/jlle/Descargas/DB/login.db";

// /home/virtual
const std::string AppPaths::userVirtualHomePath = "/home/jlle/Descargas/DB/virtual";

// /home/virtual/ftpuser.conf.default
const std::string AppPaths::ftpUserDefaultConfFile = AppPaths::userVirtualHomePath + "/ftpuser.conf.default";

//AppPaths::AppPaths()
//{
//}
