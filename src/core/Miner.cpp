#include "Miner.hpp"

Miner::Miner(std::shared_ptr<HttpServer> server, bool isGenesis) : _server(server) {
    start(server, isGenesis);
    setUpPeer(std::move(server));
}

void Miner::processTransaction(std::string transactionData, int difficulty) {
    std::vector<std::string> transaction;
    transaction.push_back(transactionData);

    std::pair<std::string, std::string> nonce =
        Utils::findHash(difficulty, _blockchain.getNumOfBlocks(), _blockchain.getLatestBlockHash(), transaction);

    /*
    Это будет основной вариант транзакции и цифрового кошелька для будущей логики,
    сейчас он просто имитирует + 0.25 токена за каждые 3 блока.
    */
    if ((_blockchain.getNumOfBlocks() != 0) && ((_blockchain.getNumOfBlocks() % 3) == 0))
        std::cout << "Вам начислено +0.25token\n";

    _blockchain.addBlock(_blockchain.getNumOfBlocks(), difficulty, Block::getTime().c_str(), nonce.first,
                         _blockchain.getLatestBlockHash(), nonce.second, transaction);

    std::cout << "Updating blockchain...\n";
    for (int i = 0; i < _peers.size(); i++) {
        int port = _peers[i];
        // std::cout << "--- sending to node " << port << '\n';
        HttpClient client("localhost:" + std::to_string(port));
        auto req = client.request("POST", "/updateLedger", _blockchain.serialize());
    }
    std::cout << "Blockchain updated!\n";
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

    return ports;
}

void Miner::setUpPeer(std::shared_ptr<HttpServer> _server) {  // определение роутов
    _server->resource["^/current$"]["GET"] =
        [this](std::shared_ptr<HttpServer::Response> response,  // передавая this в лямбду, мы педает все ф-ции?
               std::shared_ptr<HttpServer::Request> request) { response->write(_blockchain.serialize()); };

    _server->resource["^/peerpush$"]["POST"] = [this](std::shared_ptr<HttpServer::Response> response,
                                                      std::shared_ptr<HttpServer::Request> request) {
        json content = json::parse(request->content);
        _peers.push_back(content["port"].get<int>());

        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.size() << "\r\n\r\n"
                  << "joined";
    };

    _server->resource["^/updateLedger$"]["POST"] = [this](std::shared_ptr<HttpServer::Response> response,
                                                          std::shared_ptr<HttpServer::Request> request) {
        json content = json::parse(request->content);

        _blockchain.blockchain.resize(1);  // оставляем только генезис блок
        for (int i = 1; i < content["length"].get<int>(); i++) {
            auto block = content["data"][i];
            std::vector<std::string> data = block["data"].get<std::vector<std::string>>();
            _blockchain.addBlock(block["counter"], block["difficulty"], block["minedTime"], block["hash"],
                                 block["prevHash"], block["nonce"], data);
        }
        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.size() << "\r\n\r\n"
                  << "Blockchain recreated\n";
    };

    std::cout << "Server started at localhost:" << _server->config.port << "\n";
}

void Miner::start(std::shared_ptr<HttpServer> _server, bool isGenesis) {
    _server->config.port = getAvilablePort();
    writePort(_server->config.port, "ports.txt");
    _peers = readPort("ports.txt");
    // сейчас ноды узнают других членов сети по общему файлу -> если успею, то переделать на внешние сети

    if (isGenesis)
        _blockchain.initBlockchain();
    else {
        std::cout << "Joining blockchain..." << "\n";

        json js;
        js["port"] = _server->config.port;

        // POST /peerpush
        for (int i = 0; i < _peers.size() - 1; ++i) {
            int port = _peers[i];
            HttpClient client("localhost:" + std::to_string(port));
            std::shared_ptr<HttpClient::Response> response = client.request("POST", "/peerpush", js.dump());
        }

        std::vector<std::string> vect;
        for (int i = 0; i < _peers.size() - 1; ++i) {  // GET /current
            int port = _peers[i];
            HttpClient client("localhost:" + std::to_string(port));
            std::shared_ptr<HttpClient::Response> response = client.request("GET", "/current");
            vect.push_back(response->content.string());
        }

        json chain = json::parse(vect[0]);
        int max = 0;
        for (int i = 0; i < vect.size(); ++i) {
            json json_data = json::parse(vect[i]);
            if (max < json_data["length"].get<int>()) {
                max = json_data["length"].get<int>();
                chain = json_data;
            }
        }

        // добавляем блоки в локальную копию блокчейна
        for (int a = 0; a < chain["length"].get<int>(); ++a) {
            auto block = chain["data"][a];
            std::vector<std::string> data = block["data"].get<std::vector<std::string>>();
            _blockchain.addBlock(block["counter"], block["difficulty"], block["minedTime"], block["hash"],
                                 block["prevHash"], block["nonce"], data);
        }
    }
}

/*
по идее осталось сделать только /print /add

*/
