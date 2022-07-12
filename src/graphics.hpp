#include <gtkmm.h>
class Enter :public Gtk:: Window {
public:
    void on_button_clicked();

    Enter()
    {
        add(scrolledWindow);
        scrolledWindow.add(fixed);


        textbox1.set_text("Enter Citizenship number");
        fixed.add(textbox1);
        fixed.move(textbox1, 240, 150);
        //textbox1.set_size_request(50,10);


        textbox2.set_text("Password");
        fixed.add(textbox2);
        fixed.move(textbox2, 240, 200);
        textbox2.set_size_request(170,10);




        button.set_label("Log In");
        fixed.add(button);
        fixed.move(button, 280, 250);
        button.set_size_request(10,10);

        button.signal_clicked().connect(sigc::mem_fun(*this,
                                                      &Enter::on_button_clicked));

        set_title("Matadaan Garau,Desh Banau");
        move(320, 200);
        resize(640, 480);

        show_all();
    }


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
    Gtk::ScrolledWindow scrolledWindow;

    Gtk::Fixed fixed;
    Gtk::Entry textbox1;
    Gtk::Entry textbox2;
    Gtk::Button button;
    Gtk::Button button1;
    Gtk::Button button2;
};
void  Enter::on_button_clicked()
{
    hide();



};
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

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    Enter enter;

    //Shows the window and returns when it is closed.
    Gtk::Main::run(enter);
    login log;

    //Shows the window and returns when it is closed.
    Gtk::Main::run(log);




    return 0;
}
