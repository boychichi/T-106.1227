#include <iostream>
#include <ext/hash_set>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;
using namespace __gnu_cxx;

const unsigned int MIN_BUCKET_SIZE = 3000000;
const unsigned int TOT_NUM_ELE_TO_SEARCH = 10000;

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

bool lookup(const hash_multiset<const char*, hash<const char*>, eqstr>& MultiSet,
            const char* word)
{
  hash_multiset<const char*, hash<const char*>, eqstr>::const_iterator it
    = MultiSet.find(word);
  /*int n_found = MultiSet.count(word);
  cout << word << ": "
       << n_found << " "
       << (n_found == 1 ? "instance" : "instances")
       << endl;*/
  return (it != MultiSet.end() ? true : false);
}
	
int main(void)
{
  
  std::ifstream myfile("worldcities.txt");
  std::string data = "aixirivali";
  hash_multiset<const char*, hash<const char*>, eqstr> MultiSet(MIN_BUCKET_SIZE);

  int i = 0;
  int count = 0;
  char * cstr;
  char ** lookup_test;
  
  lookup_test = new char* [TOT_NUM_ELE_TO_SEARCH];
  while(!myfile.eof()) 
  {
	getline(myfile, data);
	cstr = new char [data.size()+1];

	if( i % 100 == 0 && count < TOT_NUM_ELE_TO_SEARCH )
	{
		
		lookup_test[count] = new char [data.size()+1];
		strcpy (lookup_test[count], data.c_str());
		//cout<<"For lookup: "<<lookup_test[count];
		count++;
	}
	strcpy (cstr, data.c_str());
	MultiSet.insert(cstr);
	i++;
  }
  
  cout<<"Hash bucket size: "<<MultiSet.bucket_count()<<endl;
  cout<<"Hash set size: "<<MultiSet.size()<<endl;
  cout<<"Hash max size: "<<MultiSet.max_size()<<endl;
  
  
  // look up exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 assert(lookup(MultiSet, lookup_test[j]));
  
  // delete exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 MultiSet.erase(lookup_test[j]);
  
  // look up exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 assert(!lookup(MultiSet, lookup_test[j]));
  /*
  char * temp;
  // non existing records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
  {
     temp = new char [10];
	 sprintf( temp, "%d", j );
	 lookup(MultiSet, temp);
  } */

  return 0;
}
