#pragma once

#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "MerkleTree.hpp"  //from Merkle to MerkleTree

namespace Utils {
std::string sha256(const std::string str);
std::string merkleMe(const std::string& s1);
std::string merkleMeAgain(const std::string& s1, const std::string& s2);
std::string getMerkleRoot(std::vector<std::string>& txs);
merkle::Hash getMerkleRootM(std::vector<std::string>& txs);
std::pair<std::string, std::string> findHash(int dificulty, int index, std::string prevHash,
                                             std::vector<std::string>& merkle);

}  // namespace Utils