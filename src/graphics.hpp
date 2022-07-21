#include <gtkmm.h>
#include <iostream>
#include <cstring>
//#include <vector>
//#include<fstream>


namespace superuser
{
    std::string id="admin";
    std::string pwd="admin";

}

class Enter :public Gtk:: Window {
public:

    void on_button_clicked();
    int checkclicked();
    bool checksuperuser();
    void for_error();

    Enter()
    {
        add(scrolledWindow);                //adds window
        scrolledWindow.add(fixed);

        //creates textbox for id
        textbox1.set_text("Enter Citizenship number");
        fixed.add(textbox1);
        fixed.move(textbox1, 240, 150);
        textbox1.set_size_request(50,10);

        //creates textbox foe password
        textbox2.set_text("Password");
        fixed.add(textbox2);
        fixed.move(textbox2, 240, 200);
        textbox2.set_size_request(170,10);



        //creates login button
        button.set_label("Log In");
        fixed.add(button);
        fixed.move(button, 280, 250);
        button.set_size_request(10,10);

        button.signal_clicked().connect(sigc::mem_fun(*this,
                                                      &Enter::on_button_clicked));//calls on_button_clicked function if login button is clicked

        set_title("Matadaan Garau,Desh Banau");       //sets window title
        move(320, 200);
        resize(640, 480);

        show_all();                                         //shows all widgets
    }

    //asks if u wanna exit
    bool on_delete_event(GdkEventAny* any_event) override {
        Gtk::MessageDialog dialog(*this, "matadaan grnu vayo tw??", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

        dialog.set_title("matadaan grnu vayo tw??");
        dialog.set_modal();
        dialog.set_size_request(100,20);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if (dialog.run() == Gtk::RESPONSE_YES)
            return Window::on_delete_event(any_event);
        return true;
    }
protected:
    int count=0;
    Gtk::ScrolledWindow scrolledWindow;

    Gtk::Fixed fixed;
    Gtk::Entry textbox1;
    Gtk::Entry textbox2;
    Gtk::Button button;
    Gtk::Button button0;

};


//is called when login button is clicked
void  Enter::on_button_clicked(){
    if(checksuperuser()==1) {
        hide();
        count++;
    }
    else
    {
        for_error();

    }
}


//checks if login button is clicked
int Enter::checkclicked()
{
    return count;
}


//checks if user is superuser
bool Enter::checksuperuser()
{
    std::string id=textbox1.get_text();;
    std::string pwd=textbox2.get_text();;
    if(superuser::id==id && superuser::pwd==pwd)
    {
        return true;
    }
}

//prints error if login failed
void Enter::for_error() {

    button0.set_label("Error occured while logging in!");
    fixed.add(button0);
    fixed.move(button0, 80, 50);
    button0.set_size_request(200,10);
    show_all();
}

//used for creating window after loging in
class login:public Gtk::Window
{
public:
    login() {
        add(scrolledWindow1);
        scrolledWindow1.add(fixed);

        button1.set_label("Sher bahadur Deuwa          ");
        fixed.add(button1);
        fixed.move(button1, 240, 150);
        button1.set_size_request(70, 10);

        button2.set_label("KP Oli");
        fixed.add(button2);
        fixed.move(button2, 240, 200);
        button2.set_size_request(170, 10);

        set_title("momo channa 10 min vnye,neta channa kina hatar");
        move(320, 200);
        resize(640, 480);

        show_all();
    }
private:
    Gtk::ScrolledWindow scrolledWindow1;
    Gtk::Button button1;
    Gtk::Button button2;
    Gtk::Fixed fixed;

    //asks if u wanna exit
    bool on_delete_event(GdkEventAny* any_event) override {
        Gtk::MessageDialog dialog(*this, "matadaan grnu vayo tw??", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

        dialog.set_title("matadaan grnu vayo tw??");
        dialog.set_modal();
        dialog.set_size_request(100,20);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if (dialog.run() == Gtk::RESPONSE_YES)
            return Window::on_delete_event(any_event);
        return true;
    }


};
//class user
//{
//public:
//    std::vector<std::string>id;
//    std::vector<std::string>password;
//    std::ofstream fout;
//    std::fout.open("data.txt",app);
//};

