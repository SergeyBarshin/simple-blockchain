#ifndef MINER_HPP
#define MINER_HPP

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
#include "Ledger.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using json = nlohmann::json;

class Miner {
   private:
    std::shared_ptr<HttpServer> _server;
    std::vector<int> _peers;
    BlockChain _blockchain;

   public:
    Miner(std::shared_ptr<HttpServer> server);
    Miner(const Miner& m) = delete;
    Miner* operator=(const Miner& m) = delete;

   private:
    // ф-ции для работы с портами
    int getAvilablePort();
    std::vector<int> readPort(const char* path);
    void writePort(unsigned int port, const char* path);

    void setUpPeer(std::shared_ptr<HttpServer> server);  // функция определения роутов
    void start(std::shared_ptr<HttpServer> server);      // добавление ноды в сеть

   public:  // функции взаимодействия
    void processInput();
    void printHelp();
};

#endif  // MINER_HPP
/*
Miner - является 'единицой p2p сети'.

работу с консолью можно вынести в дружественный класс
*/
