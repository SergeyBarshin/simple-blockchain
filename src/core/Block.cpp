#include "Block.hpp"

void Block::setMerkleHash(std::string message) {
    merkle::Tree::Hash hash(message);
    merkle::Tree tree;
    tree.insert(hash);
}

std::ostream& operator<<(std::ostream& stream, const Block& block) {
    fort::char_table table;
    for (int i = 0; i < block._data.size(); i++) {
        table << fort::header << "Block: " << block._counter << fort::endr << "Time: " << block.minedTime.c_str()
              << fort::endr << "Hash: " << block._hash.c_str() << fort::endr << "Nonce: " << block._nonce.c_str()
              << fort::endr << "Prev: " << block._prevHash.c_str() << fort::endr
              << "Transaction: " << block.deserialize().c_str() << fort::endr;
    }

    stream << table.to_string();
    return stream;
}

json Block::serialize() const {
    json j = {{"difficulty", _difficulty},
              {"counter", _counter},
              {"minedTime", minedTime},
              {"prevHash", _prevHash},
              {"hash", _hash},
              {"nonce", _nonce},
              {"data", _data}};
    return j;
}

std::string Block::deserialize() const {
    // для вывода
    std::string dataString;
    for (int i = 0; i < _data.size(); i++) {
        dataString += _data[i];
    }
    return dataString;
}