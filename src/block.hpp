//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCK_HPP
#define MATADAAN_BLOCK_HPP


#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include "../lib/json.hh"

class Block {
public:
    Block(int index, std::string prevHash, std::string Hash, std::string nonce, std::vector<std::string> data);

    std::string getPrevHash();
    std::string getHash();
    int getIndex() const;
    std::vector<std::string> getData();
    void toString();
//    bool validProof(int last_proof, int proof);
//    int proofOfWork(int last_proof);
    //json toJson(void); // needs to include json.hpp which will be created later for json parsering

private:
    int index;
    std::string prevHash;
    std::string blockHash;
    std::string nonce;
    std::vector<std::string> data;
};

Block::Block(int index, std::string prevHash, std::string Hash, std::string nonce, std::vector<std::string> data) {
    this->index = index;

    // Since the below are stings, std::move gives an efficient transfer of data
    this->prevHash = std::move(prevHash);
    this->blockHash = std::move(Hash);
    this-> nonce = std::move(nonce);
    this->data = std::move(data);
}

int Block::getIndex() const {
    return this->index;
}

std::string Block::getHash() {
    return this->blockHash;
}

std::vector<std::string> Block::getData() {
    return this->data;
}

std::string Block::getPrevHash() {
    return this->prevHash;
}

void Block::toString() {
    std::string dataString;
    for (int i=0; i < data.size(); i++)
        dataString += data[i] + ", ";
    std::cout<<"\n-------------------------------\n";
    std::cout<<"Block "<<index<<"\nHash: "<<this->blockHash<<"\nPrevious Hash:"<<this->prevHash<<"\nContents: "<<dataString;
    std::cout<<"\n-------------------------------\n";
}

#endif //MATADAAN_BLOCK_HPP
