#include <iostream>
#include <ext/hash_map>
#include <stdlib.h>
#include <fstream>
#include <string>


using namespace std;
using namespace __gnu_cxx;

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

void lookup(const hash_map<const char*, const char*, hash<const char*>, eqstr>& Map,
            const char* word)
{
  hash_map<const char*, const char*, hash<const char*>, eqstr>::const_iterator it
    = Map.find(word);
  cout << word << ": "
       << (it != Map.end() ? "present" : "not present")
       << endl;
	  
}
	
int main(void)
{
  std::ifstream myfile("worldcities_detailed.txt");
  std::string data = "aixirivali";
  hash_map<const char*, const char *, hash<const char*>, eqstr> Map(10000);

  int i = 0;
  int count = 0;
  char * key;
  char * value;
  char ** lookup_test;
   
  lookup_test = new char* [100];

  while(!myfile.eof()) 
  {
	getline(myfile, data, ',');
	key = new char [data.size()+1];
	
	if( i % 1000 == 0 && count < 100 )
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
	Map[key] = value;
	i++;
  }
  
  cout<<"Hash bucket size: "<<Map.bucket_count()<<endl;
  cout<<"Hash Map size: "<<Map.size()<<endl;
  cout<<"Hash max size: "<<Map.max_size()<<endl;
  /*
  for( hash_map<const char*, hash<const char*>, eqstr>::const_iterator it = Map.begin(); it != Map.end(); it++)
	{
		if( Map.count(*it) > 1) cout<<"Total elements which have the same hash as " <<*it<<": "<<Map.count(*it)<<endl;
	}
  */
  
  // look up exisiting records
  for( int j = 0; j < 100; j++ )
	 lookup(Map, lookup_test[j]);
  
  // delete exisiting records
  for( int j = 0; j < 100; j++ )
	 Map.erase(lookup_test[j]);
  
  // look up non-exisiting records
  for( int j = 0; j < 100; j++ )
	 lookup(Map, lookup_test[j]);
	 

  return 0;
}
