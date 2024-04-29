#include <algorithm>
// #include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "../Simple-Web-Server/client_http.hpp"
#include "../Simple-Web-Server/server_http.hpp"
#include "../json/single_include/nlohmann/json.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

class Miner {
    using json = nlohmann::json;

    std::shared_ptr<HttpServer> server;
    std::vector<int> peers;

   public:
    Miner(std::shared_ptr<HttpServer> server, std::vector<int>& peers);

   private:
    // Вспомогательные функции
    int getAvilablePort();
    std::vector<int> readPort(const char* path);
    void writePort(unsigned int port, const char* path);

    // функция определения роутов
    void setUpPeer(std::shared_ptr<HttpServer> server, std::vector<int>& peers);
    void start(std::shared_ptr<HttpServer> server, std::vector<int>& peers);
};

/*
Miner - является 'единицой p2p сети'.
*/
