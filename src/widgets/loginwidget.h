#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <Wt/WCompositeWidget>
#include <Wt/WContainerWidget>

class LoginWidget : public Wt::WCompositeWidget
{
public:
    LoginWidget( Wt::WContainerWidget *parent = 0);
    void emitt();

    Wt::Signal<>&loggedIn() { return _loggedIn; }

private:
  //Wt::WText              *introText_;
  Wt::WLineEdit          *_username;
  Wt::WLineEdit          *_password;
  //Wt::WComboBox          *language_;
  //Wt::WTemplate          *impl_;

  Wt::WContainerWidget *_impl;


  Wt::Signal<> _loggedIn;

  void checkCredentials();


};

#endif // LOGINWIDGET_H
