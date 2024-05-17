#include "Utils.hpp"

namespace Utils {

std::string sha256(const std::string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

merkle::Hash getMerkleRootM(std::vector<std::string>& txs) {
    std::vector<merkle::Tree::Hash> hashes(txs.size());
    merkle::Tree mt;
    for (unsigned i = 0; i < hashes.size(); i++) {
        mt.insert(sha256(txs[i]));
    }
    merkle::Tree::Hash root = mt.root();
    return root;
}

std::pair<std::string, std::string> findHash(int dificulty, int index, std::string prevHash,
                                             std::vector<std::string>& txs) {
    std::string target = "";
    for (unsigned i = 0; i < dificulty; i++) {
        target += std::to_string(0);
    }

    std::string header = std::to_string(index) + prevHash + getMerkleRootM(txs).to_string();
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Mining...\n";
    for (int i = 384993400; i >= 0; i--) {
        std::string blockHash = sha256(header + std::to_string(i));
        if (blockHash.substr(0, dificulty) == target) {
            std::cout << "FIND HASH: " << blockHash << "\r" << std::endl;

            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = finish - start;

            std::this_thread::sleep_for(std::chrono::milliseconds(500));  // задержка для красоты
            std::cout << "Elapsed Time: ~" << (elapsed.count() / 1000) << " seconds" << std::endl;
            std::cout << std::endl;
            return std::make_pair(blockHash, std::to_string(i));
        }
    }
    return std::make_pair("", "");
}

}  // namespace Utils