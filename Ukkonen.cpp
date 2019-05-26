#include <iostream>
#include <string>

using namespace std;

struct Node{
	
	//cada nó aponta para outros 128 nós ( Ascii)
	Node *pchildreen[128];
	
	// valor do nó (128 para verificação e inserção de letras)
	string suffix_edge[128];
	
	//uma vez que os edges_node são vazios, acrescentamos o símbolo 'string vazia' 
	// e para o pnext, colocamos o nullptr (null para ponteiros)
	// usando 'member function', que vai modificar o próprio nó:
	Node (){
		for (t=1; t<128; t++){
			*pchildreen[t] = nullptr 
			suffix_edge[t] = "" //por ser mais de uma letra é necessário aspas duplas.
		}
	}
}; 

class Suffix_tree{
	private:
		
	void insert(palavra,id){
		if ()	
		
	}
};
