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

    enum class Stage : int8_t { UNDEFINED = 0, INIT = 1, GENESIS = 2, JOIN };
    Stage stage = Stage::UNDEFINED;

   private:
    int _genesis = 0;
    float _version = 0.1;  // major.miner ver

   public:
    BlockChain() = default;
    ~BlockChain(){};

   public:
    Block getBlock(int counter) const;

    int getNumOfBlocks() const { return this->blockchain.size(); }
    int getGenesis() const { return _genesis; }
    void setGenesis(int genesis) { this->_genesis = genesis; }
    Stage getStage() { return this->stage; }

    std::vector<Block> getBlockChain() const { return blockchain; }
    std::string getLatestBlockHash() const { return this->blockchain.back().getHash(); };

    void printBlocks() const {
        for (int i = 0; i < this->blockchain.size(); ++i) std::cout << getBlock(i) << '\n';
    }

   public:
    void behave(Stage stage);
    std::string serialize() const;
    void addBlock(int counter, int difficulty, std::string minedTime, std::string hash, std::string prevHash,
                  std::string nonce, std::vector<std::string>& merkle);
};

/*
    класс управления блоками и майнингом
*/