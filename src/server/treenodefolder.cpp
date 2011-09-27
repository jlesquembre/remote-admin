#include "treenodefolder.h"
#include <Wt/WTreeNode>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <time.h>

#include <Wt/WIconPair>
#include <Wt/WStringUtil>
#include <Wt/WText>
#include <Wt/WTree>
#include <Wt/WTreeNode>

using namespace Wt;
//namespace fs = boost::filesystem;

/*
TreeNodeFolder::TreeNodeFolder(const WString &labelText, WIconPair *labelIcon=0, WTreeNode *parentNode=0)
    : WTreeNode(labelText, labelIcon, parentNode)
{

    fs::path full_path( fs::initial_path<fs::path>() );
    full_path = fs::system_complete( labelText.toUTF8() );

    fs::directory_iterator end_iter;
    for ( fs::directory_iterator dir_itr( full_path );
         dir_itr != end_iter;
         ++dir_itr )
        {

            if ( fs::is_directory( dir_itr->status() ) )
                {
                    //++dir_count;
                    std::cout << dir_itr->path().filename() << " [directory]\n";
                    this->addChildNode(new TreeNodeFolder(dir_itr->path().filename()));
                }




        }
}*/


TreeNodeFolder::TreeNodeFolder(const boost::filesystem::path& path)
    : WTreeNode(path.leaf() /*, createIcon(path)*/), path_(path)
{
    label()->setTextFormat(PlainText);

    this->addStyleClass("treenodefolder");
    this->setLoadPolicy(WTreeNode::NextLevelLoading);

    //if(path.leaf().compare("aa") == 0)
    //    this->setNodeVisible(false);

    if(this->hasParent())
    {
        if(this->parentNode()->label()->text().toUTF8().compare("/") == 0)
        {
            if(path.leaf().compare("mnt") != 0 && path.leaf().compare("home") != 0)
            {
                this->setNodeVisible(false);
            }
        }

    }

    if (path.string().compare("/home") == 0 )
    {

    }


   /* if (boost::filesystem::exists(path)) {
        if (!boost::filesystem::is_directory(path)) {
            //int fsize = (int)boost::filesystem::file_size(path);
            //setColumnWidget(1, new WText(boost::lexical_cast<std::string>(fsize)));
            //columnWidget(1)->setStyleClass("fsize");
        } else
            setSelectable(true);

        std::time_t t = boost::filesystem::last_write_time(path);
        struct tm ttm;

        localtime_r(&t, &ttm);
        char c[100];
        strftime(c, 100, "%b %d %Y", &ttm);*/
        //setColumnWidget(2, new WText(c));
        //columnWidget(2)->setStyleClass("date");
    //}
}
/*WIconPair *TreeNodeFolder::createIcon(const boost::filesystem::path& path)
{
    if (boost::filesystem::exists(path)
            && boost::filesystem::is_directory(path))
        return new WIconPair("icons/yellow-folder-closed.png",
                             "icons/yellow-folder-open.png", false);
    else
        return new WIconPair("icons/document.png",
                             "icons/yellow-folder-open.png", false);
}*/
void TreeNodeFolder::populate()
{
    try {
        //if (boost::filesystem::is_directory(path_)) {
            std::set<boost::filesystem::path> paths;
            boost::filesystem::directory_iterator end_itr;

            for (boost::filesystem::directory_iterator i(path_); i != end_itr; ++i)
                paths.insert(*i);

            for (std::set<boost::filesystem::path>::iterator i = paths.begin();
                 i != paths.end(); ++i)
                {
                    if (boost::filesystem::is_directory(*i))
                        addChildNode(new TreeNodeFolder(*i));
                }
        //}
    } catch (boost::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool TreeNodeFolder::expandable()
{
    boost::filesystem::directory_iterator end_itr;
    for (boost::filesystem::directory_iterator i(path_); i != end_itr; ++i)
        if (boost::filesystem::is_directory(*i))
            return true;

    return false;

    if (!populated())
        return boost::filesystem::is_directory(path_);
    else
        return WTreeNode::expandable();
}

std::string TreeNodeFolder::getCompletePath()
{
    //std::string;
    WString path("");


    WTreeNode *root = tree()->treeRoot();
    WTreeNode *node = this;
    while(node != root)
    {
        path = "/" + node->label()->text() + path;
        node = node->parentNode();
    }


    return path.toUTF8();




}
