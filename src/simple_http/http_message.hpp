//
// Created by Aavash on 7/6/2022.
//

#ifndef MATADAAN_HTTP_MESSAGE_HPP
#define MATADAAN_HTTP_MESSAGE_HPP
#pragma once

#include "uri.hpp"
#include <map>
#include <string>
#include <stdexcept>
#include <sstream>

namespace http{
    /*
     * HTTP methods defined by https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
    */
    enum class HttpMethod {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    };

    /*
     * Http versions but here only HTTP version 1.1 is used which
     * is included in header as HTTP\1.1
     */
    enum class HttpVersion{
        HTTP_0_9 = 9,
        HTTP_1_0 = 10,
        HTTP_1_1 = 11,
        HTTP_2_0 = 20
    };

    /*
     * HTTP response status codes as listed in:
     * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
     * Note that not all of them are present in this enum class
     * Only the ones which may be used are listed
     */
    enum class HttpStatusCode{
        Continue = 100,
        SwitchingProtocols = 101,
        EarlyHints = 103,
        Ok = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,
        MultipleChoices = 300,
        MovedPermanently = 301,
        Found = 302,
        NotModified = 304,
        BadRequest = 400,
        Unauthorized = 401,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        RequestTimeout = 408,
        ImATeapot = 418,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeout = 504,
        HttpVersionNotSupported = 505

    };

    // Functions to convert strings/int to enum class and vice versa

    // Conversion of enum class HttpMethod to string
    std::string to_string(HttpMethod method){
        switch (method) {
            case HttpMethod::GET:
                return "GET";
            case HttpMethod::HEAD:
                return "HEAD";
            case HttpMethod::POST:
                return "POST";
            case HttpMethod::PUT:
                return "PUT";
            case HttpMethod::DELETE:
                return "DELETE";
            case HttpMethod::CONNECT:
                return "CONNECT";
            case HttpMethod::OPTIONS:
                return "OPTIONS";
            case HttpMethod::TRACE:
                return "TRACE";
            case HttpMethod::PATCH:
                return "PATCH";
            default:
                return {};
        }
    }

    // Function to convert enum class HttpVersion into string
    std::string to_string(HttpVersion version){
        switch (version) {
            case HttpVersion::HTTP_0_9:
                return "HTTP/0.9";
            case HttpVersion::HTTP_1_0:
                return "HTTP/1.0";
            case HttpVersion::HTTP_1_1:
                return "HTTP/1.1";
            case HttpVersion::HTTP_2_0:
                return "HTTP/2.0";
            default:
                return {};
        }
    }

    // Conversion of enum class HttpStatusCode into string
    std::string to_string(HttpStatusCode status_code){
        switch (status_code) {
            case HttpStatusCode::Continue:
                return "Continue";
            case HttpStatusCode::Ok:
                return "OK";
            case HttpStatusCode::Accepted:
                return "Accepted";
            case HttpStatusCode::MovedPermanently:
                return "Moved Permanently";
            case HttpStatusCode::Found:
                return "Found";
            case HttpStatusCode::BadRequest:
                return "Bad Request";
            case HttpStatusCode::Forbidden:
                return "Forbidden";
            case HttpStatusCode::NotFound:
                return "Not Found";
            case HttpStatusCode::MethodNotAllowed:
                return "Method Not Allowed";
            case HttpStatusCode::ImATeapot:
                return "I'm a Teapot";
            case HttpStatusCode::InternalServerError:
                return "Internal Server Error";
            case HttpStatusCode::NotImplemented:
                return "Not Implemented";
            case HttpStatusCode::BadGateway:
                return "Bad Gateway";
            default:
                return {};
        }

    }

    // Conversion of string to enum class HttpMethod
    HttpMethod string_to_method(const std::string& method_string){
        std::string method_string_uppercase;
        std::transform(method_string.begin(), method_string.end(),
                       std::back_inserter(method_string_uppercase), [](char c) { return toupper(c); });
        if (method_string_uppercase == "GET") {
            return HttpMethod::GET;
        } else if (method_string_uppercase == "HEAD") {
            return HttpMethod::HEAD;
        } else if (method_string_uppercase == "POST") {
            return HttpMethod::POST;
        } else if (method_string_uppercase == "PUT") {
            return HttpMethod::PUT;
        } else if (method_string_uppercase == "DELETE") {
            return HttpMethod::DELETE;
        } else if (method_string_uppercase == "CONNECT") {
            return HttpMethod::CONNECT;
        } else if (method_string_uppercase == "OPTIONS") {
            return HttpMethod::OPTIONS;
        } else if (method_string_uppercase == "TRACE") {
            return HttpMethod::TRACE;
        } else if (method_string_uppercase == "PATCH") {
            return HttpMethod::PATCH;
        } else {
            throw std::invalid_argument("Unexpected HTTP method");
        }
    }

    // Conversion of string to enum class HttpVersion
    HttpVersion string_to_version(const std::string& version_string){
        std::string version_string_uppercase;
        std::transform(version_string.begin(), version_string.end(),
                       std::back_inserter(version_string_uppercase), [](char c) { return toupper(c); });
        if (version_string_uppercase == "HTTP/0.9") {
            return HttpVersion::HTTP_0_9;
        } else if (version_string_uppercase == "HTTP/1.0") {
            return HttpVersion::HTTP_1_0;
        } else if (version_string_uppercase == "HTTP/1.1") {
            return HttpVersion::HTTP_1_1;
        } else if (version_string_uppercase == "HTTP/2" || version_string_uppercase == "HTTP/2.0") {
            return HttpVersion::HTTP_2_0;
        } else {
            throw std::invalid_argument("Unexpected HTTP version");
        }
    }

    HttpStatusCode string_to_status_code(const int status_int){
        if (status_int == 100) {
            return HttpStatusCode::Continue;
        } else if (status_int == 200) {
            return HttpStatusCode::Ok;
        } else if (status_int == 202) {
            return HttpStatusCode::Accepted;
        } else if (status_int == 301) {
            return HttpStatusCode::MovedPermanently;
        } else if (status_int == 302) {
            return HttpStatusCode::Found;
        } else if (status_int == 400) {
            return HttpStatusCode::BadRequest;
        } else if (status_int == 403) {
            return HttpStatusCode::Forbidden;
        } else if (status_int == 404) {
            return HttpStatusCode::NotFound;
        } else if (status_int == 405) {
            return HttpStatusCode::MethodNotAllowed;
        } else if (status_int == 418) {
            return HttpStatusCode::ImATeapot;
        } else if (status_int == 500) {
            return HttpStatusCode::InternalServerError;
        } else if (status_int == 501) {
            return HttpStatusCode::NotImplemented;
        } else if (status_int == 502) {
            return HttpStatusCode::BadGateway;
        } else {
            throw std::invalid_argument("Unexpected Status Code");
        }

    }
    /*
     * Represents a general Http request which has a HttpVersion,
     * HttpHeaders and the HttpContent. It may be a request or
     * response to HTTP request. */
    class HttpMessage{
    public:
        HttpMessage(): _version(HttpVersion::HTTP_1_1){};
        virtual ~HttpMessage() = default;

        void SetHeader(const std::string& key, const std::string& value) { _headers[key] = value; }
        void RemoveHeader(const std::string& key) { _headers.erase(key); }
        void ClearHeader() { _headers.clear(); }
        void SetContent(const std::string& content) {
            _content = content;
            SetContentLength();
        }
        void ClearContent(const std::string& content) {
            _content.clear();
            SetContentLength();
        }

        HttpVersion version(){return this->_version;}

        [[nodiscard]] std::string header(const std::string& key) const {
            if (_headers.count(key) > 0)
                return _headers.at(key);
            return {};
        }
        [[nodiscard]] std::map<std::string, std::string> headers() const { return _headers; }
        [[nodiscard]] std::string content() const { return _content; }
        [[nodiscard]] size_t content_length() const { return _content.length(); }



    protected:
        HttpVersion _version;
        std::map<std::string, std::string> _headers;
        std::string _content;

        void SetContentLength(){
            SetHeader("Content-Length", std::to_string(_content.length()));
        }
    };

    /*
     * A single Http Request which contains the information of
     * Request uri, method. So that response can be sent back to
     * the request. Also contains general HttpMessage.*/
    class HttpRequest:public HttpMessage{
    public:
        HttpRequest(): _method(HttpMethod::GET){};
        ~HttpRequest() override = default;


        void SetMethod(HttpMethod method) { _method = method; }
        void SetUri(const URI& uri) { _uri = uri; }

        [[nodiscard]] HttpMethod method() const { return _method; }
        [[nodiscard]] URI uri() const { return _uri; }

        friend std::string to_string(HttpRequest& request);
        friend HttpRequest string_to_request(const std::string& request_string);

    private:
        HttpMethod _method;
        URI _uri;
    };

    /*
     * HttpResponse object represents a single HTTP Response
     * Server sends a HTTP Response to the client that includes
     * HTTP Status Code, headers and content*/
    class HttpResponse:public HttpMessage{
    public:
        HttpResponse(): _statusCode(HttpStatusCode::Ok){}
        HttpResponse(HttpStatusCode statusCode){this->_statusCode = statusCode;}
        ~HttpResponse() override = default;

        void SetStatusCode(HttpStatusCode statusCode){
            _statusCode = statusCode;
        }

        HttpStatusCode status_code(){
            return this->_statusCode;
        }

        friend std::string to_string(HttpResponse response, bool send_content);
        friend HttpResponse string_to_response(const std::string& response_string);


    private:
        HttpStatusCode _statusCode;

    };

    /*
     * Conversion of HttpRequest to string
     * Used to send the response from server
     * */
    std::string to_string(HttpRequest& request){
        std::ostringstream oss;

        /*
         * Format:
         * GET / HTTP/1.1
         * User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)
         * Content-Length: 150
         *
         * Some Content here
         * */

        oss << to_string(request.method()) << ' ';
        oss << request.uri().getPath() << ' ';
        oss << to_string(request.version()) << "\r\n";
        for (const auto& p : request.headers())
            oss << p.first << ": " << p.second << "\r\n";
        oss << "\r\n";
        oss << request.content();

        return oss.str();
    };

    /*
     * Conversion of string to the class HttpRequest
     * Used to convert the response from server to processable class
     * */
    HttpRequest string_to_request(const std::string& request_string){
        std::string start_line, header_lines, message_body;
        std::istringstream iss;                     // used for easier string processing
        HttpRequest request;
        std::string line, method, path, version;  // used for first line
        std::string key, value;                   // used for header fields
        URI uri;
        size_t lpos = 0, rpos = 0;

        // The first line ends with \r\n
        rpos = request_string.find("\r\n", lpos);
        if (rpos == std::string::npos) {
            throw std::invalid_argument("Could not find request start line");
        }

        //store the starting line with string like "GET / HTTP/1.1\r\n"
        // lpos is the beginning of the line
        // rpos gives the position of \r\n and rpos-lpos gives the number of characters
        // in between the two position
        start_line = request_string.substr(lpos, rpos - lpos);
        // skipping the \r\n character, and setting up new lpos for new line
        lpos = rpos + 2;

        // The headers ends with \r\n\r\n and content part starts
        rpos = request_string.find("\r\n\r\n", lpos);

        if (rpos != std::string::npos) {          // has header
            header_lines = request_string.substr(lpos, rpos - lpos);
            lpos = rpos + 4;
            rpos = request_string.length();
            // check if there's body in the request
            if (lpos < rpos) {
                // store the body of the request in message_body
                message_body = request_string.substr(lpos, rpos - lpos);
            }
        }

        iss.clear();                              // parse the start line
        // store start_line in iss
        iss.str(start_line);
        // From the start_line separate method, path, and version
        // Using the spaces in between them
        iss >> method >> path >> version;
        if (!iss.good() && !iss.eof()) {
            throw std::invalid_argument("Invalid start line format");
        }
        request.SetMethod(string_to_method(method));
        request.SetUri(URI(path));
        if (string_to_version(version) != request.version()) {
            throw std::logic_error("HTTP version not supported");
        }

        iss.clear();                              // parse header fields
        iss.str(header_lines);
        while (std::getline(iss, line)) {
            std::istringstream header_stream(line);
            std::getline(header_stream, key, ':');
            std::getline(header_stream, value);

            // remove whitespaces from the two strings
            key.erase(std::remove_if(key.begin(), key.end(), [](char c) { return std::isspace(c); }), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), [](char c) { return std::isspace(c); }), value.end());
            request.SetHeader(key, value);
        }

        request.SetContent(message_body);

        return request;
    }


    std::string to_string(HttpResponse response, bool send_content){
        std::ostringstream oss;

        /*
         * Format:
         * HTTP/1.1 404 Not Found
         * Content-Type: text/html
         * Content-Length: 150
         *
         * Some Content here
         * */
        oss << to_string(response.version()) << ' ';
        oss << static_cast<int>(response.status_code()) << ' ';
        oss << to_string(response.status_code()) << "\r\n";

        for (const auto& p : response.headers())
            oss << p.first << ": " << p.second << "\r\n";
        oss << "\r\n";
        if (send_content) {
            oss << response.content();
        }
        return oss.str();
    };

    HttpResponse string_to_response(const std::string& response_string){
        /*
         * Format:
         * HTTP/1.1 404 Not Found
         * Content-Type: text/html
         * Content-Length: 150
         *
         * Some Content here
         *
         * Change from string to class HttpResponse
         * */
        std::string start_line, header_lines, message_body;
        std::istringstream oss;                     // used for easier string processing
        HttpResponse response;
        HttpStatusCode statusCode;

        std::string line, version, status_code;                  // used for first line
        int status_code_int;
        std::string key, value;                   // used for header fields
        size_t lpos = 0, rpos = 0;

        rpos = response_string.find("\r\n",lpos);           // Store the number of char before \r\n in rpos
        if(rpos == std::string::npos){
            throw std::invalid_argument("Couldn't find the starting line!");
        }

        start_line = response_string.substr(lpos,rpos-lpos);
        // store the value of next line in lpos
        lpos = rpos + 2;
        rpos = response_string.find("\r\n\r\n",lpos);

        // lpos is the position of starting char, rpos is the position of end char

        if(rpos != std::string::npos){
            header_lines = response_string.substr(lpos,rpos-lpos);
            lpos = rpos +4;             // after the header lines, and \r\n\r\n, getting the position in lpos
            rpos = response_string.length();
            if(lpos<rpos) {
                message_body = response_string.substr(lpos, rpos - lpos);
            }
        }
        // Parse the Starting Line
        oss.clear();
        oss.str(start_line);
        oss >> version >> status_code_int ;

        statusCode = string_to_status_code(status_code_int);
        response.SetStatusCode(statusCode);

        // Parse the Header Fields

        oss.clear();
        oss.str(header_lines);
        while (std::getline(oss, line)) {
            std::istringstream header_stream(line);
            std::getline(header_stream, key, ':');
            std::getline(header_stream, value);

            // remove whitespaces from the two strings
            key.erase(std::remove_if(key.begin(), key.end(), [](char c) { return std::isspace(c); }), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), [](char c) { return std::isspace(c); }), value.end());
            response.SetHeader(key, value);
        }

        response.SetContent(message_body);

        return response;
    };
}


#endif //MATADAAN_HTTP_MESSAGE_HPP
