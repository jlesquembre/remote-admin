/*
 * MainPage.cpp
 *
 *  Created on: 19/04/2011
 *      Author: Jose Luis Lafuente
 */

#include "MainPage.h"
#include "../server/logindb.h"
#include "../server/optionmap.h"
#include "../server/treenodefolder.h"
#include "../server/autofscontroller.h"
#include "../server/apppaths.h"
#include "../widgets/tabwidget.h"
#include "../widgets/loginwidget.h"
#include "../services/notification.h"
#include "ftpusercontroller.h"

#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WSignal>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WJavaScript>
#include <Wt/WIconPair>
#include <Wt/WTree>
#include <Wt/WTreeNode>
#include <Wt/WTabWidget>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WCssDecorationStyle>

#include <stdlib.h>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/filesystem/path.hpp>

#include <vector>
#include <string>

/*
#define JS(...) #__VA_ARGS__

const char *someJs = JS(

    alert("Hi!!");
  var Foo = function(java, script, here) {
    var a, b;

    this.eatCrocodile = function(d) {
       d.innerHTML = "Eating it now";
    }
  };
);*/


using namespace Wt;






MainPage::MainPage( const WEnvironment& env)    
    : WApplication(env)
{

    setTitle("Main page");

    this->useStyleSheet(AppPaths::cssFile);

    // Remove this 2 lines???
    userList = new WContainerWidget(root());
    userList->setStyleClass("list");


    // Remove it?
    WContainerWidget *t = new WContainerWidget();
    t->setInline(false);
    t->show();
    t->setStyleClass("big");    

    // Remove it?
    WStackedWidget *main = new WStackedWidget(root());
    main->setStyleClass("");    

    root()->removeWidget(main);




    Wt::WHBoxLayout *loginLayout = new Wt::WHBoxLayout(root());
    LoginWidget *login = new LoginWidget();
    loginLayout->addWidget(login);
    login->loggedIn().connect(this,&MainPage::setMainPage);
}


void MainPage::setMainPage(){
    Wt::WHBoxLayout *mainLayout = new Wt::WHBoxLayout();
    root()->setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 10, 0, 0);
    mainLayout->setSpacing(0);


    Wt::WStackedWidget *contents = new Wt::WStackedWidget(0);
    contents->setOverflow(WContainerWidget::OverflowAuto);    
    contents->setStyleClass("contentsp");
    contents->setPositionScheme(Relative); // without needs testing on IE...

    // create a menu
    Wt::WMenu *menu = new Wt::WMenu(contents, Wt::Vertical, 0);
    menu->setRenderAsList(true);
    menu->addStyleClass("menu");

    mainLayout->addWidget(menu);
    mainLayout->addWidget(contents,1);
    mainLayout->addWidget(new Notification());    

    TabWidget *ftp = new TabWidget();
    ftp->addTab("General options", new Wt::WText("Not yet available"));
    ftp->addTab("Users management", new FtpUserController());

    TabWidget *samba = new TabWidget();
    samba->addTab("General options", new Wt::WText("Not yet available"));
    samba->addTab("More options", new Wt::WText("Not yet available"));

    menu->addItem("FTP", ftp);
    menu->addItem("Samba", samba);



    std::vector<WWidget*>::const_iterator a;

    for(a = root()->children().begin();
        a < (root()->children().end());
        a++){        

        if (dynamic_cast<WText*>(*a) != NULL)
          {
            std::cout << dynamic_cast<WText*>(*a)->text() << std::endl;
          }
    }

}

void MainPage::test()
{


    OptionMap a("/home/jlle/Descargas/DB/vsftpd.conf");
    a.printMap();

    system("ls -la");
    cout<<" ----------------------------------- "<<endl;


}

void MainPage::hide()
{    

    doJavaScript("$('.list').hide('slow')");

}


void MainPage::show()
{
    doJavaScript("$('.list').show('slow')");    
}


void MainPage::writeText()
{    
    wc.setText(text->text().toUTF8());
    wc.writeLog();

}

void MainPage::modifyEntry()
{

}

void MainPage::saveToDb()
{

    logindb->add(user->text().toUTF8(), pass->text().toUTF8());
    new WText(user->text().toUTF8(),userList);
    new WBreak(userList);
    user->setText("");
    pass->setText("");

}




WApplication *createApplication(const WEnvironment& env)
{
    return new MainPage(env);
}

int main(int argc, char **argv)
{
    return WRun(argc, argv, &createApplication);
}
