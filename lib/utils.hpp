//
// Created by Aavash on 7/2/2022.
//

#ifndef MATADAAN_UTILS_HPP
#define MATADAAN_UTILS_HPP

#include <string>
#include <vector>
#include <iostream>
#include "sha256.hpp"

#include <memory>
#include <stdexcept>

/*
     * merkelRoot is the unique hash which includes all the previousHash to generate a new hash
     * which is different for every block as every block has different number and list of previousHashes
     *
     * To generate a merkelRoot, iterate through all the hashes in the merkel and hash them with
     * one another until a single hash is generated.
     *
     * This is a time-consuming step, and it is responsible for making blockchain technology secure
     * as it goes on increasing.
 */
std::string getMerkleRoot(const std::vector<std::string> &merkle) {
    std::cout<<"\nFinding Merkle Root.... \n";
    // If this is the genesis block, return ""
    if (merkle.empty())
        return "";
    // If it is the block just next to the genesis block i.e. the first block with actual data
    // Return the sha256 hash of the merkel of the genesis block
    else if (merkle.size() == 1){
        return sha256(merkle[0]);
    }
    /*
     * For all other blocks except the above-mentioned blocks
     *
    */
    std::vector<std::string> new_merkle = merkle;

    /*
     * Iterating through the previous hashes to generate a single root hash known as merkelRoot
    */

    while (new_merkle.size() > 1) {
        // If odd number of hashes in the provided merkel, evening it out.
        if ( new_merkle.size() % 2 == 1 )
            new_merkle.push_back(merkle.back());

        std::vector<std::string> result;

        /*
         * Iterate through all the previous hashes in the merkel
         * to get a "merkelRoot" which includes all the previous hashes
         * and is unique for every block.
         */
        for (int i=0; i < new_merkle.size(); i += 2){
            std::string var1 = sha256(new_merkle[i]);
            std::string var2 = sha256(new_merkle[i+1]);
            std::string hash = sha256(var1+var2);
            // printf("---hash(hash(%s), hash(%s)) => %s\n",new_merkle[0].c_str(),new_merkle[1].c_str(),hash.c_str());
            result.push_back(hash);
        }
        //
        new_merkle = result;
    }
    return new_merkle[0];

}


//
// Basically calculate a legit hash and getting a nonce(number-only-used-once) of the calculated has
// The "nonce" is used later to check if the hash is legit
/*
 * Hash of current hash is calculated by hashing:
 * SHA256(str(index)+str(previousHash)+str(merkelRoot)+str(nonce))
 * merkelRoot -> A hash which is different for every block and depends on the merkel(list of hashes)
*/
std::pair<std::string,std::string> findHash(int index,const std::string& prevHash, std::vector<std::string> &merkle) {
    std::string header = std::to_string(index) + prevHash + getMerkleRoot(merkle);
    unsigned int nonce;
    for (nonce = 0; nonce < 100000; nonce++ ) {
        std::string blockHash = sha256(header + std::to_string(nonce));
        if (blockHash.substr(0,2) == "00"){
            // cout << "nonce: " << nonce;
            // cout << "header: " << header;
            return std::make_pair(blockHash,std::to_string(nonce));
        }
    }
    return std::make_pair("fail","fail");
}


void print_hex(const char *label, const uint8_t *v, size_t len) {
    size_t i;

    printf("%s: ", label);
    for (i = 0; i < len; ++i) {
        printf("%02x", v[i]);
    }
    printf("\n");
}

#endif //MATADAAN_UTILS_HPP
