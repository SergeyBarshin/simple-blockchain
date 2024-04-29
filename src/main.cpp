#include "core/Miner.hpp"
#include "libfort/lib/fort.hpp"

int main(void) {
    auto server = std::make_shared<HttpServer>();
    std::vector<int> peers;
    auto miner = std::make_unique<Miner>(server, peers);

    std::thread server_thread([&server]() { server->start(); });

    // тестовые запросы
    HttpClient client("localhost:8080");
    std::shared_ptr<HttpClient::Response> response = client.request("GET", "/current");
    std::cout << response->content.string() << '\n';

    server_thread.join();
    return 0;
}