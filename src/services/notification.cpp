#include "notification.h"

#include <Wt/WText>
#include <Wt/WAnimation>
#include <Wt/WTimer>
#include <Wt/WString>

using namespace Wt;

//Wt::WText *Notification::_message;
Notification *Notification::s_this;

Notification::Notification()
{


    //_message.setText("Hello World!!!!");
    s_this = this;
    _message = new Wt::WText(this);

    //this->addWidget(&_message);
    //this->setStyleClass("big");
    this->hide();


}

void Notification::displayMessage(WString message, messageType::Enum type, int ms)
{
    //_message->setText(message);
    s_this->updateText(message);

    switch(type){
    case messageType::SUCCESS:
        s_this->setStyleClass("success");
        break;
    case messageType::ERROR:
        s_this->setStyleClass("error");
        break;
    case messageType::WARNING:
        s_this->setStyleClass("warning");
        break;
    }

    //s_this->show();
    s_this->animateShow(WAnimation(WAnimation::SlideInFromTop, WAnimation::EaseInOut, 100));

    Wt::WTimer::singleShot(ms,s_this,&Notification::hideMessage);


}

void Notification::updateText(WString text)
{
    _message->setText(text);
}

void Notification::hideMessage()
{
    //this->hide();
    this->animateHide(WAnimation(WAnimation::SlideInFromTop, WAnimation::EaseInOut, 500));
}
