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
        ResultTextbox.set_text("Candidate Name");
        fixed3.add(ResultTextbox);//adds the textbox named "ResultTextbox"
        fixed3.move(ResultTextbox, 850, 450);
        ResultTextbox.set_size_request(50, 10);

        S2.add(fixed2);
        CandidateTextbox.set_text("Candidate Name");
        fixed2.add(CandidateTextbox); // adds the textbox named "CandidateTextbox"
        fixed2.move(CandidateTextbox, 850, 400);
        CandidateTextbox.set_size_request(50, 10);

        PartyNameTextbox.set_text("Party Name");
        fixed2.add(PartyNameTextbox); // adds the textbox named "ResultTextbox"
        fixed2.move(PartyNameTextbox, 850, 450);
        PartyNameTextbox.set_size_request(50, 10);

        RegisterpartyButton.set_label("Register"); // adds the button named "RegisterPartyButton"
        fixed2.add(RegisterpartyButton);
        fixed2.move(RegisterpartyButton, 890, 500);
        RegisterpartyButton.set_size_request(10, 10);
        RegisterpartyButton.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_RegisterpartyButton_clicked));
// connects the button 
        S1.add(fixed1);
        CnNoTextbox.set_text("Citizenship No.");
        fixed1.add(CnNoTextbox); // adds the textbox named "CnNoTextbox"
        fixed1.move(CnNoTextbox, 850, 400);
        CnNoTextbox.set_size_request(50, 10);

        passwordTextbox.set_text("Password");
        fixed1.add(passwordTextbox); // adds the textbox named "passwordTextbox"
        fixed1.move(passwordTextbox, 850, 450);
        passwordTextbox.set_size_request(50, 10);

        RegisteruserButton.set_label("Register");
        fixed1.add(RegisteruserButton); // adds the button named "RegisterUserButton"
        fixed1.move(RegisteruserButton, 890, 500);
        RegisteruserButton.set_size_request(10, 10);

        RegisteruserButton.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_RegisteruserButton_clicked));
        set_title("SuperUser Screen");//title of the window
        show_all();
    }
    
    //Destructor called
    ~SuperUser()
    {
    }

    // Call when the RegisteruserButton is clicked
    void on_RegisteruserButton_clicked()
    {
        std::cout << "Registered Voter" << std::endl;
    }
    // Call when the RegisterpartyButton is clicked
    void on_RegisterpartyButton_clicked()
    {
        std::cout << "Registered Candidate" << std::endl;
    }

private:
    Gtk::Fixed fixed, fixed1, fixed2, fixed3;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Notebook Selector;
    Gtk::Frame S1, S2, S3;
    Gtk::Entry passwordTextbox, CnNoTextbox, PartyNameTextbox, CandidateTextbox, ResultTextbox;
    Gtk::Button RegisteruserButton, RegisterpartyButton;

    bool on_delete_event(GdkEventAny *any_event) override// shows the dialog box while attempting to close window
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
