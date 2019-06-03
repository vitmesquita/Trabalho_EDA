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
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;

/* Build a dictionary with the words in the text as keys, and a reference to a vector in a vector, with the IDs as values.*/
	
class dictionary{
    public:
    int a = 0;
    vector<vector<string> > titles;
    map<string,int> dict;
    map<string,string> title_by_id;

		
    void insert(string word, string id){ //If switch id for titles, the search is a bit faster.
        if (dict.find(word)==dict.end()){ //the word is not in the dictionary
        	dict[word] = a; // referência 
        	titles.push_back({id}) ;// create a vector in a vector and append the related id.
        	a = a+1;
        }else{
        	titles[dict[word]].push_back(id);
		}
    }
   void singleones(vector<string> name) { 
		sort(name.begin(),name.end()); //Use the start and end like this

		for (vector<string>::size_type i = 0; i != (name.size()-1); ++i)
			if (name[i]==name[i+1]) {
			cout<<name[i]<<" ";
			}
	}
    
	void search(string word){
		vector<string> answer;
		int nword=0;
		word=word+" ";
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = word.find(delimiter)) != std::string::npos) { //fazendo busca para cada palavra
				token = word.substr(0, pos); 
    			token="'"+token+"'";
    			
			if (dict.find(token)==dict.end()){
				cout<<"Not found"<<endl;
				
			}else{
    			for(int k=0;k<titles[dict[token]].size();k++){
    				
					answer.push_back({ titles[dict[token]][k] });
					nword=nword+1;
				}
			}
    		word.erase(0, pos + delimiter.length());
    	}
    	if (nword>1){
    		singleones(answer);
		}else{
			for (int l=0;l<answer.size();l++){
				cout<<answer[l]<<" ";
			}
		}
	};
	
	
	void insert_titles(){
		ifstream arq1;
		string data;
		arq1.open("title_id.txt"); 
		string line;
		string title;
		string id
		while(getline(arq1,line)){ //inserindo no dicionário de títulos
			data=line.c_str();
			int index=0;
			string delimiter = " ";
			size_t pos = 0;
			string token;
			while ((pos = data.find(delimiter)) != std::string::npos) {
    			title = data.substr(0, pos);
    			data.erase(0, pos + delimiter.length());
    			id = data;
    			title_by_id[id] = title;
    		}    			
		}
	}

	
	
	void print_titles(string word){ 
		lista_ids = titles[dict[word]]
		for (i=0, i<lista_ids.length(), i++){
			cout<<title_by_id[lista_ids[i]];
		}
	}
		
};

int main(){   
	dictionary our_dict;
	ifstream arq;
	string data;
	arq.open("thereal.txt");
	string line;
	string title;
	while(getline(arq,line)){ //inserindo no dicionario
		data=line.c_str();
		int index=0;
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = data.find(delimiter)) != std::string::npos) {
    		token = data.substr(0, pos);
    		if (index==0){
    			title=token;
    			index=index+1;
			}else{
				our_dict.insert(title,token);
				index=index+1;
			}
    		data.erase(0, pos + delimiter.length());
		};
	};
	our_dict.search("one random");	
	
	insert_titles();
	
	
}
