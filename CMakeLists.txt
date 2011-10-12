cmake_minimum_required (VERSION 2.6)
project (RemoteAdmin)

#Testinbg branch
#add_subdirectory(WTtest)

SET(EXECUTABLE_OUTPUT_PATH ./Binaries)
#SET(LIBRARY_OUTPUT_PATH lib)
SET(PROJECT_FOLDER ../remote-admin)

SET(WT_INCLUDE /home/jlle/develop/wt/install_wt_3_1_10_boost_1_42_0/include/)
SET(WT_LIB_DIR /home/jlle/develop/wt/install_wt_3_1_10_boost_1_42_0/lib/)
SET(BOOST_INCLUDE /home/jlle/develop/boost/stage_boost_1_42_0/include/)
SET(BOOST_LIB_DIR /home/jlle/develop/boost/stage_boost_1_42_0/lib/)


include_directories( ${WT_INCLUDE} ${BOOST_INCLUDE})
#link_directories( ${WT_LIB} ${BOOST_LIB}) #if are in LD_LIBRARY_PATH not necessary
                                           #and better use find_library
#set_directory_properties(PROPERTIES INCLUDE_DIRECTORIES true)
add_custom_target(static_files ALL cp -r ${PROJECT_FOLDER}/css ${EXECUTABLE_OUTPUT_PATH} SOURCES css/style.css)
#add_custom_target(css ALL SOURCES css/style.css)


#find_library(WT_LIBS wt)

find_library(WT_LIB wt ${WT_LIB_DIR})
find_library(WTEXT_LIB wtext ${WT_LIB_DIR})
find_library(WTHTTP_LIB wthttp ${WT_LIB_DIR})
set(WT_LIBS ${WT_LIB} ${WTEXT_LIB} ${WTHTTP_LIB})

find_library(DB_LIB db_cxx)                          

#ADD_LIBRARY(wt SHARED Hello/HelloApp.cpp)  #Creates a library (*.so)


#message(STATUS ${WT_LIB})
#message(STATUS $ENV{LD_LIBRARY_PATH})


add_executable(MainPage src/server/apppaths.cpp src/server/optionmap.cpp src/server/autofscontroller.cpp src/server/autofs.cpp
                        src/server/treenodefolder.cpp src/client/MainPage.cpp src/server/WriteConf.cpp src/server/logindb.cpp
                        src/client/ftpuser.cpp src/client/ftpusercontroller.cpp
                        src/widgets/tabwidget.cpp )

#add_executable(m2 src/client/MainPage.cpp src/server/WriteConf.cpp)

#TARGET_LINK_LIBRARIES(HelloApp wt wtext wthttp)
TARGET_LINK_LIBRARIES(MainPage ${WT_LIBS})
TARGET_LINK_LIBRARIES(MainPage ${DB_LIB})


#file(COPY css DESTINATION ${EXECUTABLE_OUTPUT_PATH})


