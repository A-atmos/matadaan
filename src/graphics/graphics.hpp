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
        user=USER::loadData("/home/ac/CLionProjects/matadaan/data.test");
        blockchain = _blockchain.toJson();

        add(scrolledWindow);                //adds window
        scrolledWindow.add(fixed);

        //creates textbox for id
        usernameTextbox.set_text("Enter Citizenship number");
        fixed.add(usernameTextbox);
        fixed.move(usernameTextbox, 240, 150);
        usernameTextbox.set_size_request(50,10);

        //creates textbox for password
        passwordTextbox.set_text("Password");
        fixed.add(passwordTextbox);
        fixed.move(passwordTextbox, 240, 200);
        passwordTextbox.set_size_request(170,10);



        //creates login button
        loginButton.set_label("Log In");
        fixed.add(loginButton);
        fixed.move(loginButton, 280, 250);
        loginButton.set_size_request(10,10);

        loginButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                           &Enter::on_button_clicked));//calls on_button_clicked function if login button is clicked

        set_title("Matadaan Garau,Desh Banau");       //sets window title
        move(320, 200);
        resize(640, 480);

        show_all();
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
        running = false;
        return true;
    }

private:

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Fixed fixed;
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
        if(user[i].id() == usernameTextbox.get_text() && user[i].password() == passwordTextbox.get_text()){
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

    errorButton.set_label(errorMessage);
    fixed.add(errorButton);
    fixed.move(errorButton, 80, 50);
    errorButton.set_size_request(200,10);
    show_all();
}


//used for creating window after logging in

class voteWindow: public Gtk::Window{
public:
    voteWindow(USER::User _user, Blockchain::Blockchain& _blockchain);
    virtual ~voteWindow();

protected:
    void on_button_click(int,int, Blockchain::Blockchain& _blockchain);
private:
    std::vector<Gtk::Button*> board;
    USER::User currentUser;
    std::vector<CANDIDATE::candidate> candidates;

};

voteWindow::voteWindow(USER::User _user,Blockchain::Blockchain& _blockchain) {

    currentUser = _user;
    candidates = CANDIDATE::loadFromFile();
    set_default_size(600,600);
    set_title("Please Vote to your favourite candidate!");

    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    int height = candidates.size()/8;
    height++;

    int h_pos=0,v_pos=0;


    for(int i =0; i<height;++i){

        Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox);
        hbox->set_hexpand(true);

        while(!(h_pos==8 || i*8+h_pos == candidates.size())){
            Gtk::Image *image;
            image = Gtk::manage(new Gtk::Image{candidates[i*8+h_pos].getImagePath()});
            // image->property_width_request(100);
            // image->property_height_request(100);

            auto position = Gtk::manage(new Gtk::Button);
            position->set_image(*image);
            position->set_label(candidates[i*8+h_pos].getName());


            board.push_back(position);

            position->signal_clicked().connect(
                    [this,h_pos,i,&_blockchain] {this->on_button_click(h_pos,i,_blockchain);});

            hbox->add(*position);
            h_pos++;
        }
        h_pos = 0;
        vbox->add(*hbox);
    }



    vbox->show_all();
}


void voteWindow::on_button_click(int x,int y, Blockchain::Blockchain& _blockchain) {
    std::cout<<"("<<x<<","<<y<<")"<<std::endl;

    std::vector<std::string> data;
    std::cout<<currentUser.id()<<":"<<hash::sha256(currentUser.id())<<":"<<candidates[x+y*8].getName()<<std::endl;
    data.push_back(hash::sha256(currentUser.id()));
    data.emplace_back(candidates[x+y*8].getName());

    auto hash_nonce_pair = _blockchain.findNewHash(data);

    _blockchain.addBlock(_blockchain.numOfBlocks(),_blockchain.getLatestBlockHash(),hash_nonce_pair.first,hash_nonce_pair.second,data);
    hide();
}

voteWindow::~voteWindow(){}