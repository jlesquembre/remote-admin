#include "tabwidget.h"
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WMenu>
#include <Wt/WString>
#include <Wt/WWidget>

#include <iostream>

using namespace Wt;

TabWidget::TabWidget() : WContainerWidget()
{
    //WContainerWidget *a = new WContainerWidget();
    //this->setStyleClass("");
    //this->addStyleClass("overhidden");
    //a->addStyleClass("overhidden");



    WVBoxLayout *ftpLayout = new WVBoxLayout(this);  //_impl->addWidget(ftpLayout);
    ftpLayout->setSpacing(0);
    ftpLayout->setContentsMargins(0, 0, 0, 0);
    Wt::WStackedWidget *ftpContents = new Wt::WStackedWidget(0);
    ftpContents->addStyleClass("contents");
    //Wt::WMenu *_menu = new Wt::WMenu(ftpContents, Wt::Horizontal, 0);
    _menu = new Wt::WMenu(ftpContents, Wt::Horizontal, 0);
    _menu->setRenderAsList(true);
    _menu->addStyleClass("tabs");
    ftpLayout->addWidget(_menu);
    ftpLayout->addWidget(ftpContents,1);

    //ftpContents->setOverflow(OverflowAuto);
    //ftpContents->setLayout(AlignTop);


   // std::cout<<"H>>>>>>>>>> " <<ftpContents->height().value()<<std::endl;

    //_menu->setHeight(WLength::Auto);
    //ftpContents->setHeight(WLength::Auto);
    //ftpContents->setHeight(WLength(500,UniPixel));
    //ftpLayout->setLayoutHint("height","100%");
    //_menu->addItem("General options", new Wt::WText("Not yet available"));
    //_menu->addItem("Users management", new FtpUserController());


}

void TabWidget::addTab(const Wt::WString &label, Wt::WWidget *widget)
{

//    WContainerWidget *wrapper = new WContainerWidget();
//    wrapper->setStyleClass("test1");
//    wrapper->addWidget(widget);
    widget->addStyleClass("tabcontent");
    _menu->addItem(label,widget);
}
