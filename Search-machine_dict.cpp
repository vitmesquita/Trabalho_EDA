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
#include <chrono> 
#include <math.h>
#include <set>

using namespace std;
using namespace std::chrono;

/* Build a dictionary with the words in the text as keys, and a reference to a vector in a vector, with the IDs as values.*/
	
class dictionary{
    public:
    int a = 0;
    vector<vector<string>> titles;
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
    
   /*void singleones(vector<string> name) { 
		sort(name.begin(),name.end()); //Use the start and end like this

		for (vector<string>::size_type i = 0; i != (name.size()-1); ++i)
			if (name[i]==name[i+1]) {
			cout<<name[i]<<" ";
			}
	}*/
	
	vector<string> intersection(vector<string>& vec1, vector<string>& vec2){
		unordered_set<string> set{vec1.begin(),vec1.end()};
		vector<string> intersections;
		for(auto n:vec2){
			if (set.erase(n)>0){
				intersections.push_back(n);
			}
		}
		return intersections;
	}
	
	void insert_titles(){
		ifstream arq1;
		string data;
		arq1.open("title_id.txt"); 
		string line;
		string title;
		string id;
		while(getline(arq1,line)){ //inserindo no dicionário de títulos
			data=line.c_str();
			int index=0;
			string delimiter = " ";
			size_t pos = 0;
			string token;
			while ((pos = data.find(delimiter)) != std::string::npos) {
    			id = data.substr(0, pos);
    			data.erase(0, pos + delimiter.length());
    			title = data;
    			title_by_id[id] = title;
    		}    			
		}
	}

	
	
	void print_titles(vector<string> lista_ids){
		int ndocuments = 0; 
		vector<string> titles_mixed;
		for (int i=0; i<lista_ids.size(); i++){ // títulos em ordem alfabética
			titles_mixed.push_back(title_by_id[lista_ids[i]]);
			sort(titles_mixed.begin(),titles_mixed.end());
			
		}
		cout<<"Number of documents: "<<lista_ids.size();
		for (int i=0; i<lista_ids.size(); i++){
			cout<<titles_mixed[i]<<endl;
			
		}
	}
	
    
	void search(string word){
		auto start = high_resolution_clock::now();
		vector<string> answer;
		vector<string> word1;
		int aux = 0;
		int nword=0;
		word=word+" ";
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = word.find(delimiter)) != std::string::npos) { //fazendo busca para cada palavra
				nword += 1;
				token = word.substr(0, pos); 
    			token="'"+token+"'";
			if (dict.find(token)==dict.end()){
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<seconds>(stop - start);
				cout << "Time of execution: "<<duration.count() <<" seconds"<<  endl; 
				cout<<token<<" not found"<<endl;
				word.erase(0, pos + delimiter.length());
				
			}else{				
				word.erase(0, pos + delimiter.length());			
				if (word.size()==0 && aux==0){  //apenas 1 palavra.
										
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<seconds>(stop - start);
					cout <<  "Time of execution: "<<duration.count() <<" seconds" << endl;
									
					print_titles(titles[dict[token]]);
					
				}else{ //mais de 1 palavra
					aux = 1; //última palavra não entra no if.
					if (nword==1){
						word1 = titles[dict[token]];
					}else{
						word1 = intersection(word1,titles[dict[token]]);
					}
				}
			}
		}
		if (nword>1){			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			cout <<  "Time of execution: "<<duration.count() <<" seconds" << endl;
			print_titles(word1);	
		}
		cout<<nword;
			
	}
			
	};
    	
    		


int main(){   
	dictionary our_dict;
	ifstream arq;
	string data;
	arq.open("textsave.txt"); //textsave
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
		}
	}
	
	our_dict.insert_titles();
	our_dict.search("sea cast hospital");
	
	



}
