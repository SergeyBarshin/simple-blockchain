#include "Block.hpp"

void Block::setMerkleHash(std::string message) {
    merkle::Tree::Hash hash(message);
    merkle::Tree tree;
    tree.insert(hash);
}

std::ostream& Block::operator<<(std::ostream& stream) {
    fort::char_table table;
    for (unsigned i = 0; i < _data.size(); i++) {
        table << fort::header << "Block: " << _counter << fort::endr << "Time: " << minedTime.c_str() << fort::endr
              << "Hash: " << _hash.c_str() << fort::endr << "Nonce: " << _nonce.c_str() << fort::endr
              << "Prev: " << _prevHash.c_str() << fort::endr << "Transaction: " << deserialize().c_str() << fort::endr;

        std::cout << table.to_string() << std::endl;
    }

    stream << table.to_string();
    return stream;
}

json Block::serialize() {
    json j = {{"difficulty", _difficulty},
              {"counter", _counter},
              {"minedTime", minedTime},
              {"prevHash", _prevHash},
              {"hash", _hash},
              {"nonce", _nonce},
              {"data", _data}};
    return j;
}

std::string Block::deserialize() {
    // для вывода
    std::string dataString;
    for (int i = 0; i < _data.size(); i++) {
        dataString += _data[i];
    }
    return dataString;
}