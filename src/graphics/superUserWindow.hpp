//
// Created by Amrit on 8/7/2022.
//

#ifndef MATADAAN_SUPERUSERWINDOW_HPP
#define MATADAAN_SUPERUSERWINDOW_HPP
#include <iostream>
#include <gtkmm.h>


class SuperUser : public Gtk::Window
{
public:
    SuperUser()
    {
        this->resize(2000, 1900);
        set_border_width(5);
        add(scrolledWindow);       // scrollwindow is added
        scrolledWindow.add(fixed); // fixed container

        fixed.add(Selector); // adding the notebook(selector)
        Selector.set_size_request(2000, 1900);

        Selector.insert_page(S1, "Add Voter", 0); // S1,S2,S3 are the frame widgets which are added to notebook
        Selector.insert_page(S2, "Add Contender", 1);
        Selector.insert_page(S3, "Election Results", 2);

        S3.add(fixed3);
        textbox4.set_text("Candidate Name");
        fixed3.add(textbox4);
        fixed3.move(textbox4, 850, 450);
        textbox4.set_size_request(50, 10);

        S2.add(fixed2);
        textbox3.set_text("Candidate Name");
        fixed2.add(textbox3);
        fixed2.move(textbox3, 850, 400);
        textbox3.set_size_request(50, 10);

        textbox2.set_text("Party Name");
        fixed2.add(textbox2);
        fixed2.move(textbox2, 850, 450);
        textbox2.set_size_request(50, 10);
        // creates login button
        button1.set_label("Register");
        fixed2.add(button1);
        fixed2.move(button1, 890, 500);
        button1.set_size_request(10, 10);
        button1.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_button1_clicked));

        S1.add(fixed1);
        textbox1.set_text("Citizenship No.");
        fixed1.add(textbox1);
        fixed1.move(textbox1, 850, 400);
        textbox1.set_size_request(50, 10);

        textbox.set_text("Password");
        fixed1.add(textbox);
        fixed1.move(textbox, 850, 450);
        textbox.set_size_request(50, 10);
        // creates register button
        button.set_label("Register");
        fixed1.add(button);
        fixed1.move(button, 890, 500);
        button.set_size_request(10, 10);

        button.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_button_clicked));
        set_title("SuperUser Screen");
        show_all();
    }
    ~SuperUser()
    {
    }

    // Call when the button os clicked and display my url
    void on_button_clicked()
    {
        std::cout << "Registered Voter" << std::endl;
    }
    void on_button1_clicked()
    {
        std::cout << "Registered Candidate" <<std::endl;
    }

private:
    Gtk::Fixed fixed, fixed1, fixed2, fixed3;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Notebook Selector;
    Gtk::Frame S1, S2, S3;
    Gtk::Entry textbox, textbox1, textbox2, textbox3, textbox4;
    Gtk::Button button, button1;

    bool on_delete_event(GdkEventAny *any_event) override
    {
        Gtk::MessageDialog dialog(*this, "Do you Want to exit?", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

        dialog.set_title("Want To Exit?");
        dialog.set_modal();
        dialog.set_size_request(100, 30);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if (dialog.run() == Gtk::RESPONSE_YES)
            return Window::on_delete_event(any_event);
        return true;
    }
};

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    SuperUser Sudo;
    Gtk::Main::run(Sudo);
    return 0;
}
#endif // MATADAAN_SUPERUSERWINDOW_HPP
