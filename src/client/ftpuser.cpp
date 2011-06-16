#include "ftpuser.h"
#include "ftpusercontroller.h"
#include "../server/optionmap.h"
#include "../server/treenodefolder.h"

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

#include <boost/filesystem/path.hpp>

#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace Wt;

int FtpUser::n = 0;
FtpUser* FtpUser::openUser = NULL;
string FtpUser::userConfPath = "/home/jlle/Descargas/DB/user_conf/";

FtpUser::FtpUser(std::string name, WContainerWidget *parent)
    : WContainerWidget(parent)
{
    //static int n = 0;
    n++;    

    //this->setStyleClass("");
    this->setStyleClass("ftpuser");
    //changePassArea = new WContainerWidget (this);
    //changePassArea->setStyleClass("container");

    dropDown = new WContainerWidget(this);  /*dropDown->setStyleClass("");*/dropDown->setStyleClass("drop_down_container");
    dropDownHead = new WContainerWidget(dropDown); /*dropDownHead->setStyleClass("");*/ dropDownHead->setStyleClass("drop_down_head");
    dropDownBody = new WContainerWidget(dropDown); /*dropDownBody->setStyleClass("");*/ dropDownBody->setStyleClass("drop_down_body");

    //dropDownBody->setId("dropdownbody" + boost::lexical_cast<string>(n ));
    //dropDownHead->setId("dropdownhead" + boost::lexical_cast<string>(n ));

    this->name = new WText(/*boost::lexical_cast<string>(n ) +" - " + */name, dropDownHead);
    arrow = new WContainerWidget(dropDownHead);
    //arrow->setInline(true);
    //arrow->setStyleClass("arrow-s arrow-ftp-user-name");
    arrow->setStyleClass("arrow-down");
    //span class="google-visualization-table-sortind">▲</span>
    //<span class="google-visualization-table-sortind">▼</span>


    WContainerWidget *changePassArea = new WContainerWidget(dropDownBody);  //changePassArea->setInline(true);
    WContainerWidget *deleteArea = new WContainerWidget(dropDownBody);      //deleteArea->setInline(true);

    //deleteArea->setStyleClass("");
    deleteArea->setStyleClass("deleteArea");
    //changePassArea->setStyleClass("");
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

    //w1->setStyleClass("input_block");
    l1->setStyleClass("label"); l2->setStyleClass("label");
    /*this->pass->setStyleClass("");*/this->pass->setStyleClass("form"); this->repass->setStyleClass("form");


    WPushButton *changeButton = new WPushButton("Change password", changePassArea);
    WPushButton *deleteButton = new WPushButton("Delete",deleteArea);

    //deleteButton->set

    dropDownBody->hide();

    //new WBreak(changePassArea);

    changeButton->setStyleClass("button white keyimg"); //changeButton->setInline(false);
    deleteButton->setStyleClass("button red crossimg");

    //changeButton->clicked().connect(this,&FtpUser::showChangePassArea);
    this->dropDownHead->clicked().connect(this,&FtpUser::openCloseUser);
    deleteButton->clicked().connect(this, &FtpUser::deleteUser);
    changeButton->clicked().connect(this,&FtpUser::changePassword);

    //this->pass->focussed().connect(this,&FtpUser::passArea);
    //this->dropDown->clicked().connect(this,&FtpUser::showChangePassArea);

    /*WContainerWidget *addFolderBlock = new WContainerWidget(this);
    addFolderBlock->setStyleClass("addfolderblock");
    WPushButton *addFolderButton = new WPushButton("Add new folder", addFolderBlock);
    addFolderButton->setStyleClass("button white");
    new WPushButton("Add new folder", addFolderBlock);*/
    createFoldersBlock();



    /*WPushButton *a = new WPushButton(this);
    a->setStyleClass("container");*/

    options = new OptionMap(userConfPath + this->name->text().toUTF8());
    if(!options->exist())
        createConfFile();

}

WContainerWidget* FtpUser::createFoldersBlock()
{
    WContainerWidget *addFolderBlock = new WContainerWidget(this);
    addFolderBlock->setStyleClass("addfolderblock");
    WPushButton *addFolderButton = new WPushButton("Add new folder", addFolderBlock);
    addFolderButton->setStyleClass("button white");
    //new WPushButton("Add new folder", addFolderBlock);

    addFolderDialog = new WDialog("Select a folder");
    //addFolderDialog->setStyleClass("add_ftpuser_dialog");
    addFolderDialog->titleBar()->addStyleClass("add_ftpuser_dialog_titlebar");
    addFolderDialog->contents()->addStyleClass("add_folder_dialog_contents");
    addFolderDialog->setStyleClass("add_folder_dialog");

    WContainerWidget *buttonsContainer = new WContainerWidget(addFolderDialog->contents());
    buttonsContainer->setStyleClass("btncont");
    WPushButton *ok = new WPushButton("Add folder",buttonsContainer);
    ok->setStyleClass("button white");
    WPushButton *cancel = new WPushButton("Cancel",buttonsContainer);
    cancel->setStyleClass("button white");

    WContainerWidget *treeCont = new WContainerWidget(addFolderDialog->contents());
    treeCont->setStyleClass("tree_style");
    WTree *tree = new WTree(treeCont);
    tree->setSelectionMode(Wt::SingleSelection);
    boost::filesystem::path path("/home/jlle/Descargas");
    TreeNodeFolder *root = new TreeNodeFolder(path);//, folderIcon);
    tree->setTreeRoot(root);

    addFolderButton->clicked().connect(this, &FtpUser::showDialog);
    cancel->clicked().connect(this,&FtpUser::hideDialog);
}

void FtpUser::showDialog()
{
    addFolderDialog->show();

}


void FtpUser::hideDialog()
{
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


    //dynamic_cast<Wt::WContainerWidget*>(this->parent())->removeWidget(this);

    //FtpUser::openUser = NULL;

    //this->clear();
    FtpUserController *parent = dynamic_cast<FtpUserController*>(this->parent());
    parent->deleteFtpUser(this->name->text().toUTF8());
    parent->showNotification(messageType::SUCCESS, name->text() + " was removed!!");
    options->deleteConfFile();
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

    parent->showNotification(messageType::SUCCESS,"Password changed!!");
    this->openCloseUser();

}

void FtpUser::createConfFile()
{
    options = new OptionMap(userConfPath + name->text().toUTF8());
    options->read(userConfPath + "default");
    options->save();
}

