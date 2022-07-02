//
// Created by Aavash on 6/30/2022.
//

#ifndef MATADAAN_SHA256_HPP
#define MATADAAN_SHA256_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <openssl/sha.h>
#include <openssl/ripemd.h>

using namespace std;

std::string sha256(std::string str){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    // use a SHA256_CTX structure which is includes unsigned int long values for SHA hashes
    // It is required to initialize a SHA256 Hash using openssl
    SHA256_CTX sha256;

    /*
     * Used the above used structure to initialize a SHA256 hash
     * */
    SHA256_Init(&sha256);
    /*
     *can be called repeatedly with chunks of the message to be hashed (len bytes at data).
     */
    SHA256_Update(&sha256, str.c_str(), str.size());
    /*
     * places the message digest in md, which must have space for
     * SHA_DIGEST_LENGTH == 20 bytes of output, and erases the SHA_CTX*/

    SHA256_Final(hash, &sha256);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();

};
//hex in iostream
//SHA256_DIGEST_LENGTH, SHA256_CTX in openssl/sha.h
//setw() and setfill() in iomanip
//stringstream in sstream
#endif //MATADAAN_SHA256_HPP
