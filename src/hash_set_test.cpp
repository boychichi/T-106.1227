#include <iostream>
#include <ext/hash_set>
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

void lookup(const hash_set<const char*, hash<const char*>, eqstr>& Set,
            const char* word)
{
  hash_set<const char*, hash<const char*>, eqstr>::const_iterator it
    = Set.find(word);
  cout << word << ": "
       << (it != Set.end() ? "present" : "not present")
       << endl;
}
	
int main(void)
{
  std::ifstream myfile("worldcities.txt");
  std::string data = "aixirivali";
  hash_set<const char*, hash<const char*>, eqstr> Set(10000);

  int i = 0;
  int count = 0;
  char * cstr;
  char ** lookup_test;
   
  lookup_test = new char* [100];

  while(!myfile.eof()) 
  {
	getline(myfile, data);
	cstr = new char [data.size()+1];

	if( i % 1000 == 0 && count < 100 )
	{
		
		lookup_test[count] = new char [data.size()+1];
		strcpy (lookup_test[count], data.c_str());
		//cout<<"For lookup: "<<lookup_test[count];
		count++;
	}
	strcpy (cstr, data.c_str());
	Set.insert(cstr);
	i++;
  }
  cout<<"Hash bucket size: "<<Set.bucket_count()<<endl;
  cout<<"Hash set size: "<<Set.size()<<endl;
  cout<<"Hash max size: "<<Set.max_size()<<endl;
  /*
  for( hash_set<const char*, hash<const char*>, eqstr>::const_iterator it = Set.begin(); it != Set.end(); it++)
	{
		if( Set.count(*it) > 1) cout<<"Total elements which have the same hash as " <<*it<<": "<<Set.count(*it)<<endl;
	}
  */
  
  // look up exisiting records
  for( int j = 0; j < 100; j++ )
	 lookup(Set, lookup_test[j]);
  
  // delete exisiting records
  for( int j = 0; j < 100; j++ )
	 Set.erase(lookup_test[j]);
  
  // look up non-exisiting records
  for( int j = 0; j < 100; j++ )
	 lookup(Set, lookup_test[j]);
	 

  return 0;
}
