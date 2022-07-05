//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCKCHAIN_HPP
#define MATADAAN_BLOCKCHAIN_HPP

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "block.hpp"
#include "utils.hpp"
#include "../lib/json.hpp"


//

class Blockchain{
public:
    explicit Blockchain(int genesis =1);
    Block getBlock(int index);
    int addBlock(int index, const std::string& prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle);
    int numOfBlocks();
    std::string getLatestBlockHash();
    std::string jsonDump();
    int replaceChain(nlohmann::json chain);
    nlohmann::json toJson();
private:
    // A dynamic arrays of block which can resize itself is stored as blockchain
    // Vector used as it fulfills the above criteria and is easy to get the last Block of the chain

    std::vector<std::unique_ptr<Block> > blockchain;
};



Blockchain::Blockchain(int genesis) {

    /* If 0 is passed while creating the blockchain, it is considered as the genesis block
     * For Genesis block, initializing the values by creating a previous hash of "00000000000000"
     * and a merkel of "Genesis Block!" which will be considered to have a merkelRoot of
     * sha256("Genesis Block!")
    */
    if (genesis==0){
        // Initializing a vector of strings
        std::vector<std::string> v;
        // Adding a string "Genesis Block" to the vector
        v.emplace_back("Genesis Block");

        // Generating the Hash of the block and nonce of the first block,
        // First block has previous block hash as "00000000000000" and index 0
        auto hash_nonce_pair = blockUtils::findHash(0,"00000000000000",v);

        /*
         * Adding the block to the blockchain by adding the block's
         *  * index
         *  * previous Hash which is "0000000000"
         *  * own Hash which is generated from findHash()
         *  * nonce which is later used for Proof of Work(PoW)
         *
         *  this -> blockchain is a vector of blocks which will be adding blocks into it.
         */
        this -> blockchain.push_back(std::make_unique<Block>(0,std::string("0000000000"),hash_nonce_pair.first,hash_nonce_pair.second,v));
        std::cout<<"Created blockchain!\n";
    }
}

/*
 * Returns the class Block after getting the index of the block
*/
Block Blockchain::getBlock(int index){
    for(int i =0;i<this->blockchain.size();i++){
        if(blockchain[i]->getIndex()==index){
            return *(blockchain[i]);
        }
    }
    throw std::invalid_argument("Index does not exist.");
}

/*
 * After Calculating the hash of new block, it is used to validate the block and
 * add the new block to the chain
*/

int Blockchain::addBlock(int index, const std::string& prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle) {
    std::string header = std::to_string(index) + prevHash + blockUtils::getMerkleRoot(merkle) + nonce;
    if ( (!(hash::sha256(header).compare(hash))) && (hash.substr(0,2) == "00" ) && (index == blockchain.size())) {
        printf("Block hashes match --- Adding Block %s \n",hash.c_str());
        this->blockchain.push_back(std::make_unique<Block>(index,prevHash,hash,nonce,merkle));
        return 1;
    }
    std::cout << "Hash doesn't match criteria\n";
    return 0;
}

/*
 * Get number of blocks in the chain
 */

int Blockchain::numOfBlocks(){
    return this->blockchain.size();
}

std::string Blockchain::getLatestBlockHash() {
    // If the size of blockchain is 5, getting the hash of the block of index 4
    return this->blockchain[this->blockchain.size()-1]->getHash();
}

/*
 * All the data of the blockchain and its block in parsed json format
 * then converted into string with indentation of 3 spaces
*/
std::string Blockchain::jsonDump() {
    nlohmann::json jsonData;
    jsonData["length"] = this->blockchain.size();

    for(int i = 0; i<blockchain.size();i++){
        jsonData["data"][this->blockchain[i]->getIndex()]=this->blockchain[i]->toJson();
    }

    // Indent set to 3, 3 indentation spaces while separating the data
    // Json data to string
    return jsonData.dump(3);
}

nlohmann::json Blockchain::toJson(){
    nlohmann::json jsonData;
    jsonData["length"] = this->blockchain.size();

    for(int i = 0; i<blockchain.size();i++){
        jsonData["data"][this->blockchain[i]->getIndex()]=this->blockchain[i]->toJson();
    }

    return jsonData;
};
/*
* If the chain of another node is ahead of self node, replacing the self chain is necessary
* After calling from another node, json data is supplied, which will then be
* deserialized and stored as the chain in vector<Block> which is blockchain.
*/
int Blockchain::replaceChain(nlohmann::json chain) {
    // Removes all the block of the chain except the Genesis block
    // which need not be popped since it is same for all the nodes
    while(this->blockchain.size()){
        this->blockchain.pop_back();
    }

    // Adding blocks from the chain of another node from the json data
    for(int a=1; a<chain["length"].get<int>();a++){
        // Storing the json data of each block at a time
        auto block = chain["data"][a];
        // Changing the data into the list(vector) of strings
        auto data = block["data"].get<std::vector<std::string>>();
        this->addBlock(block["index"].get<int>(),block["prevHash"].get<std::string>(),block["hash"].get<std::string>(),block["nonce"].get<std::string>(),data);
    }
    return 1;
}
//
#endif //MATADAAN_BLOCKCHAIN_HPP
