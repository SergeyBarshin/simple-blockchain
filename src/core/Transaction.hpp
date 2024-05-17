#pragma once

#include <openssl/lhash.h>

#include <iostream>
#include <string>
#include <vector>

#include "../json/single_include/nlohmann/json.hpp"

class Transaction {
   public:
    static constexpr uint32_t INDEX_NULL = std::numeric_limits<uint32_t>::max();
    int16_t version = 0;

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