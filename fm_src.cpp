#include "fm_src.h"


int Fridgemadness::obtainDesire(vector<int> v1, vector<int> v2)//double-check!!
{
	int score, j, sum=0;
	int length1=v1.size();
	for (score=length1; score>0;score--)
	{
		bool flag = 0;//detect if the drink appears sooner in A's list or does not appear at all in B's list
		for(j=0; j<v2.size(); j++)
			if(v1[length1-score]==v2[j])
			{
				flag=1;
				break;
			}
		if(flag==0)
			sum+=score;
	        else
		for (j=0; j<v2.size();j++)
		{
			if((v1[length1-score] == v2[j]) && (length1-score<j))//score+index=length1
			sum+=score;
			else if((v1[length1-score] == v2[j]) && (length1-score==j) )
			sum+=score*score;
		}

	}
	return sum;
}

void Fridgemadness::dumpPairVec(vector<pair<int, int> > pv)
{
	vector<pair<int, int> >::iterator it=pv.begin();
	for(; it!= pv.end(); it++)
		cout<<it->first<<" "<<it->second<<endl;

}


void Fridgemadness::addEngineers(int id, vector<int> & preference)
{
	mapping.insert(pair<int, vector<int> >(id, preference));	

}


void Fridgemadness::mergeSort(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int array_size)
{
	//temp = pv;
	m_sort(pv, temp, 0, array_size-1);
}

void Fridgemadness::m_sort(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int left, int right)
{
  int mid;
  if (right > left)
  {
    mid = (right + left) / 2;
    m_sort(pv, temp, left, mid);
    m_sort(pv, temp, (mid+1), right);
    merge(pv, temp, left, (mid+1), right);
  }

}

void Fridgemadness::merge(vector<pair<int, int> > & pv, vector<pair<int, int> > & temp, int left, int mid, int right)
{
  int i, left_end, num_elements, tmp_pos;
  left_end = (mid - 1);
  tmp_pos = left;
  num_elements = (right - left + 1);

  while ((left <= left_end) && (mid <= right))
  {
     if (pv[left].second > pv[mid].second || (pv[left].second==pv[mid].second && pv[left].first>pv[mid].first))
     {
       temp[tmp_pos] = pv[left];
       tmp_pos += 1;
       left += 1;
     }
     else if (pv[left].second < pv[mid].second || (pv[left].second==pv[mid].second && pv[left].first<pv[mid].first))
     {
      temp[tmp_pos] = pv[mid];//cao
      tmp_pos += 1;
      mid += 1;
     } 
  }
 
 
 
  while (left <= left_end)
  {
    temp[tmp_pos] = pv[left];
    left += 1;
    tmp_pos += 1;
  }
 
  while (mid <= right)
  {
    temp[tmp_pos] = pv[mid];
    mid += 1;
    tmp_pos += 1;
  }
 
  for (i=0; i < num_elements; i++)
  {
    pv[right] = temp[right];
    right -= 1;
  }

}

void Fridgemadness::setPrefList()
{
	vector<pair<int, int> > pairVec;
	int jj;

	for (int i=0; i< numOfEng/2; i++)
	{
		vector<int> tempPrefList;
		for (int j=numOfEng/2; j<numOfEng; j++)
		{
			int tempScore = obtainDesire(mapping[i], mapping[j]); 
			pairVec.push_back(pair<int, int>(j, tempScore));
			
		}
		//start MSort
		vector<pair<int, int> > temp;
		//mergesort(pairVec, temp);
		temp = pairVec;
		mergeSort(pairVec, temp, numOfEng/2);
		pairVec = temp;
		//end of merge sort...
		//rsltEngMap.insert(pair<int, vector<int> >(i, pairVec) );
		triplet tr;
		tr.free=1;
		for(jj=0; jj<pairVec.size(); jj++)
			tr.prefList.push_back(pairVec[jj].first);
		tr.proposeTo=0;
		upper.push_back(tr);

		pairVec.clear();
	}
	//symetrically......
	
	for (int i=numOfEng/2; i< numOfEng; i++)//lower 50% get preflist
	{
		vector<int> tempPrefList;
		for (int j=0; j<numOfEng/2; j++)
		{
			int tempScore = obtainDesire(mapping[i], mapping[j]); 
			pairVec.push_back(pair<int, int>(j, tempScore));
			
		}
		//start MSort
		vector<pair<int, int> > temp;
		//mergesort(pairVec, temp);
		temp = pairVec;
		mergeSort(pairVec, temp, numOfEng/2);
		pairVec = temp;
		//end of merge sort...
		triplet tr;
		tr.free=1;
		for(jj=0; jj<pairVec.size(); jj++)
			tr.prefList.push_back(pairVec[jj].first);

		tr.proposeTo=0;
		lower.push_back(tr);
	//	dumpPairVec(pairVec);
		pairVec.clear();
	}
	//preference list obtained......
	
}


void Fridgemadness::startStableMatch()
{	
	int i,j,k,l,temp,temp1=0,cnt=0;
	engageSet=(int *)malloc(sizeof(int)*numOfEng*numOfEng/4);
	int fan = numOfEng/2;
/*	cout<<upper[0].free<<endl;
	cout<<"upper #: "<<upper.size()<<"lower #: "<<lower.size()<<endl;*/
	while (1) 
	{
		for (i=0; i<numOfEng/2; i++) 
		{
			if (upper[i].free == 1) 
				{ // A man is free to propose in decreasing order of preference

				if (lower[upper[i].prefList[upper[i].proposeTo]-fan].free == 1) 
				{ //If Women is free, engage the Man/Women
					*(engageSet+totalEngaged*numOfEng/2) = i;
					*(engageSet+totalEngaged*numOfEng/2+1) = upper[i].prefList[upper[i].proposeTo];
					totalEngaged++;
					lower[upper[i].prefList[upper[i].proposeTo]-fan].free = 0; //Women is not free anymore
					upper[i].free = 0;
					upper[i].proposeTo++;
				}
				else {
					for (j=0; j<numOfEng/2; j++) 
					if ( i == lower[upper[i].prefList[upper[i].proposeTo]-fan].prefList[j] ) break;
					
					for (k=0; k<totalEngaged; k++) 
					{
						if ( *(engageSet+k*fan+1) == upper[i].prefList[upper[i].proposeTo] ) 
						{
						for (l=0; l<numOfEng/2; l++) 
						{
							if (*(engageSet+k*fan) == lower[upper[i].prefList[upper[i].proposeTo]-fan].prefList[l]) 
							{
							if ( j < l ) 
							{
							temp = *(engageSet+k*fan);
							*(engageSet+k*fan) = i; // Women is engaged to the man that just proposed
							upper[temp].free = 1; // Free the previously engaged man of W
							upper[i].free = 0;
							upper[i].proposeTo++;
							}	
							else {
							upper[i].free = 1; // Else the Women rejects the man's proposal.. free the man
							upper[i].proposeTo++;
							}
							break;
							}
						}
						break;
					}
					}
				}
			}
		}
		
	        int jj;
		for (temp1=0; temp1<numOfEng/2; temp1++) 
			if (upper[temp1].free == 0) cnt++;
		if (cnt == numOfEng/2) break; // No men is free, the algorithm terminates here.
		cnt = 0;
		}
}

void Fridgemadness::printEngageSet()
{
	int i;
	for (i=0; i<totalEngaged; i++)
//	cout<<*(engageSet+numOfEng/2*i)<<" "<<*(engageSet+numOfEng/2*i+1)<<endl;
	rsltEngMap.insert(pair<int, int>(*(engageSet+numOfEng/2*i), *(engageSet+numOfEng/2*i+1)) );

	set<pair<int, int> >::iterator it=rsltEngMap.begin();
	for(;it!=rsltEngMap.end(); ++it)
		cout<<it->first<<" "<<it->second<<endl;
}
