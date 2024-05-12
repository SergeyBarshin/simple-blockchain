#include "core/Block.hpp"
#include "core/Miner.hpp"
#include "libfort/lib/fort.hpp"
//Testing new libs
#include "core/Cryptography.hpp"

int main(void) {
     // Test SHA-256 hash function
    std::string sha256_hash = Utils::sha256("Hello, World!");
    std::cout << "SHA-256 Hash: " << sha256_hash << std::endl;
    
    auto server = std::make_shared<HttpServer>();
    auto miner = std::make_unique<Miner>(server);

    std::thread server_thread([&server]() { server->start(); });

    miner->processInput();

    server_thread.join();
    return 0;
}