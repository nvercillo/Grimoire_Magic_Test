#include "dependencies.h"
#include "Grimoire.h"

int main(){

    srand(time(0));     // Use current time as seed for randomly generated numbers
    HashTable<MapEntry*> map;
    
    ofstream myfile;
    myfile.open ("test.in");

    int num_verses = rand() % 5 +1;
    myfile << num_verses << "\n";


    for (int iter =0;iter <num_verses; iter++){

        int num_runes = rand() % 100 +2;
        int num_lines = rand() % num_runes +1;
        
        myfile << "Num_runes: " << num_runes <<  "\n";

        for (int i =0; i<num_runes; i++){
            string value ="";
            int j =i;
            value += (char)(i %26 +65);
            j = i- (i %26);
            
            for (int w =0; w < j /26; w ++){
                value +='Z';
            }
            // cout << value << endl;
            map.put(new MapEntry(to_string(i), value));
        }
           
        for (int i =0; i<num_lines; i++){
            string line = "[";
            int square = sqrt(num_runes);
            int v1 = rand()% square;
            int v2 = rand()% square;



            HashTable<string*> set; 
            set.put(&(map.get(to_string(i))->value));
            bool first = true;
            for (int j =0; j<v1; j++){
                string key = to_string(rand() % num_runes);
                
                if  (set.get(map.get(key)->value) != nullptr){
                    continue;
                }

                if (first){
                    line += map.get(key)->value;
                    first = false; 
                } else {
                    line += "," + map.get(key)->value;
                }
                set.put(&(map.get(key)->value));
            }
        
            line += "] < " + map.get(to_string(i))->value + " < [";

            first = true;
            for (int j =0; j<v2; j++){
                string key = to_string(rand() % num_runes);
                
                if  (set.get(map.get(key)->value) != 0)
                    continue;

                if( first){
                    line += map.get(key)->value;
                    first = false;
                } else {
                    line += "," + map.get(key)->value;
                }
            }
            line += "]";
            myfile << line +"\n";
        }

    }
    myfile.close();
    
    return 0;
}

