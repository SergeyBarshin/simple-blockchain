#include "core/Miner.hpp"
#include "libfort/lib/fort.hpp"

int main(void) {
    // auto server = HttpServer();
    auto server = std::make_shared<HttpServer>();
    std::vector<int> peers;

    Miner m;
    //  auto miner = std::make_unique<Miner>(server, peers);
    //    std::thread server_thread([&server]() { server->start(); });

    // interface - собирает только hpp

    // идея для фикса: simple-Web - подключить как библиотека к майнеру

    return 0;
}