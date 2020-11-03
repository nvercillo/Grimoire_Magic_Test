#include "Grimoire.h"


void process_input(int * verse_num);
vector<string> process_str (string str);
    
struct RuneConnections {
    HashTable<string*> gt_map; // set of runes greater than key
    HashTable<string*> lt_map; // set of runes less than key
    string key; 
    RuneConnections(string k):key(k){}
    ~RuneConnections(){
        gt_map.clear();
        lt_map.clear();
    }
    operator string() const { return key;}
};


int main(){
    string str; 
    
    
    cin >> str; 

    std::cout <<  "Calculating validity of grimoire with " << str <<  " verses: " << endl;
    

    int verse_num =0;

    while (cin >> str){
        if (str.compare("Num_runes:") == 0){
            cout << "." << endl;
            cout << "." << endl;
            process_input(&verse_num);
        }
    }

    
    return 0;
}


void process_input(int * verse_num){ 

    *verse_num ++;
    HashTable<RuneConnections*> grimoire;  // initialize data structure
    int line_ele =0;   // used to determine where in input line
    int line_num =0;   // counts the number of input lines that we're at 
    vector<string> less_than_key;   // will contain all elements less rune 
    vector<string> greater_than_key;    // will contain all elements greater rune 
    string key = "";
    string str;


    vector<string> verses;
    
    auto start = high_resolution_clock::now();  // start clock

    
    cin >> str;
    int size = stoi(str);

    while (cin >> str){  
        if (str.compare("Num_runes:") ==0){
            break;
        }
        verses.push_back(str);
        if (line_ele ==0){
            less_than_key = process_str(str);  // set vector 
            line_ele ++;
        } else if (line_ele == 2){

            key = str; // cast to string 
            line_ele++;
        } else if (line_ele == 4){
            line_num ++; 
            greater_than_key = process_str(str);  // set vector

            // if verse contains no relational  information, skip entry  
            if (less_than_key.size() == 0 && greater_than_key.size()== 0){
                line_ele = 0;
                continue;
            }
         
            RuneConnections * value = grimoire.get(key);  
            if (value == 0){ // check if get returns null
                value = new RuneConnections(key);   // create new entry for rune
                grimoire.put(value);
            }   // else entry already exists


            // establish connections for all elements less than key and check for logical contradiction
            for (int i =0; i< less_than_key.size(); i++){       
    
                RuneConnections * lt = grimoire.get(less_than_key[i]);
                if (lt == 0){
                    lt = new RuneConnections(less_than_key[i]);
                    lt->gt_map.put(new string(key));    // key greater than rn->key
                    grimoire.put(lt);
                }

                for (int j =0; j< greater_than_key.size(); j++){
                    RuneConnections * gt = grimoire.get(greater_than_key[j]);
                    if ( i == 0){
                        if (gt == 0){
                            gt = new RuneConnections(greater_than_key[j]);
                            gt->lt_map.put(new string(key));
                            grimoire.put(gt);
                        }
                    }
                    if (lt->lt_map.get(greater_than_key[j]) != 0){
                        // invalid
                        std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " <<  line_num << endl;
                        std::cout << "Rational: "<< less_than_key[i] << " cannot be bother greater and less than " << greater_than_key[j] << endl;
                        auto stop = high_resolution_clock::now();  // stop clock()
                        auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                        std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
                        return;
                    }
                                         
                    if (gt->gt_map.get(less_than_key[i]) != 0){
                        // invalid
                        std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " <<  line_num << endl;
                        std::cout << "Rational: "<< less_than_key[i] << " cannot be bother greater and less than " << greater_than_key[j] << endl;
                        auto stop = high_resolution_clock::now();  // stop clock()

                        auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                        std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
                        return;
                    }

                    // insert new connections into grimoire
                    if (lt->gt_map.get(greater_than_key[j]) != 0){  // if doesnt exist, insert
                        lt->gt_map.put(new string (greater_than_key[j]));
                    }

                    if (gt->lt_map.get(less_than_key[i]) != 0){  // if doesnt exist, insert
                        gt->lt_map.put(new string(less_than_key[i]));
                    }
                }

                
                if (value->gt_map.get(less_than_key[i]) == 0){ // first contradiction not found 
                    if (value->lt_map.get(less_than_key[i]) == 0){   // if first insertion
                        value->lt_map.put(new string(less_than_key[i]));    
                    }

                    
                    if (lt->gt_map.get(key) == nullptr){
                        // check if contradiction occurs
                        if (lt->lt_map.get(key) != nullptr){  // less_than_key[i] cannot be greater than key and less than key 
                            std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " <<  line_num << endl;
                            std::cout <<"Rational: " <<  less_than_key[i] << " cannot be both greater and less than " << key << "!" <<  endl; 
                            auto stop = high_resolution_clock::now();  // stop clock()

                            auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                            std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
                            return;
                        }  
                        // check that all entries less than key are less than all those greater than key

                        for (int w=0; w<lt->lt_map.keyset.size(); w++){
                            if (value->lt_map.get(lt->lt_map.keyset[w]) ==0){
                                value->lt_map.put(new string(lt->lt_map.keyset[w]));
                            }  
                        }

                        lt->gt_map.put(new string(key));
                    }  // else skip entry already exists

                } else {    // contradiction
                    std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " << line_num << endl;
                    std::cout <<"Rational: " <<   less_than_key[i] << " cannot be bother greater and less than " << key << endl;
                    auto stop = high_resolution_clock::now();  // stop clock()

                    auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                    std::cout << "Run time: " <<  duration.count() << " ms " << endl;    
                    return;
                }
            
            }
            
            
            // establish connections for all elements greater than key and check for logical contradiction
            for (int i =0; i< greater_than_key.size(); i++){
                if (value->lt_map.get(greater_than_key[i]) == 0){
                    if (value->gt_map.get(greater_than_key[i]) ==0){
                        value->gt_map.put(new string(greater_than_key[i]));
                    }
                    
                    RuneConnections * rn = grimoire.get(greater_than_key[i]);
                    if (rn == nullptr){
                        rn = new RuneConnections(greater_than_key[i]);
                        rn->lt_map.put(new string(key));    // key less than rn->key
                        grimoire.put(rn);

                    } else if (rn->lt_map.get(key) == nullptr){
                        // check if contradiction occurs
                        if (rn->gt_map.get(key) != nullptr){  // greater_than_key[i] cannot be greater than key and less than key 
                            std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " << line_num << endl;
                            std::cout << "Rational: " <<   greater_than_key[i] << " cannot be bother greater and less than " << key << endl;
                            auto stop = high_resolution_clock::now();  // stop clock()

                            auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                            std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
                            return ;
                        }  

                        for (int w=0; w<rn->gt_map.keyset.size(); w++){
                            if (value->gt_map.get(rn->gt_map.keyset[w]) ==0){
                                value->gt_map.put(new string(rn->gt_map.keyset[w]));
                            }  
                        }

                        rn->lt_map.put(new string(key));
                    }  // else skip entry already exists
                  
                } else {
                    std::cout << "Invalid grimoire verse: logical contradiction at the verse's line num " <<  line_num << endl;
                    std::cout << "Rational: "<< greater_than_key[i] << " cannot be bother greater and less than " << key << endl;
                    auto stop = high_resolution_clock::now();  // stop clock()

                    auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
                    std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
                    return;
                }
            }
            // cout << key +" _____"<< endl;
            // value->gt_map.printAll();
            // cout <<"    " <<  endl;
            // value->lt_map.printAll();

            less_than_key.clear();
            greater_than_key.clear();
            line_ele = 0;   // new line 
        } else {
            line_ele++;      // iterate 
        }
    }

    if (grimoire.getSize()  != size){
        std::cout << "Invalid grimoire verse" << endl;
        std::cout << "Rational: not all " << size << " runes are contained in verse" <<  endl;
        auto stop = high_resolution_clock::now();  // stop clock()
        auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
        std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
        return;
    }

    std::cout << "Valid verse" << endl;
    auto stop = high_resolution_clock::now();  // stop clock()
    auto duration = duration_cast<microseconds>(stop - start);  // calc execution timed
    std::cout << "Run time: " <<  duration.count() << " ms " << endl; 
    std::cout << "Printing verse:" << endl;
    
    // print verse 
    for (int i =0; i<verses.size(); i++){
        if (i % 5 ==0 && i !=0 ) // if new line, print \n 
            std::cout << "\n";
        std::cout << verses[i] + " ";
    }
    std::cout << " "<< endl;
    std::cout << "." << endl;
    std::cout << "." << endl;

    process_input(verse_num);

    return;
}

// used to return a vector of all the elements in a string array 
vector<string> process_str (string str){
    
    vector<string> strings;

    if (str.length() ==2) return strings;
    else if (str.length() ==3){
        string s = "";
        s += str[1];
        strings.push_back(s);
        return strings;
    }

    int size = (str.length() -2) - (str.length() -2) /2;
    
    string s ="";
    for (int i=1; i<str.length()-1; i++){
        if (str[i] == ','){  // comma used as a delimeter
            strings.push_back(s);
            s = "";
        } else {
            s += str[i];
        }
    }
    strings.push_back(s);
    return strings;  // return vector
}