#include "ftpuser.h"
#include "ftpusercontroller.h"
#include "../server/optionmap.h"
#include "../server/treenodefolder.h"
#include "../server/apppaths.h"
#include "../services/notification.h"

#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WSignal>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WLabel>
#include <Wt/WDialog>
#include <Wt/WTree>
#include <Wt/WTreeNode>
#include <Wt/WAnimation>
#include <Wt/WCheckBox>

#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <vector>
#include <string>
#include <map>
#include <string>
#include <set>

using namespace Wt;

int FtpUser::n = 0;
FtpUser* FtpUser::openUser = NULL;
//string FtpUser::userConfPath = "/home/jlle/Descargas/DB/user_conf/";

FtpUser::FtpUser(std::string name, WContainerWidget *parent)
    : WContainerWidget(parent)
{

    n++;
    this->setStyleClass("ftpuser");


    dropDown = new WContainerWidget(this);  /*dropDown->setStyleClass("");*/dropDown->setStyleClass("drop_down_container");
    dropDownHead = new WContainerWidget(dropDown); /*dropDownHead->setStyleClass("");*/ dropDownHead->setStyleClass("drop_down_head");
    dropDownBody = new WContainerWidget(dropDown); /*dropDownBody->setStyleClass("");*/ dropDownBody->setStyleClass("drop_down_body");


    this->name = new WText(/*boost::lexical_cast<string>(n ) +" - " + */name, dropDownHead);
    arrow = new WContainerWidget(dropDownHead);

    arrow->setStyleClass("arrow-down");
    //span class="google-visualization-table-sortind">▲</span>
    //<span class="google-visualization-table-sortind">▼</span>


    WContainerWidget *changePassArea = new WContainerWidget(dropDownBody);  //changePassArea->setInline(true);
    WContainerWidget *deleteArea = new WContainerWidget(dropDownBody);      //deleteArea->setInline(true);


    deleteArea->setStyleClass("deleteArea");    
    changePassArea->setStyleClass("changePassArea");

    error = new WText("&nbsp;",changePassArea);
    error->setStyleClass("errorText");



    //Enter password
    WContainerWidget *w1 = new WContainerWidget(changePassArea);
    WLabel *l1 = new WLabel("Type new password",w1);
    this->pass = new WLineEdit(w1);
    this->pass->setEchoMode(WLineEdit::Password);
    l1->setBuddy(this->pass);

    // Re-enter password
    WContainerWidget *w2 = new WContainerWidget(changePassArea);
    WLabel *l2 = new WLabel("Re-type new password",w2);
    this->repass = new WLineEdit(w2); //repass->setInline(false);
    this->repass->setEchoMode(WLineEdit::Password);
    l2->setBuddy(this->repass);

    l1->setStyleClass("label"); l2->setStyleClass("label");
    this->pass->setStyleClass("form"); this->repass->setStyleClass("form");


    WPushButton *changeButton = new WPushButton("Change password", changePassArea);
    WPushButton *deleteButton = new WPushButton("Delete",deleteArea);

    dropDownBody->hide();



    changeButton->setStyleClass("button white keyimg"); //changeButton->setInline(false);
    deleteButton->setStyleClass("button red crossimg");

    this->dropDownHead->clicked().connect(this,&FtpUser::openCloseUser);
    deleteButton->clicked().connect(this, &FtpUser::deleteUser);
    changeButton->clicked().connect(this,&FtpUser::changePassword);

    createFoldersBlock();


    options = new OptionMap(AppPaths::ftpUserConfPath + "/" + this->name->text().toUTF8());
    if(!options->exist()){

        options->read(AppPaths::ftpUserDefaultConfFile);
        /*boost::filesystem::copy_file(AppPaths::ftpUserDefaultConfFile,
                                     AppPaths::ftpUserConfPath + "/" + this->name->text().toUTF8());*/
    }

    options->update("local_root",
                    AppPaths::userVirtualHomePath + "/" + this->name->text().toUTF8());

}

WContainerWidget* FtpUser::createSharedFolderBlock(std::string path, bool writable)
{
    WContainerWidget *shareFolderArea = new WContainerWidget();
    shareFolderArea->setStyleClass("sharefolderarea");
    WPushButton *deleteButton = new WPushButton("",shareFolderArea);
    deleteButton->setStyleClass("button red crossimg xsmall");

    WCheckBox *w1 = new WCheckBox("Writable", shareFolderArea);
    writable ?  w1->setChecked() : w1->setUnChecked();
    w1->setStyleClass("checkboxwritable");

    WText *t = new WText(path,shareFolderArea );    

    deleteButton->clicked().connect( boost::bind(&FtpUser::removeSharedFolder,boost::ref(*this), shareFolderArea, path));
    w1->changed().connect(boost::bind(&FtpUser::sharedFolderWritable,boost::ref(*this), path, w1) );

    return shareFolderArea;

}

void FtpUser::removeSharedFolder(WContainerWidget* widgetToRemove, std::string path)
{
    addFolderBlock->removeWidget(widgetToRemove);
    autofs->removeFolder(path);



}

void FtpUser::sharedFolderWritable(std::string &path, WCheckBox *writable )
{
    std::cout << "WWWWW->" << writable->isChecked() <<std::endl;
    autofs->removeFolder(path);
    autofs->addFolder(path, writable->isChecked());
}

WContainerWidget* FtpUser::createFoldersBlock()
{
    addFolderBlock = new WContainerWidget(this);
    addFolderBlock->setStyleClass("addfolderblock");

    WText *text = new WText("List of shared folders", addFolderBlock);
    text->setStyleClass("sharedfoldertext");

    autofs = new AutoFs(name->text().toUTF8());

    std::map<std::string,bool> map = autofs->getFolders();

    //std::map<std::string,bool>::iterator it;
    typedef std::map<std::string,bool>::const_iterator CI;

    for(CI it = map.begin(); it!=map.end(); it++)
    {
        addFolderBlock->addWidget(createSharedFolderBlock(it->first, it->second));

    }

    WPushButton *addFolderButton = new WPushButton("Share new folder", addFolderBlock);
    addFolderButton->setStyleClass("button white");


    addFolderDialog = new WDialog("Select a folder");
    addFolderDialog->titleBar()->addStyleClass("add_ftpuser_dialog_titlebar");
    addFolderDialog->contents()->addStyleClass("add_folder_dialog_contents");
    addFolderDialog->setStyleClass("add_folder_dialog");


    Wt::WCheckBox *showHiddenFolders = new WCheckBox("Show hidden folders",addFolderDialog->contents());
    //showHiddenFolders->changed().connect(boost::bind(&FtpUser::showHideHiddenFolders,boost::ref(*this), showHiddenFolders));
    //Look signal slots, connect change with tree ;-)


    WContainerWidget *buttonsContainer = new WContainerWidget(addFolderDialog->contents());
    buttonsContainer->setStyleClass("btncont");
    WPushButton *ok = new WPushButton("Share folder",buttonsContainer);
    ok->setStyleClass("button white");
    WPushButton *cancel = new WPushButton("Cancel",buttonsContainer);
    cancel->setStyleClass("button white");

    WContainerWidget *treeCont = new WContainerWidget(addFolderDialog->contents());
    treeCont->setStyleClass("tree_style");
    /*WTree */tree = new WTree(treeCont);
    tree->setSelectionMode(Wt::SingleSelection);
    boost::filesystem::path path("/");
    TreeNodeFolder *root = new TreeNodeFolder(path,false);//, folderIcon);
    tree->setTreeRoot(root);

    addFolderButton->clicked().connect(this, &FtpUser::showDialog);
    cancel->clicked().connect(this,&FtpUser::hideDialog);
    ok->clicked().connect(this,&FtpUser::addSharedFolder);



    showHiddenFolders->changed().connect(boost::bind(&TreeNodeFolder::test,boost::ref(*root), showHiddenFolders));

}

void FtpUser::showHideHiddenFolders(WCheckBox *showHidden)
{

    std::cout << std::boolalpha ;
    //std::cout << "Real Value: " << showHiddenFolders->isChecked() << std::endl;
    std::cout << "Passed is:  " << showHidden->isChecked() << std::endl;
}

void FtpUser::showDialog()
{
    addFolderDialog->show();

}


void FtpUser::hideDialog()
{
    addFolderDialog->hide();

}

void FtpUser::addSharedFolder()
{



    WTree::WTreeNodeSet set = tree->selectedNodes();
    for(WTree::WTreeNodeSet::const_iterator it = set.begin(); it!= set.end(); it++)
    {
        std::string path = ((TreeNodeFolder*)(*it))->getCompletePath();
        autofs->addFolder(path, false);        
        addFolderBlock->insertWidget(addFolderBlock->count()-1, createSharedFolderBlock(path,false));
    }

    addFolderDialog->hide();    

}

FtpUser::~FtpUser()
{
    FtpUser::openUser = NULL;

}

void FtpUser::openCloseUser()
{

    //std::string jsString =  "$('#"+dropDownHead->id()+"').click(function () {"
    //        "$('#"+dropDownBody->id()+"').slideToggle('medium');});";
           // "$(document).mouseup(function(e) {"
           // "if($(e.target).parent('#"+dropDown->id()+"').length==0) {                    "
           // "$('#"+dropDownBody->id()+"').slideUp();}      }); ";

    //doJavaScript(jsString);

    //doJavaScript("alert ("  +dropDownHead->id() + "+' --- '+"+ dropDownHead->jsRef() +");");
    //doJavaScript("alert('"+dropDownHead->id()+"');");


    if(dropDownBody->isVisible())   //close it
        {
            dropDownHead->removeStyleClass("selected");

            /**** **/
            //WAnimation fade(WAnimation::SlideInFromTop , WAnimation::Linear, 250);
            //dropDownBody->setTransitionAnimation(fade);
            //dropDownBody->animateHide(fade);
            //dropDownBody->setHidden(true,fade);

            /*******/

            dropDownBody->hide();
            arrow->setStyleClass("arrow-down");

            FtpUser::openUser = NULL;

            this->pass->setText("");
            this->repass->setText("");
            this->error->setText("&nbsp;");

        }
    else      //open it
        {
            dropDownHead->addStyleClass("selected");
            dropDownBody->show();
            arrow->setStyleClass("arrow-up");


            if(FtpUser::openUser != NULL)
                {
                    FtpUser::openUser->openCloseUser();
                }

            FtpUser::openUser = this;

        }

}



void FtpUser::init()
{
    FtpUser::n = 0;
    FtpUser::openUser = NULL;
}

void FtpUser::deleteUser()
{

    FtpUserController *parent = dynamic_cast<FtpUserController*>(this->parent());
    parent->deleteFtpUser(this->name->text().toUTF8());    
    Notification::displayMessage(name->text() + " was removed!!", messageType::SUCCESS);
    options->deleteConfFile();
    autofs->deleteFile();
    delete this;

}

void FtpUser::changePassword()
{
    if(this->pass->text().empty())
        {
            this->error->setText("Password cannot be empty");
            return;
        }
    if(this->pass->text() != this->repass->text())
        {
            this->error->setText("Password does not match");
            return;
        }

    //TODO change password in database
    FtpUserController *parent = dynamic_cast<FtpUserController*>(this->parent());
    parent->changeFtpPassword(name->text().toUTF8(), pass->text().toUTF8());

    Notification::displayMessage("Password changed!!", messageType::SUCCESS);
    this->openCloseUser();

}

void FtpUser::createConfFile()
{
    //options = new OptionMap(userConfPath + name->text().toUTF8());
    //options->read(userConfPath + "default");
    //options->save();
}

