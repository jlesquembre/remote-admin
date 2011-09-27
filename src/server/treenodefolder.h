#ifndef TREENODEFOLDER_H
#define TREENODEFOLDER_H
#include <Wt/WTreeNode>
#include <boost/filesystem/path.hpp>
#include <string>


class TreeNodeFolder : public Wt::WTreeNode
{
public:
    //TreeNodeFolder(const WString &labelText, WIconPair *labelIcon=0, WTreeNode *parentNode=0);
    //void expand();

    TreeNodeFolder(const boost::filesystem::path& path);
    std::string getCompletePath();

private:
    boost::filesystem::path path_;

    virtual void populate();
    virtual bool expandable();    
    //static Wt::WIconPair *createIcon(const boost::filesystem::path& path);





};

#endif // TREENODEFOLDER_H
