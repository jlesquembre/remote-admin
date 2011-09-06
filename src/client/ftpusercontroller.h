#ifndef FTPUSERCONTROLLER_H
#define FTPUSERCONTROLLER_H

#include "../server/logindb.h"
#include "../server/autofscontroller.h"
#include "./ftpuser.h"
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTextEdit>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WDialog>
#include <Wt/WLineEdit>
#include <string>

namespace messageType
{
enum Enum
{
    SUCCESS,
    ERROR,
    WARNING
};
}

class FtpUserController : public Wt::WContainerWidget
{
public:
    FtpUserController(Wt::WContainerWidget *parent);
    void showNotification(messageType::Enum, Wt::WString);
    void hideNotification();
    void changeFtpPassword(std::string, std::string);
    void deleteFtpUser(std::string);
private:
    LoginDB *logindb;
    AutofsController *_autofsc;

    Wt::WText *notificationArea, *error;
    Wt::WDialog *addFtpUSerDialog;
    Wt::WLineEdit *newFtpUser, *newFtpPass, *newFtpRepass;
    void showDialog();
    void hideDialog();
    void addFtpUser();
    void wDialogAddFtpUser();

};



#endif // FTPUSERCONTROLLER_H
