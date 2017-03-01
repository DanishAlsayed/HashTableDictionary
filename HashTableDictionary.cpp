#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

struct node {
	string k;
	int i;
	node * next;
};
int const m=4603;
node *hashT[m];
string dict [7000][2];
string mTable [7000];
int hFunction (string);
void readDataset();
void fill(node*&, string, int);
void hashTinitialize();
void handleCommand(string, string);
string searchHash(string);
string searchNodes(node *&, string);
string insert(string,string);
string remove1(string);
void deleteNode(node*&, string);
void status();
void displayNodes(node*, ofstream&);
void displayHash();
double statusS();
double statusF();
int c=1;
int d=1;
double sumS=0;
bool check=false;
int main(int argc, char* argv []){
	hashTinitialize();
	readDataset();
	for(int i=0;i<7000;i++){
		if(dict[i][0]=="" || dict[i][1]=="")
			break;
		fill(hashT[hFunction(dict[i][0])], dict[i][0], i);
	}
	handleCommand(argv[1], argv[2]);
	return 0;
}
int hFunction(string latin){
	int y=(int)latin[0];
	int value=(y%m);
	for (int i=1;i<latin.length();i++){
		int b=(int)latin[i];
		if(i!=latin.length()){
			value=((value*128)+b)%m;
		}
		else if (i==latin.length())
			value=value%m;
	}
	return value;
}
void readDataset(){
	for(int i=0;i<7000;i++)
		for(int j=0;j<2;j++)
			dict[i][j]="";
	string latin, meaning;
	ifstream file;
	file.open("dict.txt");
	int x=0;
	while (!file.eof()){
		getline(file,latin,'\t');
		getline(file,meaning);
		dict[x][0]=latin;
		dict[x][1]=meaning;
		if (!(latin=="" || meaning==""))
			mTable[x]=meaning;
		x++;
	}
	
}
void hashTinitialize(){
	for (int i=0;i<m;i++)
		hashT[i]=NULL;
	}
void fill (node *& n, string word, int i){
	
	if(n==NULL){
		n=new node;
		n->k=word;
		n->i=i;
		n->next=NULL;
	}
	else{
		fill(n->next, word, i);
	}

}
void handleCommand(string input, string output){
	ifstream fin;
	ofstream fout;
	fout.open(output.c_str());
	fin.open(input.c_str());
	string command="";
	string word="";
	string meaning="";
	string line="";
	while(!fin.eof()){
		command="";
		word="";
		meaning="";
		getline(fin,line);
		if (line.length()==6)
			command=line;
		else if (line.length() > 6){
		command=line.substr(0,6);
		line=line.substr(7,(line.length()-7));
		}
		if (command=="insert"){
			for(int i=0;i<line.length();i++)
			{
				if (line[i]==' '){
					word=line.substr(0,i);
					meaning=line.substr(i+1,(line.length()-(i+1)));
					fout<<insert(word, meaning)<<endl;
					break;
				}
			}
		}
		 if (command== "remove"){
			word=line;
			fout<<remove1(word)<<endl;
		}
		 if (command=="lookup"){
			word=line;
			fout<<searchHash(word)<<endl;
		}
		if (command=="status"){
				fout<<"status "<<statusS()<<" "<<statusF()<<endl;
		}
	}
	fin.close();fout.close();
}
string searchHash(string word){
	int index=hFunction(word);
	return word+":"+searchNodes(hashT[index],word);
}
string searchNodes(node *& n, string word){
	string result="";
	if (n!=NULL){
		if (check==true)
			sumS+=1;
		if(n->k==word){
			return mTable[n->i];
			
		}
		else{
			return searchNodes(n->next,word);
			
		}
	}
			return "lookup failed";
}
void displayNodes(node* h, ofstream& fout){
	
	if(h!=NULL){
		fout<<h->k<<"'s meaning index "<<h->i<<" "<<mTable[h->i]<<d++<<endl;
		displayNodes(h->next, fout);
	}
}
void displayHash(){
	ofstream fout;
	fout.open("out1.txt");
	for (int i=0; i<m;i++){
		if(hashT[i]!=NULL)
			displayNodes(hashT[i],fout);
	}
	fout.close();
}
string insert(string latin,string meaning){
if(searchHash(latin)==latin+":lookup failed"){
		int index=hFunction(latin);
		int i=0;
		for (int x=0; x<sizeof(mTable); x++){
		if (mTable[x]==""){
			i=x;
			break;
			}
		}
		mTable[i]=meaning;
		dict[i][0]=latin;
		dict[i][1]=meaning;
		fill (hashT[index],latin,i);
		return latin+":insert success";
}
else
	return latin+":insert failed";

}
string remove1(string word){
	int index=hFunction(word);
	string search=searchHash(word);
	if(search==(word+":lookup failed"))
		return word+":remove failed";
	else{
		deleteNode(hashT[index], word);
		return word+":remove success";
	}
}
void deleteNode(node*& n, string word){
	if (n!=NULL){
		if (n->k==word){
			node*temp;
			temp=n;
			n=n->next;
			mTable[temp->i]="";
			dict[temp->i][0]="";
			dict[temp->i][1]="";
			delete temp;
		}
		else
			deleteNode (n->next,word);
	}
}
double statusS(){
	check=true;
	double totalWords=0;
	double sum=0;
	for(int i=0;i<7000;i++)
	{
		if (dict[i][0]!=""){
		searchHash(dict[i][0]);
		totalWords++;
		}
	}
	sum=sumS;
	sumS=0;
	check=false;
	return (sum)/totalWords;
}
double statusF(){
	double sum=0;
	node *temp;
	for (int i=0; i<m;i++){
		if (hashT[i]!=NULL){
			temp=hashT[i];
			double i=1;
			while(temp->next!=NULL){
				temp=temp->next;
				i+=1;
			}
			sum+=i;
		}
	}
	return ((double)(sum)/m);
}