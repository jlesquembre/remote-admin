cmake_minimum_required (VERSION 2.6)
project (RemoteAdmin)


SET(EXECUTABLE_OUTPUT_PATH ./Binaries)
SET(PROJECT_FOLDER ../remote-admin)

#SET(WT_INCLUDE /home/jlle/develop/wt/wt-install/include/)
#SET(WT_LIB_DIR /home/jlle/develop/wt/wt-install/lib/)
#-DWT_DIR=/home/jlle/develop/wt/wt-install

IF(WT_DIR)
    #include_directories( ${WT_INCLUDE})# ${BOOST_INCLUDE})
    include_directories( ${WT_DIR}/include )
ENDIF()


#link_directories( ${WT_LIB} ${BOOST_LIB}) #if are in LD_LIBRARY_PATH not necessary
                                           #and better use find_library

add_custom_target(static_files ALL cp -r ${PROJECT_FOLDER}/resources ${EXECUTABLE_OUTPUT_PATH} SOURCES resources/style.css)




IF(WT_DIR)
    find_library(WT_LIB wt ${WT_DIR}/lib)
    find_library(WTEXT_LIB wtext ${WT_DIR}/lib)
    find_library(WTHTTP_LIB wthttp ${WT_DIR}/lib)
ELSE()
    find_library(WT_LIB wt)
    find_library(WTEXT_LIB wtext)
    find_library(WTHTTP_LIB wthttp)
ENDIF()
set(WT_LIBS ${WT_LIB} ${WTEXT_LIB} ${WTHTTP_LIB})

find_library(DB_LIB db_cxx)


add_executable(remoteadmin src/server/apppaths.cpp src/server/optionmap.cpp src/server/autofscontroller.cpp src/server/autofs.cpp
                           src/server/treenodefolder.cpp src/client/MainPage.cpp src/server/WriteConf.cpp src/server/logindb.cpp
                           src/client/ftpuser.cpp src/client/ftpusercontroller.cpp
                           src/widgets/tabwidget.cpp src/widgets/loginwidget.cpp
                           src/services/notification.cpp src/services/daemonsmanager.cpp)


TARGET_LINK_LIBRARIES(remoteadmin ${WT_LIBS})
TARGET_LINK_LIBRARIES(remoteadmin ${DB_LIB})



#MESSAGE("arch is  ${arch}")
#UNSET(DISTRO CACHE)
IF(NOT DISTRO)
    EXECUTE_PROCESS(COMMAND lsb_release -is
                    OUTPUT_VARIABLE DISTRO
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF()

STRING(TOLOWER ${DISTRO} DISTRO)

IF(DISTRO MATCHES debian)
    INCLUDE(./packages/debian/CMakeLists.txt)
ENDIF()

#MESSAGE("arch is ${DISTRO}")




