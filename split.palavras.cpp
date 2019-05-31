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
#include <string.h>
#include <typeinfo>

using namespace std;

int main(){
	
	ifstream arq;
	arq.open("text.txt");
	string line;
	string data;
	while(getline(arq,line)){
		data=line.c_str();
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = data.find(delimiter)) != std::string::npos) {
    		token = data.substr(0, pos);
    		std::cout << token << std::endl;
    		data.erase(0, pos + delimiter.length());
		};
		std::cout <<typeid(data).name()<< data << endl;
	};
		
};
