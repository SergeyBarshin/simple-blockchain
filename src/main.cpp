#include "core/Miner.hpp"
#include "libfort/lib/fort.hpp"

int main(void) {
    auto server = std::make_shared<HttpServer>();
    auto miner = std::make_unique<Miner>(server);

    std::thread server_thread([&server]() { server->start(); });

    miner->processInput();

    server_thread.join();
    return 0;
}