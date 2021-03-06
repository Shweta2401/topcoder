#line 2 "PerfectPermutation.cpp"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
// BEGIN CUT HERE
#include "cout.h"
// END CUT HERE
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<string> vs;
typedef vector<long long> vll;
#define sz(a)  int((a).size())
#define pb  push_back
#define all(c)  (c).begin(),(c).end()
#define mset(arr,val)  memset(arr,val,sizeof(arr))
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);var++)
#define forr(var,from,to) for(int var=(from);var<=(to);var++) 
#define found(s,e)  ((s).find(e)!=(s).end())
#define remove_(c,val) (c).erase(remove((c).begin(),(c).end(),(val)),(c).end())
#define lastc(str) (*((str).end()-1))

vector<int> isle(const vector<vector<bool> >& plan) {
  int n=plan.size();
  vector<int> id(n,0); for(int i=0;i<n;i++) id[i]=i;
  for (int i=0;i<n-1;i++) {
    for (int j=i+1;j<n;j++) {
      if (plan[i][j]==true) {
        int idi=id[i],idj=id[j];
        if (idi>idj) {
          replace(id.begin(),id.end(),idi,idj);
        } else if (idi<idj) {
          replace(id.begin(),id.end(),idj,idi);
        }
      }
    }
  }
  return id;
}

map<int,int> summary(const vector<int>& id)
{
  map<int,int> s;
  for(int i=id.size()-1;i>=0;i--){
    if(s.find(id[i])==s.end()) s[id[i]]=1;
    else s[id[i]]++;
  }
  return s;
}

class PerfectPermutation {
 public:
  int reorder(vector<int> P) {
    //cout << "P: " << P << endl;
    int n=sz(P);
	vector<vector<bool> > a(n,vector<bool>(n,false));
    rep(i,n) a[i][P[i]] = a[P[i]][i] = true;
    map<int,int> isles = summary(isle(a));
    // cout << "isle: " << isle(a) << endl;
    // cout << s << endl;
    int s = sz(isles);
    return (s==1)?0:s;
  }
};

// BEGIN CUT HERE
#include <time.h>
clock_t start_time;
void timer_clear() { start_time = clock(); }
string timer() { clock_t end_time = clock(); double interval = (double)(end_time - start_time)/CLOCKS_PER_SEC; ostringstream os; os << " (" << interval*1000 << " msec)"; return os.str(); }

template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
int verify_case(const int &Expected, const int &Received) { if (Expected == Received) cerr << "PASSED" << timer() << endl; else { cerr << "FAILED" << timer() << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } return 0;}

template<int N> struct Case_ {};
char Test_(...);
int Test_(Case_<0>) {
	timer_clear();
	int P_[] = {2, 0, 1};
	  vector <int> P(P_, P_+sizeof(P_)/sizeof(*P_)); 
	int RetVal = 0; 
	return verify_case(RetVal, PerfectPermutation().reorder(P)); }
int Test_(Case_<1>) {
	timer_clear();
	int P_[] = {2, 0, 1, 4, 3};
	  vector <int> P(P_, P_+sizeof(P_)/sizeof(*P_)); 
	int RetVal = 2; 
	return verify_case(RetVal, PerfectPermutation().reorder(P)); }
int Test_(Case_<2>) {
	timer_clear();
	int P_[] = {2, 3, 0, 1};
	  vector <int> P(P_, P_+sizeof(P_)/sizeof(*P_)); 
	int RetVal = 2; 
	return verify_case(RetVal, PerfectPermutation().reorder(P)); }
int Test_(Case_<3>) {
	timer_clear();
	int P_[] = {0, 5, 3, 2, 1, 4};
	  vector <int> P(P_, P_+sizeof(P_)/sizeof(*P_)); 
	int RetVal = 3; 
	return verify_case(RetVal, PerfectPermutation().reorder(P)); }
int Test_(Case_<4>) {
	timer_clear();
	int P_[] = {4, 2, 6, 0, 3, 5, 9, 7, 8, 1};
	  vector <int> P(P_, P_+sizeof(P_)/sizeof(*P_)); 
	int RetVal = 5; 
	return verify_case(RetVal, PerfectPermutation().reorder(P)); }

template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
int main() { Run_<0>(); }
// END CUT HERE


// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A permutation A[0], A[1], ..., A[N-1] is a sequence containing each integer between 0 and N-1, inclusive, exactly once.  Each permutation A of length N has a corresponding child array B of the same length, where B is defined as follows:


B[0] = 0
B[i] = A[B[i-1]], for every i between 1 and N-1, inclusive.


A permutation is considered perfect if its child array is also a permutation.

Below are given all permutations for N=3 with their child arrays. Note that for two of these permutations ({1, 2, 0} and {2, 0, 1}) the child array is also a permutation, so these two permutations are perfect.


Permutation		Child array
{0, 1, 2}		{0, 0, 0}
{0, 2, 1}		{0, 0, 0}
{1, 0, 2}		{0, 1, 0}
{1, 2, 0}		{0, 1, 2}
{2, 0, 1}		{0, 2, 1}
{2, 1, 0}		{0, 2, 0}


You are given a vector <int> P containing a permutation of length N.  Find a perfect permutation Q of the same length such that the difference between P and Q is as small as possible, and return this difference.  The difference between P and Q is the number of indices i for which P[i] and Q[i] are different.

DEFINITION
Class:PerfectPermutation
Method:reorder
Parameters:vector <int>
Returns:int
Method signature:int reorder(vector <int> P)


CONSTRAINTS
-P will contain between 1 and 50 elements, inclusive.
-P will contain each integer between 0 and N-1, inclusive, exactly once, where N is the number of elements in P.


EXAMPLES

0)
{2, 0, 1}

Returns: 0

P is a perfect permutation, so we can use the same permutation for Q.  The difference is then 0 because P and Q are the same.

1)
{2, 0, 1, 4, 3}

Returns: 2

Q might be {2, 0, 3, 4, 1}.

2)
{2, 3, 0, 1}

Returns: 2

Q might be {1, 3, 0, 2}.

3)
{0, 5, 3, 2, 1, 4}

Returns: 3



4)
{4, 2, 6, 0, 3, 5, 9, 7, 8, 1}

Returns: 5



*/
// END CUT HERE
