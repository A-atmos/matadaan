#include <gtkmm.h>
#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include<fstream>


#include "utils.hpp"
#include "../../lib/json.hpp"
#include "userModel.hpp"
#include "blockchain.hpp"

namespace superuser
{
    std::string id="admin";
    std::string pwd="admin";

}



class Enter :public Gtk:: Window{
public:
    bool loggedIn;
    bool running;
    void show_login_page();
    void on_button_clicked();
    bool checkclicked();
    bool checksuperuser();
    void loginError(std::string errorMessage);
    USER::User loggedUser();

    Enter(Blockchain::Blockchain& _blockchain){
        // loads the user data from file and make it the vector of users

        user = USER::loadData("user.txt");
        blockchain = _blockchain.toJson();

        add(scrolledWindow);                //adds window
        scrolledWindow.add(fixed);

        //creates textbox for id
        label1.set_text("Citizenship No:");
        fixed.add(label1);
        fixed.move(label1, 240, 100);
        label1.set_size_request(10, 10);
        usernameTextbox.set_text("");
        fixed.add(usernameTextbox);
        fixed.move(usernameTextbox, 240, 130);
        usernameTextbox.set_size_request(50, 10);

        //creates textbox for password
        label2.set_text("Password:");
        fixed.add(label2);
        fixed.move(label2, 240, 180);
        label2.set_size_request(10, 10);
        passwordTextbox.set_text("");
        fixed.add(passwordTextbox);
        fixed.move(passwordTextbox, 240, 200);
        passwordTextbox.set_size_request(170, 10);



        //creates login button
        loginButton.set_label("Log In");
        fixed.add(loginButton);
        fixed.move(loginButton, 280, 250);
        loginButton.set_size_request(10, 10);

        loginButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                           &Enter::on_button_clicked));//calls on_button_clicked function if login button is clicked

        set_title("D-Voting Application");       //sets window title
        move(320, 200);
        resize(640, 480);

        show_all();

    }

    //asks if u wanna exit
    bool on_delete_event(GdkEventAny* any_event) override {
        Gtk::MessageDialog dialog(*this, "Please Login as Superuser to exit.", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_CLOSE, true);

        dialog.set_title("Sorry");
        dialog.set_modal();
        dialog.set_size_request(100,20);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if (dialog.run() == Gtk::RESPONSE_CLOSE){
            return true;

        }
        running = true;
        return true;
    }

private:

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Fixed fixed;
    Gtk::Label label1, label2;
    Gtk::Entry usernameTextbox;
    Gtk::Entry passwordTextbox;
    Gtk::Button loginButton;
    Gtk::Button errorButton;
    std::vector<USER::User> user;
    nlohmann::json blockchain;
};



//is called when login button is clicked
void  Enter::on_button_clicked(){
    try{
        if(!loggedUser().exists()){
            throw USER::UserDoesnotExist();
        }

        if(loggedUser().alreadyVoted(blockchain)){
            throw USER::UserAlreadyVoted();
        }
        hide();
        loggedIn = true;
    }
    catch(USER::UserAlreadyVoted){
        loginError("You have already voted!");
    }
    catch(USER::UserDoesnotExist){
        loginError("Please Register to Vote!");
    }

}

USER::User Enter::loggedUser() {

    for(int i = 0; i<user.size(); i++){
        // std::cout<<user[i].id()<<":"<<user[i].password()<<std::endl;
        if(user[i].id() == usernameTextbox.get_text() && user[i].password() == hash::sha256(passwordTextbox.get_text())){
            return user[i];
        }
    }
    loggedIn = false;
    return {};
}

//checks if login button is clicked
bool Enter::checkclicked()
{
    return loggedIn;
}

//checks if user is superuser
bool Enter::checksuperuser()
{
    std::string id=usernameTextbox.get_text();;
    std::string pwd=passwordTextbox.get_text();;
    if(superuser::id==id && superuser::pwd==pwd)
    {
        return true;
    }
}

//prints error if login failed
void Enter::loginError(std::string errorMessage) {

    Gtk::MessageDialog dialog(*this, errorMessage, true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK, true);

    dialog.set_title("Error: "+errorMessage);
    dialog.set_modal();
    dialog.set_size_request(100,20);
    dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    if (dialog.run() == Gtk::RESPONSE_OK)
        show();


}


//used for creating window after logging in

class voteWindow: public Gtk::Window{
public:
    const int h_elements = 6;
    voteWindow(USER::User _user, Blockchain::Blockchain& _blockchain);
    virtual ~voteWindow();

protected:
    void on_button_click(int,int, Blockchain::Blockchain& _blockchain);
private:
    Gtk::ScrolledWindow scrolledWindow;
    std::vector<Gtk::Button*> board;
    USER::User currentUser;
    std::vector<CANDIDATE::candidate> candidates;

};

voteWindow::voteWindow(USER::User _user,Blockchain::Blockchain& _blockchain) {

    this->fullscreen();

    try {
        add(scrolledWindow);
        currentUser = _user;
        candidates = CANDIDATE::loadFromFile();
//        this->fullscreen();
        set_title("Please Vote to your favourite candidate!");

        Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
        scrolledWindow.add(*vbox);


        auto msg = Gtk::manage(new Gtk::Label("Federal Elections of Nepal - 2080"));
        auto attrlist = pango_attr_list_new();

        PangoFontDescription *font_desc = pango_font_description_new();
        pango_font_description_set_size(font_desc, 36 * PANGO_SCALE);
        PangoAttribute *attr = pango_attr_font_desc_new(font_desc);
        pango_attr_list_insert(attrlist, attr);

        msg->set_hexpand(true);
        auto list = Pango::AttrList(attrlist);
        msg->set_attributes(list);

        vbox->add(*msg);
        auto lab = Gtk::manage(new Gtk::Label(""));
        lab->set_hexpand(true);
        vbox->add(*lab);

        int height = candidates.size() / h_elements;
        height++;

        int h_pos = 0;


        for (int i = 0; i < height; ++i) {

            Gtk::HBox *hbox = Gtk::manage(new Gtk::HBox);
            hbox->set_hexpand(true);

            while (!(h_pos == h_elements || i * h_elements + h_pos == candidates.size())) {
                Gtk::Image *image;
                image = Gtk::manage(new Gtk::Image{candidates[i * h_elements + h_pos].getImagePath()});
                // image->property_width_request(100);
                // image->property_height_request(100);

                auto position = Gtk::manage(new Gtk::Button);
                position->set_image(*image);
                position->set_label(candidates[i * h_elements + h_pos].getName());


                board.push_back(position);

                position->signal_clicked().connect(
                        [this, h_pos, i, &_blockchain] { this->on_button_click(h_pos, i, _blockchain); });

                hbox->add(*position);
                h_pos++;
            }
            h_pos = 0;
            vbox->add(*hbox);
        }


        show_all();

    }catch(...){
        Gtk::MessageDialog dialog(*this, "Error: Please Check if there is a candidates list!", true, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);

        dialog.set_title("Error");
        dialog.set_modal();
        dialog.set_size_request(100,20);
        dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        if(dialog.run() == Gtk::RESPONSE_CLOSE){
            hide();
            exit(1);
        }
    }
}


void voteWindow::on_button_click(int x,int y, Blockchain::Blockchain& _blockchain) {
    Gtk::MessageDialog dialog(*this, "Do you want to confirm your vote?", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);

    dialog.set_title("Vote Confirmation");
    dialog.set_modal();
    dialog.set_size_request(100,20);
    dialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    if (dialog.run() == Gtk::RESPONSE_YES) {

        std::vector<std::string> data;
        std::cout << currentUser.id() << ":" << hash::sha256(currentUser.id()) << ":" << candidates[x + y * h_elements].getName()
                  << std::endl;
        data.push_back(hash::sha256(currentUser.id()));
        data.emplace_back(candidates[x + y * h_elements].getName());

        auto hash_nonce_pair = _blockchain.findNewHash(data);

        _blockchain.addBlock(_blockchain.numOfBlocks(), _blockchain.getLatestBlockHash(), hash_nonce_pair.first,
                             hash_nonce_pair.second, data);

        std::thread (Blockchain::sendBlockchainToPeerNodes,std::ref(_blockchain)).detach();
        
        Gtk::MessageDialog registeredDialog(*this, "Your vote has been sucessfully registered!", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK, true);

        registeredDialog.set_title("Confirmed Vote");
        registeredDialog.set_modal();
        registeredDialog.set_size_request(100,20);
        registeredDialog.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
        
        if(registeredDialog.run() == Gtk::RESPONSE_OK){
            hide();
        }
        
        
    }
}

voteWindow::~voteWindow(){}