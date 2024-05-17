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

std::string merkleMe(const std::string& s1) { return sha256(s1); }

std::string merkleMeAgain(const std::string& s1, const std::string& s2) { return sha256(sha256(s1) + sha256(s2)); }

std::string getMerkleRoot(std::vector<std::string>& merkle) {
    bool mutation = false;

    if (merkle.size() == 1) {
        return sha256(merkle[0]);
    }

    std::vector<std::string> new_merkle = merkle;

    while (new_merkle.size() > 1) {
        if (new_merkle.size() % 2 == 1) new_merkle.push_back(merkle.back());

        std::vector<std::string> result;

        for (int i = 0; i < new_merkle.size(); i += 2) {
            result.push_back(sha256(new_merkle[i]) + sha256(new_merkle[i++]));
        }
        new_merkle = result;
    }
    return new_merkle[0];
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