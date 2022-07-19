//
// Created by Aavash on 7/5/2022.
//

#ifndef MATADAAN_URI_HPP
#define MATADAAN_URI_HPP

#pragma once

#include<string>
#include<algorithm>
#include <utility>

namespace http{
    class URI{
    private:
        std::string scheme;
        std::string path;
        std::string host;
        std::uint16_t port{};
    public:
        URI() = default;
        explicit URI(std::string& _path): path(_path){};

        inline bool operator<(const URI& other) const { return path < other.path; }
        void setPathToLowerCase();
        int setPath(const std::string& _path);
        std::string getScheme();
        std::string getPath();
        std::string getHost();
        [[nodiscard]] std::uint16_t getPort() const;
        void setHost(std::string _host){
            host = std::move(_host);
        }
        void setPort(int _port){
            port = _port;
        }

    };

    int URI::setPath(const std::string &_path) {
        this->path = _path;
        setPathToLowerCase();
        return 1;
    }

    /*
     * std::transform from algorithm header used to transform the path to lowercase
     * path.begin() is the first term, path.end() is the last term
     * The result is to be stored starting from path.begin() and toLower() is used to
     * lower each character in the url, which is used as a unary operator.
     * */
    void URI::setPathToLowerCase() {
        std::transform(path.begin(),path.end(),path.begin(),[](char c) { return tolower(c); });
    }

    std::string URI::getHost() {return this->host;}

    std::string URI::getPath() {return this->path;}

    std::uint16_t URI::getPort() const {return this->port;}

    std::string URI::getScheme() {return this->scheme;}
}

#endif //MATADAAN_URI_HPP
