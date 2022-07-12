//
#ifndef MATADAAN_HTTP_SERVER_HPP
#define MATADAAN_HTTP_SERVER_HPP
#pragma once

#include<string>
#include<thread>
#include<function>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>

#include"http_message.hpp"
#include"uri.hpp"

namespace http_server{

    // Request Handler accepts a HttpRequest and returns a HttpResponse
    using HttpRequestHandler = std::function<HttpResponse(const HttpRequest&)>;

    class HttpServer{
    private:
        int kBacklogSize = 1000;
        int kMaxConnections = 1000;
        int kMaxEvents = 1000;
        int kThreadPoolSize = 5;

        std::string host_;
        std::uint16_t port_;
        int sock_fd_;
        bool running_;
        std::thread listening_thread;
        std::thread worker_threads[kThreadPoolSize];
        int worker_epoll_fd_[kThreadPoolSize];
        epoll_event worker_events_[kThreadPoolSize][kMaxEvents];
        std::map<URI, std::map<HttpMethod, HttpRequestHandler> > request_handlers_;

        void CreateSocket();
        void SetUpEpoll();
        void Listen();
        void ProcessEvents(int worker_id);
        void HandleEpollEvent(int epoll_fd, EventData *event, std::uint32_t events);
        void HandleHttpData(const EventData& request, EventData *response);
        HttpResponse HandleHttpRequest(const HttpRequest& request);

        void control_epoll_event(int epoll_fd, int op, int fd, std::uint32_t events = 0, void *data = nullptr);
    
    
    public:
        explicit HttpServer(std::string& host, std::uint16_t port);
        ~HttpServer() = default;

        HttpServer() = default;
        HttpServer(HttpServer&&) = default;
        HttpServer& operator=(HttpServer&&) = default;

        void Start();
        void Stop();
        void RegisterHttpRequestHandler(std::string& path, HttpMethod mathod, HttpRequestHandler callback){
            URI uri(path);
            request_handlers_[uri].insert(std::make_pair(method,std::move(callback)));  
        }

        void RegisterHttpRequestHandler(URI& uri, HttpMethod mathod, HttpRequestHandler callback){
            request_handlers_[uri].insert(std::make_pair(method,std::move(callback)));  
        }

        std::string host() const {return this->host_;}
        std::uint16_t port() const {return this->port_;}

        bool running() const {return this->running_;}
    }





    
}

#endif //MATADAAN_HTTP_SERVER_HPP
