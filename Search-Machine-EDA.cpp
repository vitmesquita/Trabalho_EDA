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
#include <algorithm>
#include <chrono> 
#include <math.h>
#include <set>
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;
using namespace std::chrono;

//classe de serializa��o

template<class Key, class Value>
class serializable_map : public map<Key, Value> {
private:
  size_t offset;

  template<class T>
  void write(stringstream &ss, T &t) {
    ss.write((char*)(&t), sizeof(t));
  }

  void write(stringstream &ss, string &str) {
    size_t size = str.size();
    ss.write((char*)(&size), sizeof(size));
    ss.write((char*)(str.data()), str.length());
  }
  
  template<class T>
  void read(vector<char> &buffer, T &t) {
    t = (T)(*(buffer.data() + offset));
    offset += sizeof(T);
  }

  void read(vector<char> &buffer, string &str) {
	int size = 0;
  	char startchar1 = buffer[offset];
  	char startchar2 = buffer[offset+1];
  	while ((isspace(startchar1)) || (isspace(startchar2))){
  		offset = offset + 1;
  		startchar1 = buffer[offset];
  		startchar2 = buffer[offset+1];
	}
	offset=offset+1;
  	char endchar1 = buffer[offset+size];
  	char endchar2 = buffer[offset+size+1];
  	while (!(isspace(endchar1)) || !(isspace(endchar2))){
		size = size + 1;
  		endchar1 = buffer[offset+size];
  		endchar2 = buffer[offset+size+1];
	}
    string str2(buffer.data() + offset, buffer.data() + offset + size);
    offset = offset + size + 1;
    str = str2;
  }
public:
  vector<char> serialize() {
    vector<char> buffer;
    stringstream ss;
    for (auto &i : (*this)) {
      Key str = i.first;
      Value value = i.second;
      string v2 = to_string(value);
      for (int l=0;l<str.size();l++){
          write(ss, str[l]);
      }
      write(ss,"  ");
      
      for (int j=0;j<v2.size();j++){
          write(ss, v2[j]);
      }
      write(ss,"  ");
    }
    size_t size = ss.str().size();
    buffer.resize(size);
    ss.read(buffer.data(), size);
    return buffer;
  }
  void deserialize_titles(vector<char> &buffer) {
    offset = 0; // Hot start
    while (offset < buffer.size()-5) {
      Key key;
      Value value;
	  read(buffer, key);
      read(buffer, value);
      (*this)[key] = value;
  //cout<<"key:*"<<key<<"*value:*"<<value<<"*offset: "<<offset<<endl;
    }
  }
  void show(void) {
    for (auto &i : (*this)) {
      cout <<"*"<< i.first << "*" << i.second << "*"<<endl;
    }
    cout << endl;
  }

 void deserialize_dict(vector<char> &buffer) {
    offset = 0; // Hot start
    while (offset < buffer.size()-18) {
      Key key;
      Value value;
	  read(buffer, key);
      read(buffer, value);
      (*this)[key] = value;
  //cout<<"key:*"<<key<<"*value:*"<<value<<"*offset: "<<offset<<endl;
    }
  }
};




// construindo o dicionario
	
class dictionary{
    public:
    	
    int a = 0;
    vector<string> titles;
    serializable_map<string,string> dict;
    serializable_map<string,string> title_by_id;
		
  /*  void insert(string word, string id){ //If switch id for titles, the search is a bit faster.
        if (dict.find(word)==dict.end()){ //the word is not in the dictionary
        	dict[word] = a; // refer�ncia 
        	titles.push_back({id}) ;// create a vector in a vector and append the related id.
        	a = a+1;
        }else{
        	titles[dict[word]].push_back(id);
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

	vector<string> list_id(string str){
    string delimiter=" ";
    string token;
    vector<string> v2;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
    		token = str.substr(0, pos);
    		v2.push_back(token);
    		str.erase(0, pos + delimiter.length());
		}
        return v2;
} 
	
	string search_key(string title){
		string key;
		for (auto &i : title_by_id) {
      		if (i.second == title) {
         		key = i.first;
         		return key;
      		}
   		}
	}
	void abre_busca(){
		string busca;
 	  	cout <<"Digite uma busca: ";
    	getline(cin >> ws,busca);
			transform(busca.begin(),busca.end(),busca.begin(),::tolower);
    	search(busca);
	}
	
/*	void insert_titles(){
		ifstream arq1;
		string data;
		arq1.open("titles_ids.txt"); 
		string line;
		string title;
		string id;
		while(getline(arq1,line)){ //inserindo no dicion�rio de t�tulos
			data=line.c_str();
			int index=0;
			string delimiter = " ";
			size_t pos = 0;
			string token;
			pos = data.find(delimiter);
			id = data.substr(0, pos);
    		data.erase(0, pos + delimiter.length());
    		title = data;
    		title_by_id[id] = title;
			}   			
	}*/

	
	
void print_titles(vector<string> lista_ids){
		int ndocuments = 0; 
		vector<string> titles_mixed;
		for (int i=0; i<lista_ids.size(); i++){ // t�tulos em ordem alfab�tica
			titles_mixed.push_back(title_by_id[lista_ids[i]]);
			sort(titles_mixed.begin(),titles_mixed.end());
			
		}
		cout<<"Number of documents: "<<lista_ids.size()<<endl;
		for (int i=0; i<lista_ids.size(); i++){
			cout<<titles_mixed[i]<<endl;
			
		}
		ifstream infile1;
		string nr;
    	cout <<"Digite o numero do arquivo (0,1...) ou insira q para nova busca ";
    	cin >> nr;
    	cout <<"\nVoce digitou: "<<nr<<endl;
			if(nr=="q"){
				abre_busca();
			}else{
    		int n=stoi(nr); //n � o index da lista que mostramos
    		string find=titles_mixed[n];
    		string key=search_key(find);
				key=key.substr(1,key.size()-2);
				int index=stoi(key);
				index=index/10000;
				infile1.open("docs/doc_"+to_string(index)+"/doc_"+key);
				if(infile1.fail())
				{
						cout << "File failed to open.\n";
				}
				cout << infile1.rdbuf();
				infile1.close();
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
		vector<string> cadu;
		while ((pos = word.find(delimiter)) != string::npos) { //fazendo busca para cada palavra
				nword += 1;
				token = word.substr(0, pos); 
    			token="'"+token+"'";
			if (dict.find(token)==dict.end()){ // nao encontra nada no dicionario
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time of execution: "<<duration.count()<<" microseconds"<<  endl; 
				cout<<token<<" not found"<<endl;
				abre_busca();
				word.erase(0, pos + delimiter.length());
				
			}else{				
				word.erase(0, pos + delimiter.length());			
				if (word.size()==0 && aux==0){  //apenas 1 palavra.
										
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout <<  "Time of execution: "<<duration.count() <<" microseconds" << endl;
					int n= stoi(dict[token]);
					cadu=list_id(titles[n]);
					print_titles(cadu);
					
				}else{ //mais de 1 palavra
					aux = 1; //�ltima palavra n�o entra no if.
					if (nword==1){
						int n=stoi(dict[token]);
						cadu=list_id(titles[n]);
						word1 = cadu;
					}else{
						int n=stoi(dict[token]);
					 	cadu=list_id(titles[n]);
						word1 = intersection(word1,cadu);
					}
				}
			}
		}
		if (nword>1){			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout <<  "Time of execution: "<<duration.count() <<" microseconds" << endl;
			print_titles(word1);	
		}
		cout<<nword;
			
	}
			
	};
    	
    		


int main(){   
// declarando vari�veis //
//	string busca;
	dictionary our_dict;
	/*ifstream arq;
	string data;
	arq.open("texto_completo"); //textsave
	string line;
	string title;
	
//inserindo no dicionario//
	cout<<"Estou inserindo"<<endl;
	while(getline(arq,line)){ 
	data=line.c_str();
	int index=0;
	string delimiter = " ";
	size_t pos = 0;
	string token;
		while ((pos = data.find(delimiter)) != string::npos) {
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
	};*/
    	
    	
//tentando fazer a serializa��o funcionar
//our_dict.insert_titles();
//	our_dict.title_by_id.show();
	/*cout<<"Estou serializando"<<endl;
	vector<char> buffer=(our_dict.dict).serialize();
	
	ofstream c;
	c.open("dict.txt");
	cout<<"Serializei e estou escrevendo"<<endl;
	for (int i=0;i<buffer.size();i++){ //serializei o dict
		c<<buffer[i];
	}
	
	ofstream outfile ("titles.txt"); //serializei o vetor
	
	cout<<"Serializando o vetor de ids e escrevendo"<<endl;
    for(int j=0;j<our_dict.titles.size();j++){
    	for(int i=0;i<our_dict.titles[j].size();i++){
		
    		outfile<<our_dict.titles[j][i]<<" ";
		}
		outfile<<endl;
	};
	*/
	
	
	//deserializando dict
	ifstream a;
	vector<char> buffer1;
	char vivit;
	a.open("word_id.txt");
	while(a.get(vivit)){
		buffer1.push_back(vivit);
	}
	serializable_map<string,string> dic;
	cout<<"Deserializarando o dict"<<endl;
	dic.deserialize_dict(buffer1);
	our_dict.dict=dic;
	cout<<"Deserializei o dict"<<endl;
	
	//deserializando titulos
	ifstream b;
	vector<char> buffer2;    //funciona com offset come�ando em +5
	char vivi;
	b.open("titles_by_id.txt");
	while(b.get(vivi)){
		buffer2.push_back(vivi);
	}
	serializable_map<string,string> id;
	cout<<"Deserializando os ids"<<endl;
	id.deserialize_titles(buffer2);
	our_dict.title_by_id=id;
	cout<<"Deserializei os ids"<<endl;
//	id.show();
	
	//deserializando vetor
	ifstream c;
	string data2;
  string line2;	
	int l=0;

	vector<string>  v2;
	c.open("vector_id.txt");
	cout<<"Deserializando o vetor"<<endl;

	while(getline(c,line2)){
	    data2=line2.c_str();
        v2.push_back(data2);
	};

	our_dict.titles=v2;


//chamando a fun��o de busca//
	our_dict.abre_busca();

return 0;

}
