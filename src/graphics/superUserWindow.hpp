//
// Created by Amrit on 8/7/2022.
//

#ifndef MATADAAN_SUPERUSERWINDOW_HPP
#define MATADAAN_SUPERUSERWINDOW_HPP

#include <iostream>
#include <gtkmm.h>
#include "../blockchain.hpp"

class SuperUser : public Gtk::Window
{
public:
    bool exit;
    SuperUser(USER::User _user, Blockchain::Blockchain &blockchain);

    // Destructor called
    ~SuperUser() {}

    // Call when the RegisteruserButton is clicked
    void on_RegisteruserButton_clicked();
    // Call when the RegisterpartyButton is clicked
    void on_RegisterpartyButton_clicked();
    void on_addbutton_clicked(Blockchain::Blockchain &blockchain);
    void on_click_logout();

private:
    Gtk::Fixed fixed, fixed1, fixed2, fixed3, fixed7;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Notebook Selector;
    Gtk::Frame S1, S2, S3, S4;
    Gtk::Entry passwordTextbox, CnNoTextbox, PartyNameTextbox, CandidateTextbox, ResultTextbox, ResultTextbox1;
    Gtk::Button RegisteruserButton, RegisterpartyButton, addbutton, Logout;
    Gtk::Label label1, label2, label3, label4, label5, toplabel, toplabel1, label7, label8;

    bool on_delete_event(GdkEventAny *any_event) override // shows the dialog box while attempting to close window
    {
        Gtk::MessageDialog dialog(*this, "You will end up ending the voting process.\nPlease Confirm to exit!", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

        dialog.set_title("Close");
        dialog.set_modal();
        dialog.set_size_request(200, 50);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if (dialog.run() == Gtk::RESPONSE_YES)
        {
            exit = true;
            return Window::on_delete_event(any_event);
        }
        return true;
    }
};

SuperUser::SuperUser(USER::User _user, Blockchain::Blockchain &blockchain)
{
    this->resize(1920, 1080);
    set_border_width(5);
    add(scrolledWindow);       // scrollwindow is added
    scrolledWindow.add(fixed); // fixed container

    fixed.add(Selector); // adding the notebook(selector)
    Selector.set_size_request(1920, 1080);

    Selector.insert_page(S1, "Add Voter", 0); // S1,S2,S3 are the frame widgets which are added to notebook
    Selector.insert_page(S2, "Add Contender", 1);
    Selector.insert_page(S4, "Settings", 2);

    //    S3.override_background_color(Gdk::RGBA("#abaaa7"));
    //    S2.override_background_color(Gdk::RGBA("#abaaa7"));
    //    S1.override_background_color(Gdk::RGBA("#abaaa7"));
    //    S4.override_background_color(Gdk::RGBA("#abaaa7"));

    S4.add(fixed7);

    auto attlist = pango_attr_list_new();
    PangoFontDescription *font_desc = pango_font_description_new();
    pango_font_description_set_size(font_desc, 20 * PANGO_SCALE);
    PangoAttribute *attr3 = pango_attr_font_desc_new(font_desc);
    pango_attr_list_insert(attlist, attr3);

    auto list3 = Pango::AttrList(attlist);

    label7.set_text("Settings");
    label7.set_attributes(list3);
    fixed7.add(label7);
    fixed7.move(label7, 740, 100);
    label7.set_size_request(400, 20);
    label7.override_background_color(Gdk::RGBA("#D3D3D3"));

    label8.set_text("Node:");
    fixed7.add(label8);
    fixed7.move(label8, 740, 420);
    label8.set_size_request(10, 10);

    ResultTextbox1.set_text("");
    fixed7.add(ResultTextbox1); // adds the textbox named "ResultTextbox"
    fixed7.move(ResultTextbox1, 740, 450);
    ResultTextbox1.set_size_request(400, 10);

    Logout.set_label("Logout");
    fixed7.add(Logout);
    fixed7.move(Logout, 840, 600);
    Logout.set_size_request(200, 10);
    Logout.signal_clicked().connect([this]
                                    { this->on_click_logout(); });

    addbutton.set_label("Add"); // adds the button named "RegisterPartyButton"
    fixed7.add(addbutton);
    fixed7.move(addbutton, 840, 500);
    addbutton.set_size_request(200, 10);
    addbutton.signal_clicked().connect([this, &blockchain]
                                       { this->on_addbutton_clicked(blockchain); });
    //    addbutton.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_addbutton_clicked));

    S2.add(fixed2);

    pango_font_description_set_size(font_desc, 20 * PANGO_SCALE);
    PangoAttribute *attr1 = pango_attr_font_desc_new(font_desc);
    pango_attr_list_insert(attlist, attr1);

    auto list1 = Pango::AttrList(attlist);
    toplabel.set_text("Add A Candidate");
    toplabel.set_attributes(list1);
    fixed2.add(toplabel);
    fixed2.move(toplabel, 740, 100);
    toplabel.set_size_request(400, 20);

    label2.set_text("Candidate Name:");
    fixed2.add(label2);
    fixed2.move(label2, 740, 370);
    label2.set_size_request(10, 10);

    CandidateTextbox.set_text("");
    fixed2.add(CandidateTextbox); // adds the textbox named "CandidateTextbox"
    fixed2.move(CandidateTextbox, 740, 400);
    CandidateTextbox.set_size_request(400, 10);

    label3.set_text("Path For Election Symbol:"); // adding the label
    fixed2.add(label3);
    fixed2.move(label3, 740, 450);
    label3.set_size_request(10, 10);

    PartyNameTextbox.set_text("");
    fixed2.add(PartyNameTextbox); // adds the textbox named "ResultTextbox"
    fixed2.move(PartyNameTextbox, 740, 480);
    PartyNameTextbox.set_size_request(400, 10);

    RegisterpartyButton.set_label("Register"); // adds the button named "RegisterPartyButton"
    fixed2.add(RegisterpartyButton);
    fixed2.move(RegisterpartyButton, 840, 530);
    RegisterpartyButton.set_size_request(200, 10);
    RegisterpartyButton.signal_clicked().connect(sigc::mem_fun(*this, &SuperUser::on_RegisterpartyButton_clicked));
    // connects the button

    S1.add(fixed1);
    pango_font_description_set_size(font_desc, 20 * PANGO_SCALE);
    PangoAttribute *attr2 = pango_attr_font_desc_new(font_desc);
    pango_attr_list_insert(attlist, attr2);

    auto list2 = Pango::AttrList(attlist);
    toplabel1.set_attributes(list1);
    toplabel1.set_text("Add A Voter");
    fixed1.add(toplabel1);
    fixed1.move(toplabel1, 740, 100);
    toplabel1.set_size_request(400, 20);

    label5.set_text("Citizenship No:");
    fixed1.add(label5);
    fixed1.move(label5, 740, 370);
    label5.set_size_request(10, 10);

    CnNoTextbox.set_text("");
    fixed1.add(CnNoTextbox); // adds the textbox named "CnNoTextbox"
    fixed1.move(CnNoTextbox, 740, 400);
    CnNoTextbox.set_size_request(400, 10);

    label4.set_text("Password:");
    fixed1.add(label4);
    fixed1.move(label4, 740, 450);
    label4.set_size_request(10, 10);

    passwordTextbox.set_text("");
    fixed1.add(passwordTextbox); // adds the textbox named "passwordTextbox"
    fixed1.move(passwordTextbox, 740, 480);
    passwordTextbox.set_size_request(400, 10);

    RegisteruserButton.set_label("Register");
    fixed1.add(RegisteruserButton); // adds the button named "RegisterUserButton"
    fixed1.move(RegisteruserButton, 840, 530);
    RegisteruserButton.set_size_request(200, 10);
    //[this,&blockchain] {this->on_RegisteruserButton_clicked(blockchain);}
    RegisteruserButton.signal_clicked().connect([this]
                                                { this->on_RegisteruserButton_clicked(); });

    //    ResultTextbox.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    ResultTextbox1.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    passwordTextbox.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    CnNoTextbox.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    CandidateTextbox.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    PartyNameTextbox.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    RegisteruserButton.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    RegisterpartyButton.override_background_color(Gdk::RGBA("#D3D3D3"));
    //    addbutton.override_background_color(Gdk::RGBA("#D3D3D3"));

    set_title("SuperUser Screen"); // title of the window
    show_all();
}

void SuperUser::on_addbutton_clicked(Blockchain::Blockchain &blockchain)
{
    //    ResultTextbox1
    blockchain.add_node(ResultTextbox1.get_text());
    Gtk::MessageDialog dialog(*this, "Added Node:" + ResultTextbox1.get_text(), true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK, true);

    dialog.set_title("Node Added");
    dialog.set_modal();
    dialog.set_size_request(100, 20);
    dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    if (dialog.run() == Gtk::RESPONSE_OK)
        show();
}

void SuperUser::on_RegisteruserButton_clicked()
{
    USER::saveUser(CnNoTextbox.get_text(), passwordTextbox.get_text());
    Gtk::MessageDialog dialog(*this, "Added Voter:" + CnNoTextbox.get_text(), true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK, true);

    dialog.set_title("Voter Added");
    dialog.set_modal();
    dialog.set_size_request(100, 20);
    dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    if (dialog.run() == Gtk::RESPONSE_OK)
        show();
}

void SuperUser::on_RegisterpartyButton_clicked()
{
    std::cout << "Registered Candidate" << std::endl;
}

void SuperUser::on_click_logout()
{
    Gtk::MessageDialog dialog(*this, "Please Confirm to logout!", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

    dialog.set_title("Logout");
    dialog.set_modal();
    dialog.set_size_request(200, 50);
    dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    if (dialog.run() == Gtk::RESPONSE_YES)
    {
        exit = false;
        hide();
    }
}

#endif // MATADAAN_SUPERUSERWINDOW_HPP
