/*
Обработчик комман из теминала, который обращается к функциям майнера
*/
#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <iostream>
#include <memory>

#include "Miner.hpp"

class Interface {  // Product
   public:
    std::shared_ptr<Miner>& miner;
    Interface(std::shared_ptr<Miner>& miner) : miner{miner} {};
    virtual ~Interface(){};
    virtual void processInput(std::shared_ptr<Miner>& miner) = 0;
};

class CLInterface : public Interface {
   private:
    void printHelp() {
        std::cout << "\nType /listNodes to print adresses of all nodes in network:" << std::endl;
        std::cout << "Type /help to print manual:" << std::endl;
        std::cout << "Type /print to print blocks:" << std::endl;
        std::cout << "Type /add to add transaction" << std::endl;
    }

    void printNodes() {
        for (auto peer : miner->getPeers()) std::cout << "localhost:" << peer << ", ";
        std::cout << '\n';
    }

    void printBlockChain() {
        auto blockchain = miner->getBlockChain();
        blockchain.printBlocks();
    }

    void addTransaction() {
        std::string sender;
        std::string recipient;
        float amount;
        int difficulty = 3;

        std::cout << "Sender:\n";
        std::cin >> sender;

        std::cout << "Recipient:\n";
        std::cin >> recipient;

        std::cout << "Amount:";
        std::cin >> amount;

        std::string transactionData = "Sender: " + sender + ", " + "Recipient: " + recipient + ", " + "Amount: +" +
                                      std::to_string(amount) + "token";
        miner->processTransaction(transactionData, difficulty);
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
                addTransaction();
            }
        }
    }

   public:
    CLInterface(std::shared_ptr<Miner>& miner) : Interface(miner) { processInput(miner); }
};

// тут создаете нужно создать класс подобный

class Creator {
   public:
    // функция в которой мы выбираем запустить ли с y/j и их аналогом в GUI
    // должна возвращать true/false, если genesis/подключение к существующему
    virtual bool getInitStage() const = 0;

    virtual ~Creator(){};
    virtual Interface* FactoryMethod(std::shared_ptr<Miner>& miner) const = 0;
};

class ClICreator : public Creator {
   public:
    bool getInitStage() const override {
        std::cout << "Welcome to Chain, stranger!\n";
        std::cout << "If you are creating a new blockchain, type 'y',\nif you are joining the existing, type 'j':\n";
        char in = 'j';
        std::cin >> in;
        return in == 'y';
    }

    Interface* FactoryMethod(std::shared_ptr<Miner>& miner) const override { return new CLInterface(miner); }
};
#endif