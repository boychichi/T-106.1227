#include <iostream>
#include <vector>
#include <ext/hash_set>
#include <stdlib.h>

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
  char * temp = new char;
  hash_set<const char*, hash<const char*>, eqstr> Set;
  
  for( int i = 0; i < 100; i++)
  {
	itoa(i, temp, 10);
	cout<<temp<<" ";
	Set.insert(temp);
  }
  delete temp;
  Set.insert("kiwi");
  Set.insert("plum");
  Set.insert("apple");
  Set.insert("mango");
  Set.insert("apricot");
  Set.insert("banana");

  lookup(Set, "mango");
  lookup(Set, "apple");
  lookup(Set, "durian");
  lookup(Set, "100");
  lookup(Set, "75");
  
  vector<int> V;
  V.insert(V.begin(), 3);
  assert(V.size() == 1 && V.capacity() >= 1 && V[0] == 3);
  cout<<"hello world"<<endl;
  return 0;
}