#include "ftpusercontroller.h"
#include "ftpuser.h"
#include "MainPage.h"
#include "../server/logindb.h"
#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WSignal>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <Wt/WTimer>
#include <Wt/WDialog>
#include <Wt/WApplication>
#include <Wt/WMessageBox>
#include <Wt/WLabel>
#include <boost/bind.hpp>
#include <vector>
#include <string>

using namespace Wt;

FtpUserController::FtpUserController( WContainerWidget *parent)
    : WContainerWidget(parent)
{

    //this->setStyleClass("");
    //this->addStyleClass("test1");

    //Define notification area
    notificationArea = new Wt::WText("&nbsp;",this);
    notificationArea->setStyleClass("notificationArea");

    //Define button to add ftp users
    WContainerWidget *addFtpUSerButtonContainer = new WContainerWidget(this);
    WPushButton *addFtpUserButton = new WPushButton("Add FTP user", addFtpUSerButtonContainer);
    addFtpUSerButtonContainer->setStyleClass("add_ftpuser_button");
    addFtpUserButton->setStyleClass("button orange bigrounded");

    //Define dialog to add ftp users
    this->wDialogAddFtpUser();
    addFtpUserButton->clicked().connect(this,&FtpUserController::showDialog);



    /**
      Add user form
      */

    /*

    WContainerWidget *addFtpUser = new WContainerWidget(this);
    WContainerWidget *dropDown = new WContainerWidget(addFtpUser);
    WContainerWidget *dropDownHead = new WContainerWidget(dropDown);
    WContainerWidget *dropDownBody = new WContainerWidget(dropDown);

    addFtpUser->setStyleClass("add_ftp_user");
    dropDown->setStyleClass("right");
    dropDownHead->setStyleClass("drop_down_head");
    dropDownBody->setStyleClass("drop_down_body");

    new WText("Add user", dropDownHead);
    dropDownBody->hide();

    WContainerWidget *arrow = new WContainerWidget(dropDownHead);
    arrow->setStyleClass("arrow-down");

*/

    /* --------------------- */



    //this->setStyleClass("ftp_controller");

    logindb = new LoginDB();
    std::vector <std::string> names = logindb->getKeys();
    FtpUser::init();

    std::vector<std::string>::iterator it;
    for(it = names.begin(); it < names.end(); it++)
        {
            //if( ! it->empty()) //TO-DO delete this line

            new FtpUser(*it,this);
            //users.push_back(new FtpUser(*it,this));

            /*
            new WText(*it, userList);
            new WLineEdit(userList);
            WPushButton *btn = new WPushButton("Modify name",userList);
            btn->clicked().connect(this,&MainPage::modifyEntry);

            new WBreak(userList);*/

        }

    _autofsc = new AutofsController();

    //new WBreak(this);


}


void FtpUserController::showNotification(messageType::Enum type, Wt::WString message)
{

    notificationArea->setText(message);

    switch(type){
    case messageType::SUCCESS:
        notificationArea->addStyleClass("success");
        break;
    case messageType::ERROR:
        notificationArea->addStyleClass("error");
        break;
    case messageType::WARNING:
        notificationArea->addStyleClass("warning");
        break;
    }

    Wt::WTimer::singleShot(3000,this,&FtpUserController::hideNotification);



}

void FtpUserController::hideNotification()
{
    notificationArea->setText("&nbsp;");
    notificationArea->setStyleClass("notificationArea");
}

void FtpUserController::showDialog()
{

    //dynamic_cast<MainPage*>(this->parent())->gray();
    //Wt::WApplication::root();



    addFtpUSerDialog->show();

    /*
    Wt::WDialog::DialogCode code = addFtpUSerDialog->exec();


    if ( code == Wt::WDialog::Accepted)
       this->showNotification(messageType::SUCCESS, newFtpUser->text() + " FTP User added!!!");

    if (code == Wt::WDialog::Rejected)
       this->showNotification(messageType::ERROR, newFtpUser->text() +  "FTP User not added!!!");
*/
}

void FtpUserController::hideDialog()
{

    newFtpUser->setText("");
    newFtpPass->setText("");
    newFtpRepass->setText("");
    error->setText("&nbsp;");
    addFtpUSerDialog->hide();

}


void FtpUserController::addFtpUser()
{

    if(this->newFtpUser->text().empty())
        {
            this->error->setText("User name cannot be empty");
            return;
        }
    if(logindb->contains(this->newFtpUser->text().toUTF8()))
        {
            this->error->setText("User name alredy exists");
            return;
        }
    if(this->newFtpPass->text().empty())
        {
            this->error->setText("Password cannot be empty");
            return;
        }
    if(this->newFtpRepass->text() != this->newFtpPass->text())
        {
            this->error->setText("Password does not match");
            return;
        }

    logindb->add(newFtpUser->text().toUTF8(),newFtpPass->text().toUTF8());
    _autofsc->addEntry(newFtpUser->text().toUTF8());
    //this->insertWidget(this->count()-1,new FtpUser(newFtpUser->text().toUTF8(),0));
    new FtpUser(newFtpUser->text().toUTF8(),this);
    this->showNotification(messageType::SUCCESS, newFtpUser->text() + " was added!");
    this->hideDialog();

    //this->insertWidget(this->count()-1,new FtpUser(newFtpUser->text().toUTF8()));

}


void FtpUserController::wDialogAddFtpUser()
{

    addFtpUSerDialog = new WDialog("Add FTP User");
    addFtpUSerDialog->setStyleClass("add_ftpuser_dialog");
    addFtpUSerDialog->titleBar()->addStyleClass("add_ftpuser_dialog_titlebar");
    addFtpUSerDialog->contents()->addStyleClass("add_ftpuser_dialog_contents");

    error = new WText("&nbsp;",addFtpUSerDialog->contents());
    error->setStyleClass("errorText");
    //
    WContainerWidget *w1 = new WContainerWidget(addFtpUSerDialog->contents());
    WLabel *l1 = new WLabel("FTP user name",w1);
    this->newFtpUser = new WLineEdit(w1);
    l1->setBuddy(this->newFtpUser);
    l1->setStyleClass("label");
    this->newFtpUser->setStyleClass("form");

    WContainerWidget *w2 = new WContainerWidget(addFtpUSerDialog->contents());
    WLabel *l2 = new WLabel("Password",w2);
    this->newFtpPass = new WLineEdit(w2);
    this->newFtpPass->setEchoMode(WLineEdit::Password);
    l2->setBuddy(this->newFtpPass);
    l2->setStyleClass("label");
    this->newFtpPass->setStyleClass("form");

    WContainerWidget *w3 = new WContainerWidget(addFtpUSerDialog->contents());
    WLabel *l3 = new WLabel("Re-type password",w3);
    this->newFtpRepass = new WLineEdit(w3);
    this->newFtpRepass->setEchoMode(WLineEdit::Password);
    l3->setBuddy(this->newFtpRepass);
    l3->setStyleClass("label");
    this->newFtpRepass->setStyleClass("form");
    //
    /*
    new Wt::WText("Enter your name: ", addFtpUSerDialog->contents());
    newFtpUser = new Wt::WLineEdit(addFtpUSerDialog->contents());
    new Wt::WBreak(addFtpUSerDialog->contents());
    newFtpPass = new Wt::WLineEdit(addFtpUSerDialog->contents());
    new Wt::WBreak(addFtpUSerDialog->contents());
    newFtpRepass = new Wt::WLineEdit(addFtpUSerDialog->contents());
    new Wt::WBreak(addFtpUSerDialog->contents());*/

    WPushButton *ok = new Wt::WPushButton("Ok", addFtpUSerDialog->contents());
    ok->setStyleClass("button white");
    WPushButton *cancel = new Wt::WPushButton("Cancel", addFtpUSerDialog->contents());
    cancel->setStyleClass("button white");

    //ok->clicked().connect(addFtpUSerDialog, &Wt::WDialog::accept);
    //cancel->clicked().connect(addFtpUSerDialog, &Wt::WDialog::reject);
    ok->clicked().connect(this, &FtpUserController::addFtpUser);
    cancel->clicked().connect(this, &FtpUserController::hideDialog);


    //ok->clicked().connect(addFtpUSerDialog, boost::bind(&FtpUserController::showNotification, messageType::ERROR ,"Hello"));






}

void FtpUserController::deleteFtpUser(std::string name)
{
    logindb->del(name);
    _autofsc->deleteEntry(name);
}

void FtpUserController::changeFtpPassword(std::string name, std::string pass)
{
    logindb->change(name, pass);
}

