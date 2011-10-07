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



    /*
    boost::property_tree::ini_parser::read_ini;

    new boost::property_tree::ptree();

     boost::property_tree::ptree a;




    */


    //this->setCssTheme("polished");

    setTitle("Main page");
    //wApp->require("http://code.jquery.com/jquery-1.6.1.min.js");

    this->useStyleSheet("css/style.css");

    //this->setCssTheme("");

    userList = new WContainerWidget(root());
    userList->setStyleClass("list");
    //userList->sets

    //WText *a = new WText(logindb->getFirstKey(), root());



  /*    logindb = new LoginDB();
    std::vector <std::string> names = logindb->getKeys();

    std::vector<std::string>::iterator it;
    for(it = names.begin(); it < names.end(); it++)
        {

            new WText(*it, userList);
            new WLineEdit(userList);
            WPushButton *btn = new WPushButton("Modify name",userList);
            btn->clicked().connect(this,&MainPage::modifyEntry);

            new WBreak(userList);

        }
*/



    //new FtpUserController(root());
    //new FtpUserController(examples);


    WContainerWidget *a = new WContainerWidget();
    a->addStyleClass("overhidden");
    //a->setStyleClass("ttt");

    WVBoxLayout *ftpLayout = new WVBoxLayout(a);
    ftpLayout->setSpacing(0);
    ftpLayout->setContentsMargins(0, 10, 10, 10);
    Wt::WStackedWidget *ftpContents = new Wt::WStackedWidget(0);
    Wt::WMenu *ftpMenu = new Wt::WMenu(ftpContents, Wt::Horizontal, 0);
    ftpMenu->setRenderAsList(true);
    ftpMenu->addStyleClass("tabs");
    ftpLayout->addWidget(ftpMenu);
    ftpLayout->addWidget(ftpContents,1);
    ftpMenu->addItem("General options", new Wt::WText("Not yet available"));
    ftpMenu->addItem("Users management", new FtpUserController());

    ftpContents->setStyleClass("contents");
    //ftpMenu->addStyleClass("mmenu");

    WVBoxLayout *sambaLayout = new WVBoxLayout();
    Wt::WStackedWidget *sambaContents = new Wt::WStackedWidget(0);
    Wt::WMenu *sambaMenu = new Wt::WMenu(sambaContents, Wt::Horizontal, 0);
    sambaMenu->setRenderAsList(true);
    sambaMenu->addStyleClass("menu");






    Wt::WHBoxLayout *mainLayout = new Wt::WHBoxLayout(root());
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    //WVBoxLayout * secondl = new WVBoxLayout();
    //mainLayout->addLayout(secondl);

    Wt::WStackedWidget *contents = new Wt::WStackedWidget(0);
    contents->setOverflow(WContainerWidget::OverflowAuto);
    //contents->setStyleClass("contents");
    contents->setPositionScheme(Relative); // without needs testing on IE...

    // create a menu
    Wt::WMenu *menu = new Wt::WMenu(contents, Wt::Vertical, 0);
    menu->setRenderAsList(true);
    menu->addStyleClass("menu");




    mainLayout->addWidget(menu);
    mainLayout->addWidget(contents,1);
    //mainLayout->addLayout(ftpLayout);
    //mainLayout->addWidget(contents,1);
    //layout->setResizable(0,true);




    menu->addItem("FTP", a);
    menu->addItem("Samba", new Wt::WText("Not yet available"));

    //ftpTabs->addTab(new WText("aa"), "General options");
    //ftpTabs->addTab(new FtpUserController(), "Users management");

//    WContainerWidget *a = new WContainerWidget();
//    mainLayout->addWidget(a);






    /*********
      Test for options file
      ***/

    //namespace pt = boost::property_tree;

    WPushButton *test = new WPushButton("Test!!!",root());

    test->clicked().connect(this, &MainPage::test);

    /*
    Wt::WIconPair *folderIcon = new Wt::WIconPair("icons/yellow-folder-closed.png",
                                                   "icons/yellow-folder-open.png", false);
     Wt::WTree *tree = new Wt::WTree(this->root());
     tree->setSelectionMode(Wt::SingleSelection);

     Wt::WTreeNode *root = new Wt::WTreeNode("Tree root", folderIcon);
     root->setStyleClass("example-tree");
     tree->setTreeRoot(root);
     root->label()->setTextFormat(Wt::PlainText);
     root->setImagePack("resources/");
     root->setLoadPolicy(Wt::WTreeNode::NextLevelLoading);
     root->addChildNode(new Wt::WTreeNode("one"));
     root->addChildNode(new Wt::WTreeNode("two"));

     Wt::WTreeNode *three = new Wt::WTreeNode("three");
     three->addChildNode(new WTreeNode("three: one"));
     three->addChildNode(new WTreeNode("three: two"));
     root->addChildNode(three);

     root->expand();*/

//     Wt::WTree *tree2 = new Wt::WTree(this->root());
//     tree2->setSelectionMode(Wt::SingleSelection);
//     //tree2->setStyleClass("aaa");
//     boost::filesystem::path path("/home/jlle/Descargas");
//     TreeNodeFolder *root2 = new TreeNodeFolder(path);//, folderIcon);
//     tree2->setTreeRoot(root2);


     //cerr<<"hello"<<endl;
     //AutofsController *a = new AutofsController();


}

void MainPage::test()
{


    OptionMap a("/home/jlle/Descargas/DB/vsftpd.conf");
    a.printMap();

    system("ls -la");
    /*
    using boost::property_tree::ptree;

    namespace po = boost::program_options;

    //namespace pt =  boost::property_tree;



    ptree root;

    filebuf fb;
    fb.open ("/home/jlle/Descargas/DB/vsftpd.conf",ios::in);
    istream conf(&fb);



    po::variables_map vm;
    po::options_description desc("Allowed options");
    po::store(po::parse_config_file(conf, desc), vm);
    //store(parse_config_file("example.cfg", desc), vm);
    po::notify(vm);

    fb.close();




    read_ini("/home/jlle/Descargas/DB/vsftpd.conf",root);

    //ptree wave_packet;


    root.put( "width", "1" );
    root.put( "position", "2.0" );

    ptree calculation_parameters;
    calculation_parameters.put( "levels", "15" );
/*
    root.push_front(
                ptree::value_type( "calculation parameters", calculation_parameters )
                );
    root.push_front(
                ptree::value_type( "wave packet", wave_packet )
                );*/

    cout<<" ----------------------------------- "<<endl;

    //write_ini( std::cout, root );

}

void MainPage::hide()
{

    //js = new JSlot(userList);
    //js->setJavaScript("$('.list').hide()");
    //js->exec();
    //std::string googleCmd = "$('.list').hide()";

    doJavaScript("$('.list').hide('slow')");


    //userList->hide();
    //userList->javaScriptMember()
}


void MainPage::show()
{
    doJavaScript("$('.list').show('slow')");
    //userList->show();
    //userList->ja
}


void MainPage::writeText()
{

    //;
    //	std::string temp(text->text().length(), ' ');

    //std::copy(text->text().begin(), text->text().end(), temp.begin());
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
