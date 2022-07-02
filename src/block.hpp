//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCK_HPP
#define MATADAAN_BLOCK_HPP


#include <vector>
#include <string>
#include <iostream>
#include "../lib/json.hh"

class Block {
public:
    Block(int index, std::string prevHash, std::string Hash, std::string nonce, std::vector<std::string> data);

    std::string getPrevHash();
    std::string getHash();
    int getIndex();
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
    this->prevHash = prevHash;
    this->blockHash = Hash;
    this-> nonce = nonce;
    this->data = data;
}

int Block::getIndex() {
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
