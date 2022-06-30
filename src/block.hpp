//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCK_HPP
#define MATADAAN_BLOCK_HPP


#include <vector>
#include <string>

class Block {
public:
    Block(){};
    Block(int index, std::string prevHash, std::string Hash, std::string timeStamp, std::vector<std::string> data);

    std::string getPrevHash();
    std::string getHash();
    int getIndex();
    std::vector<std::string> getData();
    void toString();
    std::string calculateHash();
    std::string calculateHash(std::string inputStr);
    std::string getStringToHash();
    bool validProof(int last_proof, int proof);
    int proofOfWork(int last_proof);
    //json toJson(void); // needs to include json.hpp which will be created later for json parsering

private:
    int index;
    std::string prevHash;
    std::string blockHash;
    std::string timeStamp;
    std::vector<std::string> data;
    int proof;
};


#endif //MATADAAN_BLOCK_HPP
