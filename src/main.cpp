#include "core/Interface.hpp"
#include "core/ChatInterface.hpp"
#include "core/Miner.hpp"
#include "libfort/lib/fort.hpp"

int main(void) {
    auto server = std::make_shared<HttpServer>();

    //Creator* creator = new ClICreator();  // созадаем CLI, применяя "фабричный метод".
    Creator* creator = new ChatCreator();  // ChatCreator for ChatInterface

    bool isGenesis = creator->getInitStage();
    auto miner = std::make_shared<Miner>(server, isGenesis);

    std::thread server_thread([&server]() { server->start(); });

    creator->FactoryMethod(miner);

    server_thread.join();
    return 0;
}