#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../json/single_include/nlohmann/json.hpp"
#include "../libfort/lib/fort.hpp"
#include "MerkleTree.hpp"
#include "Transaction.hpp"

using json = nlohmann::json;

/*
  Блокчейн - упорядоченный список блоков. Каждый блок содержит хэш SHA-256 предыдущего блока,
  связывающий их в хронологическом порядке. Блокчейн поддерживается p2p сетью.
  Отдельные блоки, публичные адреса и транзакции внутри блоков являются общедоступной информацией.
*/

class Block {
   public:
    std::string minedTime;

   private:
    int _counter = 0;
    int _difficulty = 0;
    uint64_t _version = 0;
    std::string _hash;
    std::string _prevHash;
    std::string _nonce;
    std::vector<std::string> _data;
    merkle::Tree _merkleHash;

    // массив транзакций, которые происходили с блоком
    // std::vector<Transaction>* transactions = nullptr;

   public:
    Block() = default;
    Block(int counter, int difficulty, std::string minedTime, std::string hash, std::string prevHash, std::string nonce,
          std::vector<std::string> data)
        : _counter(counter),
          _difficulty(difficulty),
          minedTime(minedTime),
          _hash(hash),
          _prevHash(prevHash),
          _nonce(nonce),
          _data(data) {}

   public:
    std::string getPreviousHash() const { return _prevHash; }
    std::string getHash() const { return _hash; }
    int getCounter() const { return _counter; }
    std::vector<std::string> getData() const { return _data; }
    int getNonce() const { return std::stoi(_nonce); }

    static std::string getTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d | %X");
        return ss.str();
    }

    void setMerkleHash(std::string message);

    friend std::ostream& operator<<(std::ostream& stream, const Block& block);

    // работа с json
    json serialize() const;
    std::string deserialize() const;
    std::string jsonToString(const json& json) const { return std::string(json.dump()); }
};
