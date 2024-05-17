/*
Обработчик комман из теминала, который обращается к функциям майнера
*/
#include <iostream>

#include "Miner.hpp"

class Interface {  // Product
   public:
    virtual ~Interface(){};
    virtual void processInput(Miner miner) = 0;
};

class CLInterface : public Interface {
   public:
    CLInterface() { std::cout << "CLI\n"; }
    void processInput(Miner miner) override { std::cout << "CLI1\n"; }
};

class Creator {  // в начале иниициализируем блокчейн
   private:
    virtual void initBlockchain() = 0;  // функция в которой мы выбираем запустить ли с y/j и их аналогом в GUI

   public:
    virtual ~Creator(){};
    virtual Product* FactoryMethod() const = 0;

    // нужно где-то спрашивать y/j
};

class ClICreator : public Creator {
   private:
   public:
    Interface* FactoryMethod() const override {
        std::cout << " y/j?";
        return new CLInterface();
    }
};