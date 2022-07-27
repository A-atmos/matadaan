#include <iostream>
#include "main.h"
#include <thread>

#define PORT 8080

int init_server(Blockchain::Blockchain& blockchain){

    std::string host = networkUtils::getTunnelAddress();
    int port = PORT;
    http_server::HttpServer server(host, port);


    auto index = [](const http::HttpRequest& request) -> http::HttpResponse {
        http::HttpResponse response(http::HttpStatusCode::Ok);
        response.SetHeader("Content-Type", "text/plain");
        response.SetContent("This is the index page.\n");
        return response;
    };

    auto add_nodes = [&blockchain](const http::HttpRequest& request) -> http::HttpResponse {
        // Has a HttpRequest with some data in the content
        // which includes the host address in the content
        std::string host_,nodes_,content_;
        nlohmann::json content;

        host_ = request.content();

        // add the node which is in the request content to the blockchain
        // and get all the nodes in the chain and send it as an response

        if(!host_.empty() ) {
            blockchain.add_node(host_);
        }
        nodes_ = blockchain.get_nodes();

        content["length"] = blockchain.node_length() ;
        content["nodes"] = nodes_;
        content_ = content.dump(-1);

        http::HttpResponse response(http::HttpStatusCode::Created);
        response.SetHeader("Content-Type", "application/json");
        response.SetContent(content_);
        return response;
    };

    auto total_votes = [&blockchain](const http::HttpRequest& request) -> http::HttpResponse {
            std::string content_;
            std::vector<std::pair<std::string, int>> total_votes;
            nlohmann::json content;

            //initiate the background process of generating new set of votes
            std::thread (Blockchain::getVotesInBlockchain,std::ref(blockchain)).detach();

            // get the votes
            total_votes = blockchain.getTotalVotes();

            for(int i = 0 ; i <total_votes.size();i++){
                content["votes"][total_votes[i].first] = total_votes[i].second;
            }

            content["candidates"] = total_votes.size();

            content_ = content.dump(-1);
            http::HttpResponse response(http::HttpStatusCode::Created);
            response.SetHeader("Content-Type", "application/json");
            response.SetContent(content_);
            return response;
        };


    auto full_data = [&blockchain](const http::HttpRequest& request) -> http::HttpResponse {
        // Has a HttpRequest with some data in the content
        // which includes the host address in the content
        std::string content_;
        http::HttpResponse response;
        if(to_string(request.method()) == "GET") {
            content_ = blockchain.jsonDump();
            response.SetStatusCode(http::HttpStatusCode::Ok);
        }
        else if(to_string(request.method()) == "POST"){
            // replace the chain in the current node from the blockchain json obtained from the request
            nlohmann::json request_json;
            request_json = nlohmann::json::parse(request.content());
            blockchain.replaceChain(request_json);
            content_ = "{\"message\":\"Blockchain added to the node.\"}";
            response.SetStatusCode(http::HttpStatusCode::Created);
        }
        else{
            response.SetStatusCode(http::HttpStatusCode::InternalServerError);
        }
        response.SetHeader("Content-Type", "application/json");
        response.SetContent(content_);
        return response;
    };


    server.RegisterHttpRequestHandler("/", http::HttpMethod::HEAD, index);
    server.RegisterHttpRequestHandler("/", http::HttpMethod::GET, index);
    server.RegisterHttpRequestHandler("/nodes", http::HttpMethod::HEAD, add_nodes);
    server.RegisterHttpRequestHandler("/nodes", http::HttpMethod::GET, add_nodes);
    server.RegisterHttpRequestHandler("/votes", http::HttpMethod::HEAD, total_votes);
    server.RegisterHttpRequestHandler("/votes", http::HttpMethod::GET, total_votes);
    server.RegisterHttpRequestHandler("/blockchain", http::HttpMethod::HEAD, full_data);
    server.RegisterHttpRequestHandler("/blockchain", http::HttpMethod::GET, full_data);
    server.RegisterHttpRequestHandler("/blockchain", http::HttpMethod::POST, full_data);

    try {

        std::cout << "Starting the web server.." << std::endl;
        server.Start();
        std::cout << "Server listening on " << host << ":" << port << std::endl;

        std::cout << "Enter [quit] to stop the server" << std::endl;
        std::string command;
        while (std::cin >> command, command != "quit");
        std::cout << "'quit' command entered. Stopping the web server.." << std::endl;
        server.Stop();
        std::cout << "Server stopped" << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1;
    }

}

void ask_input(Blockchain::Blockchain& blockchain){
    std::string string1;
    std::cout<<"Give a input string"<<std::endl;
    std::cin>>string1;
}

int main() {

    std::string init_;

    //Initialize blockchain with genesis block
    Blockchain::Blockchain blockchain(0);



    std::vector<std::string> data;
    data.push_back(hash::sha256("2002"));
    data.emplace_back("1");

    auto hash_nonce_pair = blockUtils::findHash(1,blockchain.getLatestBlockHash(), data);
    std::cout<<hash_nonce_pair.first<<","<<hash_nonce_pair.second<<std::endl;
    blockchain.addBlock(blockchain.numOfBlocks(),blockchain.getLatestBlockHash(),hash_nonce_pair.first,hash_nonce_pair.second,data);

    hash_nonce_pair = blockchain.findNewHash(data);
    std::cout<<hash_nonce_pair.first<<","<<hash_nonce_pair.second<<std::endl;
    blockchain.addBlock(blockchain.numOfBlocks(),blockchain.getLatestBlockHash(),hash_nonce_pair.first,hash_nonce_pair.second,data);


    std::thread thread1(init_server,std::ref(blockchain));
    std::thread thread2(ask_input,std::ref(blockchain));


    thread1.detach();       // To seperate the server from the main application
    thread2.join();         // thread2 contains the main gui application which has the voting system running



    return 0;
}
