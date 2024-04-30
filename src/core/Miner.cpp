#include "Miner.hpp"

Miner::Miner(std::shared_ptr<HttpServer> server) : server(server) {
    start(server);
    setUpPeer(std::move(server));
}

void Miner::printHelp() {
    //  std::cout << "(don't work) Type /print to print all blocks" << std::endl;
    // std::cout << "(don't work) Type /add to add transaction" << std::endl;
    // std::cout << "(don't work) Type [name] of the block to look at:" << std::endl;
    std::cout << "\nType /listNodes to print adresses of all nodes in network:" << std::endl;
    std::cout << "Type /help to print manual:" << std::endl;
}

void Miner::processInput() {
    printHelp();
    for (;;) {
        std::string input;
        std::cin >> input;
        if (input == "/listNodes") {
            for (int i = 0; i < peers.size(); ++i) std::cout << "localhost:" << peers[i] << ", ";
            std::cout << std::endl;
        }
        if (input == "/help") {
            printHelp();
        }
    }
}

int Miner::getAvilablePort() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(3000, 4000);

    auto port = uni(rng);
    return port;
}

void Miner::writePort(unsigned int port, const char* path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::app);
    if (file.fail()) throw std::ios_base::failure(std::strerror(errno));

    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << port << std::endl;
}

std::vector<int> Miner::readPort(const char* path) {
    std::ifstream is(path);
    std::istream_iterator<int> start(is), end;
    std::vector<int> ports(start, end);
    // for (auto i : numbers) std::cout << i << ", ";
    // std::copy(ports.begin(), ports.end(), std::ostream_iterator<int>(std::cout, ","));
    return ports;
}

void Miner::setUpPeer(std::shared_ptr<HttpServer> server) {
    server->resource["^/current$"]["GET"] =
        [this](std::shared_ptr<HttpServer::Response> response,  // передавая this в лямбду, мы педает все ф-ции?
               std::shared_ptr<HttpServer::Request> request) {
            std::cout << "GET / HTTP/1.1 current ";
            std::cout << "ПИРЫ В СЕТИ: " << peers.size() << '\n';
            response->write("Тестовый ответ");
            // response->write(blockchain.serialize());
        };

    server->resource["^/peerpush$"]["POST"] = [this](std::shared_ptr<HttpServer::Response> response,
                                                     std::shared_ptr<HttpServer::Request> request) {
        json content = json::parse(request->content);
        peers.push_back(content["port"].get<int>());
        std::cout << "POST / HTTP/1.1 " << content["port"].get<int>() << " added to peers\n";
        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.size() << "\r\n\r\n"
                  << "joined";
    };

    std::cout << "Server started at localhost: " << server->config.port << "\n";
}

void Miner::start(std::shared_ptr<HttpServer> server) {
    std::cout << "Welcome to Chain, stranger!\n";
    std::cout << "If you are creating a new blockchain, type 'y',\nif you are joining the existing, type 'j':\n";
    char in = 'j';
    // std::cin >> in;

    server->config.port = getAvilablePort();
    writePort(server->config.port, "ports.txt");
    // сейчас ноды узнают других членов сети по общему файлу -> если успею, то переделать на внешние сети

    if (in == 'y') {
        // инициализируем блокчейн
    } else if (in == 'j') {
        peers = readPort("ports.txt");

        json js;
        js["port"] = server->config.port;

        // POST /peerpush
        for (int i = 0; i < peers.size() - 1; i++) {
            int port = peers[i];
            HttpClient client("localhost:" + std::to_string(port));
            std::shared_ptr<HttpClient::Response> response = client.request("POST", "/peerpush", js.dump());
        }
        // std::vector<std::string> vect;
        for (int a = 0; a < peers.size() - 1; a++) {  // GET /current
            int port = peers[a];
            HttpClient client("localhost:" + std::to_string(port));
            std::shared_ptr<HttpClient::Response> response = client.request("GET", "/current");
            //  vect.push_back(response->content.string());
        }
    }
}
