/*
 * MainPage.h
 *
 *  Created on: 19/04/2011
 *      Author: Jose Luis Lafuente
 */
#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include <Wt/WJavaScript>
#include "../server/WriteConf.h"
#include "../server/logindb.h"

using namespace Wt;

#ifndef MAINPAGE_H_
#define MAINPAGE_H_

class MainPage : public WApplication
{
public:
	MainPage(const WEnvironment& env);
	void writeText();
        void saveToDb();
        void modifyEntry();
        void show();
        void hide();




private:

        JSlot *js;
        WContainerWidget *userList;
        WPushButton *button, *showb, *hideb;
        WLineEdit *text, *user, *pass;
        LoginDB *logindb;
	WriteConf wc;
        void test();



  //void greet();
};

#endif /* MAINPAGE_H_ */


