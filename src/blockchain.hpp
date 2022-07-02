//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCKCHAIN_HPP
#define MATADAAN_BLOCKCHAIN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "block.hpp"
#include "../lib/utils.hpp"

using namespace std;

//

class Blockchain{
public:
    Blockchain(int genesis =1);
//    Block getBlock(int index);
//    int addBlock(int index, string prevHash, string hash, string nonce, vector<string> &merkle);
//    int numOfBlocks();
//    string getLatestBlockHash();

private:
    // A dynamic arrays of block which can resize itself is stored as blockchain
    // Vector used as it fulfills the above criteria and is easy to get the last Block of the chain

    vector<unique_ptr<Block> > blockchain;
};


Blockchain::Blockchain(int genesis) {

    /* If 0 is passed while creating the blockchain, it is considered as the genesis block
     * For Genesis block, initializing the values by creating a previous hash of "00000000000000"
     * and a merkel of "Genesis Block!" which will be considered to have a merkelRoot of
     * sha256("Genesis Block!")
    */
    if (genesis==0){
        // Initializing a vector of strings
        vector<string> v;
        // Adding a string "Genesis Block" to the vector
        v.push_back("Genesis Block");

        // Generating the Hash of the block and nonce of the first block,
        // First block has previous block hash as "00000000000000" and index 0

        auto hash_nonce_pair = findHash(0,"00000000000000",v);

        /*
         * Adding the block to the blockchain by adding the block's
         *  * index
         *  * previous Hash which is "00000000000000"
         *  * own Hash which is generated from findHash()
         *  * nonce which is later used for Proof of Work(PoW)
         *
         *  this -> blockchain is a vector of blocks which will be adding blocks into it.
         */
        this -> blockchain.push_back(std::make_unique<Block>(0,string("00000000000000"),hash_nonce_pair.first,hash_nonce_pair.second,v));
        std::cout<<"Created blockchain!\n";
    }
}
#endif //MATADAAN_BLOCKCHAIN_HPP
