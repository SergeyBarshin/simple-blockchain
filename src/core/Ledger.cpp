#include "Ledger.hpp"

Block BlockChain::getBlock(int counter) const {
    Block res;
    for (int i = 0; i < blockchain.size(); i++) {
        if (blockchain[i].getCounter() == counter) {
            res = blockchain[i];
        }
    }
    return res;
}

std::string BlockChain::serialize() const {
    json j;
    j.emplace("length", blockchain.size());
    for (int i = 0; i < this->blockchain.size(); i++)
        j["data"][this->blockchain[i].getCounter()] = this->blockchain.at(i).serialize();

    return j.dump(3);
}

void BlockChain::behave(BlockChain::Stage stage) {
    std::vector<std::string> data;

    if (stage == Stage::INIT)
        std::cout << "Blockchain Initialized" << "\n";
    else if (stage == Stage::GENESIS) {
        data.push_back("Genesis");
        std::pair<std::string, std::string> nonce;

        // std::pair<std::string, std::string> nonce = Utils::findHash(2, 0, std::string(GENESIS_HASH), data);

        this->blockchain.push_back(
            Block(0, 2, Block::getTime().c_str(), nonce.second, nonce.first, std::string(GENESIS_HASH), data));
        std::cout << "Blockchain has been created" << "\n";

        this->printBlocks();
    } else if (stage == Stage::JOIN)
        std::cout << "Joined blockchain" << "\n";
    else
        std::cout << "Something went wrong during blockchain creation" << "\n";
}

/*
int BlockChain::addBlock(int counter, int difficulty, std::string minedTime, std::string prevHash, std::string hash,
                         std::string nonce, std::vector<std::string>& merkle) {
    std::string target;
    for (unsigned i = 0; i < difficulty; i++) {
        target += std::to_string(0);
    }
    std::string header = std::to_string(counter) + prevHash + Utils::getMerkleRootM(merkle).to_string() + nonce;

    if ((!Utils::sha256(header).compare(hash)) && (hash.substr(0, difficulty) == target) &&
        (counter == blockchain.size())) {
        spdlog::info("(Consensus???)Proof of idiot. Somehow it's a match.\nHash: {0}\n Difficulty {1:d};", hash.c_str(),
                     difficulty);
        this->blockchain.push_back(Block(difficulty, counter, minedTime, prevHash, hash, nonce, merkle));
        return 0;
    }
    spdlog::error("Check hashing");
    return 1;
}*/