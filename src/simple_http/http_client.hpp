//
// Created by ac on 7/19/22.
//

#ifndef MATADAAN_HTTP_CLIENT_HPP
#define MATADAAN_HTTP_CLIENT_HPP
#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "http_client.h"


namespace http_client{

    int HttpClient::CreateSocket() {
        if ((sock_fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }
        return 1;
    }

    int HttpClient::Connect(std::string host, int port) {
        struct sockaddr_in serv_addr;



        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);


        if(inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_fd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        return 0;
    }

    int HttpClient::CloseSocket() const {
        close(client_fd_);
        return 1;
    }

    http::HttpResponse HttpClient::sendRequest(http::HttpRequest request_) {
        http::HttpResponse response;
        char buffer[1024] = {0};
        close(sock_fd_);
        CreateSocket();
//        std::cout<<request_.uri().getHost()<<":"<<request_.uri().getPort()<<std::endl;
        Connect(request_.uri().getHost(),request_.uri().getPort());

//        std::cout<<to_string(request_)<<std::endl<<std::endl;

        send(sock_fd_ , to_string(request_).c_str() , strlen(to_string(request_).c_str()) , 0 );
        read( sock_fd_ , buffer, 1024);
//        printf("%s", buffer);
        std::string response_string = buffer;
        close(sock_fd_);

        response = http::string_to_response(response_string);
        return response;
    }

}
#endif //MATADAAN_HTTP_CLIENT_HPP
