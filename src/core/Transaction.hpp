#pragma once

#include <openssl/lhash.h>

#include <iostream>
#include <string>
#include <vector>

#include "../json/single_include/nlohmann/json.hpp"

class Transaction {
   private:
    float amount;
    std::unique_ptr<std::string> in;
    std::unique_ptr<std::string> out;
    uint64_t hash;

   public:
    Transaction() = default;

    Transaction(const Transaction&) = default;
    Transaction& operator=(const Transaction&) = default;

    Transaction(float amount, std::unique_ptr<std::string> out, std::unique_ptr<std::string> in)
        : amount(amount), in(std::move(in)), out(std::move(out)) {}

   public:
    // uint64_t calculateHash() const {};
    const uint64_t getHash() const { return hash; }
};
/*
Класс транзакций. Нужет чтобы переделать транзацию с 'просто строки' на более сложную правильную сущьность
*/