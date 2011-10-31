#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WString>

namespace messageType
{
enum Enum
{
    SUCCESS,
    ERROR,
    WARNING
};
}

class Notification : public Wt::WContainerWidget
{
public:
    Notification();

    static void displayMessage(Wt::WString, messageType::Enum, int = 4000);


private:
    void updateText(Wt::WString);
    void hideMessage();

    Wt::WText *_message;
    static Notification *s_this;


};


//class Notification : /*public Singleton<Notification>,*/ public Wt::WContainerWidget
//{
//public:
//    static Notification& getInstance()
//            {
//                static Notification instance; // Guaranteed to be destroyed.
//                                              // Instantiated on first use.
//                return instance;
//            }


//private:
//    //
//    static Wt::WText _message;
//    Notification();

//};




#endif // NOTIFICATION_H
