#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

/* Build a dictionary with the words in the text as keys, and a reference to a vector in a vector, with the IDs as values.*/
	
class dictionary{
    public:
    int a = 0;
    vector<vector<int>> titles;
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
};

int main(){   
		
	vector<string> words = {"the","a","pretty","the"};
	vector<int> ids = {12,1,45,30};
	
	dictionary our_dict;
	for (int i=0; i<words.size();i++){
		our_dict.insert(words[i],ids[i]);
	};
	
	cout<< our_dict.dict["pretty"]<<"\n";
	cout<< our_dict.titles[our_dict.dict["pretty"]][0];
	
	return 0;
}



