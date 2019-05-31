#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <stdio.h>
#include <initializer_list>
#include <iomanip>
#include <list>
#include <fstream>
#include <string.h>
#include <typeinfo>

using namespace std;

/* Build a dictionary with the words in the text as keys, and a reference to a vector in a vector, with the IDs as values.*/
	
class dictionary{
    public:
    int a = 0;
    vector<vector<string> > titles;
    map<string,int> dict;

		
    void insert(string word, string id){ //If switch id for titles, the search is a bit faster.
        if (dict.find(word)==dict.end()){ //the word is not in the dictionary
        	dict[word] = a; // referência 
        	titles.push_back({id}) ;// create a vector in a vector and append the related id.
        	a = a+1;
        }else{
        	titles[dict[word]].push_back(id);
		}
    }
    
    void insertlist(string word,vector<string> ids){ // Insert a vector with the ids of a word in the dataset
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
	ifstream arq;
	string data;
	arq.open("textsave.txt");
	string line;
	string word;
	
	while(getline(arq,line)){
		data=line.c_str();
		int index=0;
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = data.find(delimiter)) != std::string::npos) {
    		token = data.substr(0, pos);
    	//	std::cout << token << std::endl;
    		if (index==0){
    			word=token;
    			index=index+1;
			}else{
				//cout<<word<<token<<endl;
				our_dict.insert(word,token);
				index=index+1;
				//our_dict.print(word);
			}
    		data.erase(0, pos + delimiter.length());
		};
		our_dict.print(word);
	};
	
}



