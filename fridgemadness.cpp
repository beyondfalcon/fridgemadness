#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <map>
#include "fm_src.h"

using namespace std;

void parseVector(string str, vector<int> & vec)
{
	size_t pos, pos1;
	pos =0;
	pos1=0;

	while(pos1!=string::npos)
	{
		pos1=str.find_first_of(",", pos);
		//if(pos1==string::npos) break;
		string sub = str.substr(pos, pos1-pos);
		vec.push_back(atoi(sub.c_str()));
		pos=pos1+1;
	}	

}

void dumpVector(vector<int> vec)
{
	vector<int>::iterator it=vec.begin();
	for(; it!= vec.end(); it++)
		cout<<*it<<" ";
	cout<<endl;
}

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		cout<<"usage: "<<argv[0]<<" "<<"<input file name>"<<endl;
		exit(0);
	}

	char burbust[256];
	memset(burbust, 0x0, 256);
	string pref;
	int n1, n2, i,j, id;
	ifstream fin;
	fin.open(argv[1]);
	if(!fin) 
	{
		cout<<"failed to open input file!!!"<<endl;
		exit(0);
	}	
	
	fin>>n1>>n2;
	//cout<<"n1:"<<n1<<"   n2:"<<n2<<endl;
	Fridgemadness* fm = new Fridgemadness(n1, n2);

	for(i=0;i<=n2;i++){
		fin.getline(burbust, 256);

        }

	while(true)
	{
		vector<int> temp;
		fin>>id>>pref;
		if(fin.eof()) break;
		parseVector(pref, temp);
		fm->addEngineers(id, temp);
	}
	
	fin.close();
	fm->setPrefList();
	fm->startStableMatch();
	fm->printEngageSet();
        delete fm;
}
