#include <iostream>
#include "main.h"

int main() {
    std::cout << "Testing Blockchain..." << std::endl;
    Blockchain blockchain(0);
    std::cout << blockchain.getBlock(0).toJson()<<std::endl;

    // Data must be a vector of string
    std::vector<std::string> data;
    data.push_back(hash::sha256("2002"));
    data.emplace_back("1");
    auto hash_nonce_pair = blockUtils::findHash(1,blockchain.getLatestBlockHash(), data);
    std::cout<<hash_nonce_pair.first<<","<<hash_nonce_pair.second<<std::endl;
    blockchain.addBlock(blockchain.numOfBlocks(),blockchain.getLatestBlockHash(),hash_nonce_pair.first,hash_nonce_pair.second,data);
    std::cout << blockchain.jsonDump()<<std::endl;
    std::cout << voteUtils::isValidVoter(hash::sha256("2002"),blockchain.toJson());

    return 0;
}
