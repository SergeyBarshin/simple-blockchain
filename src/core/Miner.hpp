#include <algorithm>
// #include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "../Simple-Web-Server/client_http.hpp"
#include "../Simple-Web-Server/server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

class Miner {
   public:
    std::shared_ptr<HttpServer> server;
    std::vector<int> peers;

    Miner() { std::cout << "sadads"; };
    Miner(std::shared_ptr<HttpServer> server, std::vector<int>& peers);

    int start(std::shared_ptr<HttpServer> server, std::vector<int>& peers);
    // int setUpPeer(std::shared_ptr<HttpServer> server, std::vector<int>& peers);
};

/*
Miner - является 'единицой в p2p сети'.
*/
