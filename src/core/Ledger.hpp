#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../json/single_include/nlohmann/json.hpp"
#include "Block.hpp"
#include "Utils.hpp"

using json = nlohmann::json;

#define GENESIS_HASH "000000000000000000000000000000000000000001"

class BlockChain {
   public:
    std::vector<Block> blockchain;

   private:
   public:
    BlockChain() = default;
    ~BlockChain(){};

   public:
    Block getBlock(int counter) const;
    int getNumOfBlocks() const { return this->blockchain.size(); }

    std::vector<Block> getBlockChain() const { return blockchain; }
    std::string getLatestBlockHash() const { return this->blockchain.back().getHash(); };

    void printBlocks() const {
        for (int i = 0; i < this->blockchain.size(); ++i) std::cout << getBlock(i) << '\n';
    }

   public:
    void initBlockchain();
    std::string serialize() const;
    void addBlock(int counter, int difficulty, std::string minedTime, std::string hash, std::string prevHash,
                  std::string nonce, std::vector<std::string>& merkle);
};

/*
    класс управления блокчейном: инициальзацией, добавлением, хранит историю
*/