#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <stdio.h>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>

using namespace std;

/* Build a dictionary with the words in the text as keys, and a reference to a vector in a vector, with the IDs as values.*/
	
class dictionary{
    public:
    int a = 0;
    vector<vector<int> > titles;
    map<string,int> dict;

		
    void insert(string word, int id){ //If switch id for titles, the search is a bit faster.
        if (dict.find(word)==dict.end()){ //the word is not in the dictionary
        	dict[word] = a; // referência 
        	titles.push_back({id}) ;// create a vector in a vector and append the related id.
        	a = a+1;
        }else{
        	titles[dict[word]].push_back(id);
		}
    }
    
    void insertlist(string word,vector<int> ids){ // Insert a vector with the ids of a word in the dataset
    	for (int j=0;j<ids.size();j++) {
		insert(word,ids[j]); //add every id of the vector using insert function
		}
	};
	void print(string word){
		for(int k=0;k<titles[dict[word]].size();k++){
			cout<< titles[dict[word]][k]<<endl;
		}
	}
};

int main(){   
	dictionary our_dict;
	our_dict.insertlist("happy",{6,4,5});
	our_dict.print("happy");
	
	char data[80];
	ifstream arq;
	arq.open("textsave.txt");
	if (arq.is_open() && arq.good()){
		arq>> data;
		while(!arq.fail()){
			arq>>data;
			cout<<data;
		}
		arq.close();
	}
	return 0;
}



