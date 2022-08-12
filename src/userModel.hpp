//
// Created by ac on 8/7/22.
//

#ifndef MATADAAN_USERMODEL_HPP
#define MATADAAN_USERMODEL_HPP

#include "../lib/json.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <gtkmm.h>
#include <gdkmm.h>

namespace USER {

    class UserDoesnotExist {
    };

    class UserAlreadyVoted {
    };

    class User {
    private:
        std::string _id;
        std::string _password;
        bool _superuser;
    public:

        User() {}

        User(std::string id, std::string password, bool is_superuser) : _id(std::move(id)), _password(std::move(password)) {_superuser = is_superuser;}


        std::string id() { return _id; }
        std::string password() { return _password; }
        bool is_superuser(){return _superuser;}
        // friend std::vector<User> load_data(std::string fileName);
        bool alreadyVoted(nlohmann::json blockchain);


        friend std::vector <User> loadData(std::string fileName);
        friend void saveUser(const std::string& _username,std::string _password,bool superuser,std::string filename);

        ~User() {}

        bool exists() {
            if (_id.empty() && _password.empty()) {
                return false;
            }
            return true;
        }

    };


    void saveUser(const std::string& _username,std::string _password,bool superuser=false,std::string filename="user.txt"){
        std::ofstream fout(filename.c_str(),std::ios::app);
        fout<<std::endl<<_username<<","<<hash::sha256(std::move(_password))<<","<<superuser;
        fout.close();
    }


    std::vector <User> loadData(std::string fileName) {
        std::string line;
        std::vector <User> users;

        std::string _id, _pass, _is_superuser;
        bool superuser;

        std::ifstream file;
        file.open(fileName.c_str(), std::ios::in);

        if (!file) {
            std::cerr << "Data Load Error";
        }
        while (!file.eof()) {
            getline(file, line, '\n');
            std::stringstream ss(line);

            std::getline(ss, _id, ',');

            std::getline(ss, _pass, ',');
            std::getline(ss,_is_superuser);
            std::istringstream(_is_superuser) >> superuser;
            // std::cout<<"\n\n"<<_id<<":"<<_pass<<std::endl;
            users.emplace_back(_id, _pass,superuser);

        }
        // std::cout<<"\n";
        file.close();


        return users;

    }

    bool User::alreadyVoted(nlohmann::json blockchain) {
        for(int i=1;i<blockchain["length"].get<int>();i++) {
            if(blockchain["data"][i]["data"][0] == hash::sha256(_id)){
                return true;
            }
        }

//    std::cout<<blockchain["length"];
        return false;
    }

}


namespace CANDIDATE{
    class candidate{
    private:
        std::string name;
        std::string pathToImage;

    public:
        candidate(std::string _name, std::string _pathToImage);
        friend void save(std::string _name, std::string _path_to_image,std::string fileName);
        friend std::vector<candidate> loadFromFile(std::string fileName);
        std::string getName(){return name;}
        std::string getImagePath(){return pathToImage;}
    };
    candidate::candidate(std::string _name ,std::string _pathToImage) {
        name = _name;
        pathToImage = _pathToImage;
    }

    std::vector<candidate> loadFromFile(std::string fileName="candidates/candidates.txt"){
        std::string _name,_pathToImage,line;

        std::vector<candidate> cand;

        std::fstream file;
        file.open(fileName,std::ios::in);

        if (!file) {
            std::cerr << "Data Load Error";
        }
        while (!file.eof()) {
            getline(file, line, '\n');
            std::stringstream ss(line);

            std::getline(ss, _name, ',');

            std::getline(ss, _pathToImage);

            // std::cout<<"\n\n"<<_id<<":"<<_pass<<std::endl;
            // users.push_back(User(_id, _pass));
            cand.push_back(candidate(_name,_pathToImage));

        }
        file.close();
        return cand;

    }

    void save(std::string _name, std::string _image_name, std::string fileName="candidates/candidates.txt") {
        std::fstream file;
        std::string _pathToImage = "candidates/images/"+_image_name+".png";
        file.open(fileName,std::ios::app);
        file<<std::endl<<_name<<","<<_pathToImage;
        file.close();
    }


}

#endif //MATADAAN_USERMODEL_HPP
