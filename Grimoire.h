#include "dependencies.h"
#ifndef HashTable_h
#define HashTable_h

struct MapEntry {    
    string key;
    string value;
    MapEntry(string k, string v):key(k), value(v){}

    operator string() const { return key;}
};


// Template class for dyanmically sized hashtable (grimoire)
template <class T>
class HashTable {
    private:
        double size = 5;
        double numElements =0;
        T * table = 0;       // 0 is a nice C++ nullptr equilvalent 
        bool invalid = false;
        
    public:
        vector <string> keyset;
        operator bool() const{return !invalid;}
    
        HashTable (){
            table = new T [(int)size];
            for (int i =0; i< size; i++){
                table[i] = nullptr;
            }
        }

        void reinitalize() {    // used after clear is run 
            size =5;
            numElements =0;
            table = new T [(int)size];
            for (int i =0; i< size; i++){
                table[i] = nullptr;     // fill with nullptr
            }
            invalid = false;
        }

        double getTableSize(){return size;}

        double getSize(){return numElements;}

        void put(T t){      // used for insertions sometimes a rehash is required 
            // int hash = hashFunction((string) t, size);
            int hash = hashFunction( (string) *t, size);
            int probe = 1;   // offset used in open addressing (could b replaced with second hash function)

            if (numElements / size < 0.70){     // loading factor, if this is exceeded, rehash witha new size
                while (table[hash] != nullptr){     // iterate until a free spot is found
                    hash = (hash + probe) % (int) size;
                }
                table[hash] = t;    
            } else {
                int divisor = calculateDivisor(size);    // calculate new size
                T * newtable = new T[divisor];      // set newly sized table
                for (int i =0; i< divisor; i++){    // initalize new table of double the size 
                    newtable[i] = nullptr;
                }
                T * tempTable = table;
                table = newtable;
                // REHASH PREVIOUS VALUES INTO NEW TABLE 
                for (int i =0; i<size; i++){
                    if (tempTable[i] != nullptr){
                            hash = hashFunction((string) *tempTable[i], divisor);
                            probe = 1;
                            while (table[hash] != nullptr){
                                hash = (hash + probe) % divisor;
                            }
                            table[hash] = tempTable[i];
                    }
                }

                // INSERT original insertion into new table
                hash = hashFunction((string) *t, divisor);
                probe = 1;
                while (table[hash] != nullptr){
                    hash = (hash + probe) % divisor;
                }
                table[hash] = t;
                delete [] tempTable;
                size = divisor;
            }
            keyset.push_back( (string)*t);
            numElements ++;
        }

        T get(string str){      // get element 
            // cout << str << endl;
            int hash = hashFunction(str, size);
            int f = hash;
            if (table[hash] == nullptr){    // element is not found
                return 0;
            } else {
                int probe = 1;
                int count =0;
                while (table[hash] != nullptr && count < size){     // iterate through addresses
                    count ++;
                    if ((string) *table[hash] == str){
                        return table[hash];
                    }
                    hash = (hash + probe) % (int) size;
                }
                return 0;       // element not found 
            }
        }

        bool update(string str, T t){       // update values
            int hash = hashFunction(str, size);
            if (table[hash] == nullptr){
                return false;
            } else {
                int probe = 1;
                while (table[hash] != nullptr){
                    if ((string) *table[hash] == str){
                        delete table[hash];     // delete previous object
                        table[hash] = t;    //assign new objects
                        return true;
                    }
                    hash = (hash + probe) % (int) size;
                }
                return false;
            }
        }

        int calculateDivisor(int s){    // calculate new size   
            int baseHash = (6 - (2*(int)s % 6)) + 2 * s;        // almost every prime of the form 6n+1 or 6n-1 
            for (int i =0; i<size*2; i++){
                if (isPrime(baseHash-1)){   // see if 6n-1 is prime or not
                    return baseHash-1;
                } else if (isPrime(baseHash+1)){ // see if 6n+1 value is prime or not
                    return baseHash+1;
                } else {
                    baseHash = baseHash + 6;
                }
            }
            return baseHash;
        }

        bool isPrime(int n){
            for (int i=2; i<n; i++){
                if (n % i == 0)
                    return false;
            }
            return true;
        }

        void printAll(){
            for (int i =0; i<size; i++){
                if (table[i] == nullptr){
                    cout << "nullptr" << endl;
                } else {
                    cout << (string) (*table[i]) << endl;
                }
            }
        }
        
        int hashFunction(string str, int s){    
            // 61 used cause theres about 58 useful characters that can be inputed and 61 is the nearest prime
            const int g = 61;
            
            int hash =0; 
            for ( int i = 0; i<str.length(); i++){         
                hash = abs(g  * hash + (str.at(i)));     // useful string characters begin at 48 
            }
            return hash % s;
        }

        void clear(){
            // MANAGE MEMORY
            if (table != nullptr){      
                for (int i =0 ; i<size; i++){   
                    delete table[i];    // delete element 
                }
                keyset.clear();
                delete[] table;     // delete pointer arrat
                table = 0;          // reinitalize as NULL
                invalid = true;
            }
        }
};
#endif