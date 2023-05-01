#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <stdlib.h>

using namespace std;

class triplet
{
	public:
		bool free;
		vector<int> prefList;
		int proposeTo;
};

class Fridgemadness
{
	public:
		Fridgemadness(int n1, int n2) {numOfEng = n1; numOfDrink = n2; totalEngaged =0;};
		void addEngineers(int id, vector<int> & preference);
		void setPrefList();
		void dumpPairVec(vector<pair<int, int> > pv);
		int obtainDesire(vector<int> v1, vector<int> v2);

		//void merge(vector<pair<int, int> > left, vector<pair<int, int> > right, vector<pair<int, int> > & result);
		//void mergesort(vector<pair<int, int> > input, vector<pair<int, int> > & output);
		void mergeSort(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int array_size);
		void m_sort(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int left, int right);
		void merge(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int left, int mid, int right);
	
		void startStableMatch();
		void printEngageSet();

	private:
		map<int, vector<int> > mapping;
		set<pair<int, int>  > rsltEngMap;
		int numOfEng;
		int numOfDrink;
		vector<triplet> upper;//man
		vector<triplet> lower;//woman
		int * engageSet;
		int totalEngaged;
		
};
