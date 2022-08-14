#include "main.h"
#include <gtkmm.h>
#include <string>


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
        http::HttpResponse response;
        // add the node which is in the request content to the blockchain
        // and get all the nodes in the chain and send it as an response
        if(to_string(request.method()) == "GET" ){
            nodes_ = blockchain.get_nodes();

            content["length"] = blockchain.node_length() ;
            content["nodes"] = nodes_;
            content_ = content.dump(-1);

            response.SetHeader("Content-Type", "application/json");
            response.SetContent(content_);
            response.SetStatusCode(http::HttpStatusCode::Ok);
        }
        else if(to_string(request.method()) == "POST"){
            host_ = request.content();
            blockchain.add_node(host_);

            nodes_ = blockchain.get_nodes();

            content["length"] = blockchain.node_length() ;
            content["nodes"] = nodes_;
            content_ = content.dump(-1);

            response.SetHeader("Content-Type", "application/json");
            response.SetContent(content_);
            response.SetStatusCode(http::HttpStatusCode::Created);
        }
        else{
            response.SetStatusCode(http::HttpStatusCode::InternalServerError);
        }
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
    server.RegisterHttpRequestHandler("/nodes", http::HttpMethod::POST, add_nodes);

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



int GUI(Blockchain::Blockchain& blockchain) {


    Gtk::Main kit;


//Shows the window and returns when it is closed.
    while(true){
        Enter enter(blockchain);

        Gtk::Main::run(enter);

        if (enter.checkclicked()) {
            //Shows the window and returns when it is closed.
            if(!enter.loggedUser().is_superuser()) {
                std::cout << enter.loggedUser().id() << ":" << enter.loggedUser().password() << std::endl;
                auto app = Gtk::Application::create("voterScreen");
                auto* win = new voteWindow(enter.loggedUser(), blockchain);

                app->run(*win);

                app->remove_window(*win);
                delete win;

                enter.loggedIn = false;
                enter.running = true;
            }
            else{
                // if superuser spawn superuser screen
                SuperUser Sudo(enter.loggedUser(),blockchain);
                Gtk::Main::run(Sudo);
                if(Sudo.exit){
                    enter.running = false;
                    Blockchain::getVotesInBlockchain(blockchain);
                    blockchain.saveTotalVotes();
                }
                else{
                    enter.running = true;
                }
            }
        }


        if(!enter.running){
            return 1;
        }

    }
}

int main(){

    Blockchain::Blockchain blockchain(networkUtils::getTunnelAddress(),0);

    std::thread thread1(init_server,std::ref(blockchain));
//    std::thread thread2(ask_input,std::ref(blockchain));
    std::thread thread2(GUI,std::ref(blockchain));

    thread1.detach();       // To seperate the server from the main application
    thread2.join();         // thread2 contains the main gui application which has the voting system running



    return 0;
}
