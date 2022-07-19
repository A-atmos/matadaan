//
// Created by ac on 7/19/22.
//

#ifndef MATADAAN_HTTP_CLIENT_H
#define MATADAAN_HTTP_CLIENT_H

#pragma once

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <utility>


#include "http_message.hpp"
#include "uri.hpp"

namespace http_client{

    class HttpClient{
    private:
        int sock_fd_,client_fd_;
        int CreateSocket();
        int Connect(std::string host,int port);


        int CloseSocket() const;

    public:

        HttpClient(){};

        http::HttpResponse sendRequest(http::HttpRequest request_ );

    };
}

#endif //MATADAAN_HTTP_CLIENT_H
