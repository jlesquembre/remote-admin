#ifndef FTPUSER_H
#define FTPUSER_H

#include "../server/logindb.h"
#include "../server/optionmap.h"
#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WSignal>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WDialog>
#include <vector>
#include <string>

class FtpUser : public Wt::WContainerWidget
{
public:
    FtpUser(std::string name, Wt::WContainerWidget *parent);
    ~FtpUser();

    static void init();
    void deleteUser();

private:
    static int n;
    static FtpUser* openUser;
    static string userConfPath;

    //std::string name;
    Wt::WText *name, *error;
    Wt::WContainerWidget *changePassArea, *dropDownBody, *dropDownHead, *dropDown, *arrow;
    Wt::WLineEdit *pass, *repass;
    Wt::WDialog *addFolderDialog;

    OptionMap *options;

    void openCloseUser();
    void changePassword();

    void createConfFile();

    Wt::WContainerWidget *createFoldersBlock();
    void showDialog();
    void hideDialog();





};



#endif // FTPUSER_H
