#ifndef CHATINTERFACE_HPP
#define CHATINTERFACE_HPP

#include "Interface.hpp"

class ChatInterface : public Interface {
public:
    ChatInterface(std::shared_ptr<Miner>& miner) : Interface(miner) {
        processInput(miner);
    }

private:
    void printHelp() {
        std::cout << "\nType /listNodes to print adresses of all nodes in network:" << std::endl;
        std::cout << "Type /help to print manual:" << std::endl;
        std::cout << "Type /print to print blocks:" << std::endl;
        std::cout << "Type /add to type message" << std::endl;
    }
    void processInput(std::shared_ptr<Miner>& miner) override {
        printHelp();
        for (;;) {
            std::string input;
            std::cin >> input;
            if (input == "/listNodes") {
                printNodes();
            } else if (input == "/help") {
                printHelp();
            } else if (input == "/print") {
                printBlockChain();
            } else if (input == "/add") {
                addMessage();
            }
        }
    }
    void addMessage() {
        std::string message;
        int difficulty = 3;

        std::cout << "Type your message:";
        std::cin.ignore(); // Clear newline character left by previous input
        std::getline(std::cin, message);

        std::string transactionData = "Message: " + message;

        miner->processTransaction(transactionData, difficulty);
    }

    void printNodes() {
        for (auto peer : miner->getPeers()) {
            std::cout << "localhost:" << peer << ", ";
        }
        std::cout << '\n';
    }

    void printBlockChain() {
        auto blockchain = miner->getBlockChain();
        blockchain.printBlocks();
    }
};

class ChatCreator : public Creator {
public:
    bool getInitStage() const override {
        std::cout << "Welcome to Chat!\n";
        std::cout << "If you are creating a new chat, type 'y',\nif you are joining the existing, type 'j':\n";
        char in = 'j';
        std::cin >> in;
        return in == 'y';
    }

    Interface* FactoryMethod(std::shared_ptr<Miner>& miner) const override {
        return new ChatInterface(miner);
    }
};

#endif // CHATINTERFACE_HPP
