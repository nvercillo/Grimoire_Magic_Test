# HashTable Solver


## Introduction

The purpose of this model is to determine the validity of a ancient grimoire in linear time (very cool idea btw!) 

Key assumption: a valid grimoire is a grimoire which does not contain a verse (rune relationship declaration) which contains a contradiction and also contains all the runes in the verse. This implies that ambiguous grimoires are in fact valid. (This can be easily changed but is what was infered by the desciption)

A dynamically sized hash map strucutre is used to represent a grimoire. The hash map is a template funciton which implements a MapNode. This node contains a string which represents the map key, and two seperate hashtables representing elemenets who are greater than and less than the key. 

The algorithm processes each verse or line of the grimoire, and fills in the data structure with all encoded logic. For example if we know a that a rune "A" comes befoe "B", then we also know that "B" comes after "A". If a contradiction occurs at any line, then then the program terminates and the contradiction is stated.

## Execution 
To run the file, run the make command in the directory with g++ installed and setup. Then generate the grimoire and binaries with:

make

To then test the validity, run the following: 

make run


To generate new grimoires, run ./generate. 



## Grimoire 

### Data Structure 
The hash map implementation used in this program is given an inital size of 5 elements (it is a template class so the 2.) To deal with insert collisions, I have implemented a secondary hashing function which probes the table for an empty spot. However dealing with collions slows the performance of the program, so once the loading factor is exceeded, the table is rehahsed to a new size. Rehashing is also expensive so its optimal to resize as little as possible. This is achieved using the distribution of prime numbers. According to one of Euler's theorems, prime numbers are often of the form 6n +1. As n increases, the proability that 6n +1 decreases, so using a prime of this form we can resize less often. Additionally using a prime number as the new size allows for a more uniformally distributed hashing function. 

### Form
The verses of the grimoire are stored as lines in a text file. For example, the realtionship between different runes is represented as: [A, B,......, N] < K < [Z, Y, ......, M], where the first array represents all the runes explitly stated to be less than a given rune, the second array represents all the runes explicitly stated to be greater than a given node, and K represents the given rune previously referenced. Addionally A to N, Z to M, and K are all arbitrary elements the set of all possible runes.

The number of verses is indcated by the first number in the test file.

For example, the given verse    [A, B] < K < [X, Y] would be pharsed in a magical statement similar to: "K, comes before X and Y, but after A and B.

### Generation 

The generation of a file incorporates the above structure. An arbitrary grimoire is created through the command ./generate (after make.) Firstly an random number between 1 and 100 is generated and used as the number of runes. Then, a random number from 1 to the number of runes is generated as the number of verses in the grimoire. A custom function is then used to encode each key as a string. In each row, a random number between 0 and the square root of the number of grimoires of runes is then used to create random connections between the nodes.

Note: all random numbers in this program are pseduo-random numbers as there is a slightly non-uniform probability distrubutions across any given range.

## Run time

Because of the use of a hash table structure, put, and get functions into each implementation of the strucutre is on the average case constant (O(1)). On worse case, the insert and get functions are linear, however because of how the tables are resized, this results in an average case of O(1).  Therefore the runtime for the overall program is linear to the number of relation, or more formally there is a tight-bound of O(A x N) where A is the average number of connections per rune, and N is the number of runes.  

## Contact Information 
I appreciate the opportunity to compelte this challenge for 1QBit and would love for the opportunity to discuss my aptitude with the team further. My email is snvercil@uwaterloo.ca and phone number 416-459-9071.  My porfolio and resume can be found at [a link](https://stefanvercillo.ca)