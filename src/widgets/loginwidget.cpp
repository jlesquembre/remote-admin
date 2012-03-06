#include "loginwidget.h"

#include <Wt/WContainerWidget>
#include <Wt/WCompositeWidget>
#include <Wt/WPushButton>
#include <Wt/WText>

using namespace Wt;

LoginWidget::LoginWidget(WContainerWidget *parent):
  WCompositeWidget(parent)
{

    setImplementation(_impl = new WContainerWidget());
    _impl->setStyleClass("center-block");

    WContainerWidget *container = new WContainerWidget(_impl);
    container->setStyleClass("center");

    new WText("Name",container);

    WPushButton *login = new WPushButton("GO!!!",container);
    login->setStyleClass("button white");
    login->clicked().connect(this, &LoginWidget::emitt);
    //login->clicked().emit();


}

void LoginWidget::emitt(){
    _loggedIn.emit();
}
