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
    // массив транзакции

   public:
    Block() = delete;
    Block(int counter, int difficulty, uint64_t version, std::string hash, std::string prevHash, std::string nonce,
          std::vector<std::string> data, merkle::Tree merkleHash)
        : _counter(counter),
          _difficulty(difficulty),
          _version(version),
          _hash(hash),
          _prevHash(prevHash),
          _nonce(nonce),
          _data(data),
          _merkleHash(merkleHash) {}

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

    std::ostream& operator<<(std::ostream& stream);

    // работа с json
    json serialize();
    std::string deserialize();
    std::string jsonToString(const json& json) { return std::string(json.dump()); }
};
