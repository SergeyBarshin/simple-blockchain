#include "Miner.hpp"

Miner::Miner() {
    std::cout << "alive2\n";

    // setUpPeer(std::move(server), peers);
}

Miner::Miner(std::shared_ptr<HttpServer> server, std::vector<int>& peers) : server(server), peers(peers) {
    start(server, peers);
    // setUpPeer(std::move(server), peers);
}

int Miner::start(std::shared_ptr<HttpServer> server, std::vector<int>& peers) {
    std::cout << "Hellow wrld\n";
    // server->config.port = 8080;
    // thread server_thread([&server, &server_port]() {
    // Start server
    //    server->start([&server_port](unsigned short port) { server_port.set_value(port); });
    // });
    // server_thread.join();
    return 0;
}
