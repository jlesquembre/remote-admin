#ifndef TREENODEFOLDER_H
#define TREENODEFOLDER_H
#include <Wt/WTreeNode>
#include <Wt/WCheckBox>
#include <boost/filesystem/path.hpp>
#include <string>


class TreeNodeFolder : public Wt::WTreeNode
{
public:
    //TreeNodeFolder(const WString &labelText, WIconPair *labelIcon=0, WTreeNode *parentNode=0);
    //void expand();

    TreeNodeFolder(const boost::filesystem::path& path);
    TreeNodeFolder(const boost::filesystem::path& path, bool);
    std::string getCompletePath();
    bool visible();
    void test(Wt::WCheckBox*);

private:
    boost::filesystem::path _path;
    bool _visible;
    bool _showHidden;

    bool computeVisibility();

    virtual void populate();
    virtual bool expandable();    
    //static Wt::WIconPair *createIcon(const boost::filesystem::path& path);






};

#endif // TREENODEFOLDER_H
