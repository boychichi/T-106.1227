#include <iostream>
#include <ext/hash_map>
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

bool lookup(const hash_multimap<const char*, const char*, hash<const char*>, eqstr>& MultiMap,
            const char* word)
{
  /*
  cout << word << ": ";
  pair<hash_multimap<const char*, const char*, hash<const char*>, eqstr>::const_iterator, hash_multimap<const char*, const char*, hash<const char*>, eqstr>::const_iterator> p =
    MultiMap.equal_range(word);
  for (hash_multimap<const char*, const char*, hash<const char*>, eqstr>::const_iterator i = p.first; i != p.second; ++i)
    cout << (*i).second << " ";
  cout << endl;
  */
  
  hash_multimap<const char*, const char*, hash<const char*>, eqstr>::const_iterator it
    = MultiMap.find(word);
  /*cout << word << ": "
       << (it != MultiMap.end() ? "present" : "not present")
       << endl;
	   */
	return (it != MultiMap.end() ? true : false);  
}
	
int main(void)
{
  std::ifstream myfile("worldcities_detailed.txt");
  std::string data = "aixirivali";
  hash_multimap<const char*, const char *, hash<const char*>, eqstr> MultiMap(MIN_BUCKET_SIZE);

  int i = 0;
  int count = 0;
  char * key;
  char * value;
  char ** lookup_test;
   
  lookup_test = new char* [TOT_NUM_ELE_TO_SEARCH];

  while(!myfile.eof()) 
  {
	getline(myfile, data, ',');
	key = new char [data.size()+1];
	
	if( i % 100 == 0 && count < TOT_NUM_ELE_TO_SEARCH )
	{		
		lookup_test[count] = new char [data.size()+1];
		strcpy (lookup_test[count], data.c_str());
		//cout<<"For lookup: "<<lookup_test[count];
		count++;
	}
	strcpy (key, data.c_str());
	getline(myfile, data);
	value = new char [data.size()+1];
	strcpy (value, data.c_str());
	//cout<<"Key: "<<key<<" Value: "<<value<<endl;
	MultiMap.insert(hash_multimap<const char*, const char*, hash<const char*>, eqstr>::value_type(key, value));
	i++;
  }
  
  cout<<"Hash bucket size: "<<MultiMap.bucket_count()<<endl;
  cout<<"Hash MultiMap size: "<<MultiMap.size()<<endl;
  cout<<"Hash max size: "<<MultiMap.max_size()<<endl;
    
  // look up exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 assert(lookup(MultiMap, lookup_test[j]));
  
  // delete exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 MultiMap.erase(lookup_test[j]);
  
  // look up non-exisiting records
  for( int j = 0; j < TOT_NUM_ELE_TO_SEARCH; j++ )
	 assert(!lookup(MultiMap, lookup_test[j]));
  return 0;
}
