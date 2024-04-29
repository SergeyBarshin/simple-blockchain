#include "Miner.hpp"

Miner::Miner() {
    std::cout << "alive2\n";

    // setUpPeer(std::move(server), peers);
}

Miner::Miner(std::shared_ptr<HttpServer> server, std::vector<int>& peers) : server(server), peers(peers) {
    start(server, peers);
    setUpPeer(std::move(server), peers);
}

void Miner::setUpPeer(std::shared_ptr<HttpServer> server, std::vector<int>& peers) {
    // функция должна принимать ссылку на блокчейн
    server->resource["^/current$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response,
                                               std::shared_ptr<HttpServer::Request> request) {
        std::cout << "GET / HTTP/1.1 current\n";
        response->write("Тестовый ответ");  // возвращаем порт этого пира
        // response->write(blockchain.serialize());
    };

    server->resource["^/peerpush$"]["POST"] = [&peers](std::shared_ptr<HttpServer::Response> response,
                                                       std::shared_ptr<HttpServer::Request> request) {
        /* json content = с::parse(request->content);
         peers.push_back(content["port"].get<int>());
         std::cout << "POST / HTTP/1.1 " << content["port"].get<int>() << " added to peers";
         *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.size() << "\r\n\r\n"
        << "joined";*/

        std::cout << "POST / HTTP/1.1 peerpush";
        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << 228 << "\r\n\r\n"
                  << "joined";
    };

    std::cout << "Server started at localhost: " << server->config.port << "\n";
}

void Miner::start(std::shared_ptr<HttpServer> server, std::vector<int>& peers) {
    std::cout << "Welcome to Chain, stranger!\n";
    std::cout << "If you are creating a new blockchain, type 'y',\nif you are joining the existing, type 'j':\n";
    char in = 'j';
    //  std::cin >> in;

    server->config.port = 8080;  // тут должен быть getAviliablePort()

    if (in == 'y') {
    } else if (in == 'j') {
        // записываем пир во все другие пиры и все другие в наш
        // POST /peerpush
        // GET /current
    }
}
