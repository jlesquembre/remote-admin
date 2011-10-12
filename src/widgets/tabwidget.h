#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <Wt/WWidget>
#include <Wt/WMenu>

class TabWidget : public Wt::WContainerWidget
{
public:
    TabWidget() ;
    void addTab(const Wt::WString&, Wt::WWidget*);

private:    
    Wt::WMenu *_menu;
   // Wt::WStackedWidget *ftpContents;

};

#endif // TABWIDGET_H
