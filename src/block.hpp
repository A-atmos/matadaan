//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_BLOCK_HPP
#define MATADAAN_BLOCK_HPP

#pragma once


#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include "../lib/json.hpp"

#include "../lib/sha256.hpp"


namespace Blockchain{
        class Block {
            public:
            Block()
            {};
            Block(int
            index, std::string
            prevHash, std::string
            Hash, std::string
            nonce, std::vector<std::string>
            data);

            std::string getPrevHash();
            std::string getHash();
            int getIndex() const;
            std::vector<std::string> getData();
            void toString();
        //    bool validProof(int last_proof, int proof);
        //    int proofOfWork(int last_proof);
            nlohmann::json
            toJson(); // needs to include json.hpp which will be created later for json serialization/deserialization
            std::string getVote();
            friend std::string getMerkleRoot(const std::vector<std::string> &merkle);



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
            this->nonce = std::move(nonce);
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
            for (int i = 0; i < data.size(); i++)
                dataString += data[i] + ", ";
            std::cout << "\n-------------------------------\n";
            std::cout << "Block " << index << "\nHash: " << this->blockHash << "\nPrevious Hash:" << this->prevHash
                      << "\nContents: " << dataString;
            std::cout << "\n-------------------------------\n";
        }

        nlohmann::json Block::toJson() {
            nlohmann::json jsonData;
            jsonData["index"] = this->index;
            jsonData["hash"] = this->blockHash;
            jsonData["nonce"] = this->nonce;
            jsonData["data"] = this->data;
            jsonData["prevHash"] = this->prevHash;

            return jsonData;
        }

        std::string Block::getVote() {

            return data[1];
        }



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
            std::cout << "\nFinding Merkle Root.... \n";
            // If the merkel is empty, return ""
            if (merkle.empty())
                return "";
                // If it is the genesis block i.e. the initialization block
                // return the sha256 hash of the merkel of the genesis block
                // which is "Genesis Block"
            else if (merkle.size() == 1) {
                return hash::sha256(merkle[0]);
            }
            /*
             * For all other blocks except genesis block
             *
            */
            std::vector<std::string> new_merkle = merkle;

            /*
             * Iterating through the previous hashes to generate a single root hash known as merkelRoot
            */

            while (new_merkle.size() > 1) {
                // If odd number of hashes in the provided merkel, evening it out.
                if (new_merkle.size() % 2 == 1)
                    new_merkle.push_back(merkle.back());

                std::vector<std::string> result;

                /*
                 * Iterate through all the previous hashes in the merkel
                 * to get a "merkelRoot" which includes all the previous hashes
                 * and is unique for every block.
                 */
                for (int i = 0; i < new_merkle.size(); i += 2) {
                    std::string var1 = hash::sha256(new_merkle[i]);
                    std::string var2 = hash::sha256(new_merkle[i + 1]);
                    std::string hash = hash::sha256(var1 + var2);
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

};

#endif //MATADAAN_BLOCK_HPP
