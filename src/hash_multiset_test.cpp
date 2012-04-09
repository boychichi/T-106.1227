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

void lookup(const hash_multiset<const char*, hash<const char*>, eqstr>& MultiSet,
            const char* word)
{
  int n_found = MultiSet.count(word);
  cout << word << ": "
       << n_found << " "
       << (n_found == 1 ? "instance" : "instances")
       << endl;
}
	
int main(void)
{
  std::ifstream myfile("worldcities.txt");
  std::string data = "aixirivali";
  hash_multiset<const char*, hash<const char*>, eqstr> MultiSet(10000);

  int i = 0;
  int count = 0;
  char * cstr;
  char ** lookup_test;
  
  lookup_test = new char* [100];
  while(!myfile.eof()) 
  {
	getline(myfile, data);
	cstr = new char [data.size()+1];

	if( i % 500 == 0 && count < 100 )
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
  /*
  for( MultiSet<const char*, hash<const char*>, eqstr>::const_iterator it = MultiSet.begin(); it != MultiSet.end(); it++)
	{
		if( MultiSet.count(*it) > 1) cout<<"Total elements which have the same hash as " <<*it<<": "<<MultiSet.count(*it)<<endl;
	}
  */
  
  // look up exisiting records
  for( int j = 0; j < 100; j++ )
	 lookup(MultiSet, lookup_test[j]);
  
  // delete exisiting records
  for( int j = 0; j < 100; j++ )
	 MultiSet.erase(lookup_test[j]);
  
  char * temp;
  // non existing records
  for( int j = 0; j < 100; j++ )
  {
     temp = new char [2];
	 sprintf( temp, "%d", j );
	 lookup(MultiSet, temp);
  } 

  return 0;
}
