# Blockchain in matadaan

Matadaan is a decentralized voting system, implementing the concept of
blockchain technology, in an Object oriented approach,
built as a semester project, abiding by the guidelines of
[DoECE, Pulchowk Campus](https://doece.pcampus.edu.np).

The concepts of blockchain were used while making the project.
We have fragmented the concept in the following parts to make it easy to understand:

1. [Block](#block)
   1. Components
   2. Functions
2. [Blockchain](#blockchain)
   1. Components
   2. Functions


## Block:
A block is a singular component of a blockchain. The combination
of blocks make the blockchain. It consists of different components which
makes it unique from other blocks.

### Components:
There are various components of a block. For this project, since this is a simple 
PoC, we have included the basic components which includes:

1. Index
2. Current Hash
3. Previous Hash
4. Number-only-used-once (nonce)
5. Data

> Index:

    It is the component of block which is used to track the
    number of blocks present in the chain, and the current index 
    of the block gives a indication of how far is the block from 
    the initial block. And is a number to index the blocks as the
    name suggests.

> Current Hash:

    Each block in the blockchain has a unique identity in its own
    to seperate itself from every other blocks. In a block, it is 
    stored as a hash.