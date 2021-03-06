#line 2 "StrongEconomy.cpp"
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

class StrongEconomy {
	public:
	long long earn(long long n, long long k, long long price, long long target) {
      double l_n = log2l((long double)n),
          l_k = log2l((long double)k),
          l_p = log2l((long double)price),
          l_t = log2l((long double)target);
// BEGIN CUT HERE
      printf("earn(%lld <%d>, %lld <%d>, %lld <%d>, %lld <%d>)...\n",
             n, (int)ceil(l_n),
             k, (int)ceil(l_k),
             price, (int)ceil(l_p),
             target, (int)ceil(l_t)
             );
// END CUT HERE
      if (l_n + l_k >= 13 || n*k >= target) {
        //printf("n=%lld, k=%lld, n*k=%g...\n", n,k,(double)n*k);
        return 1;
      }
      
      ll t=0, am=0LL, nk=n*k;
      ll atmost = target / nk; if (target % nk) atmost++;
      printf("t=0, gold=0, nk=%lld; at most: %lld\n", nk, atmost);
      while(1){
        am += nk; t++;
        if (am>=target) return t;
        
        if (am<price) {
          ll i = (price-am)/nk;
          if (price-am > nk*i) i++;
          am += nk * i; t+=i;
        }
        if (am>=target) return t;

        printf("t=%lld, gold=%lld\n", t,am);

        if (n<k) swap(n,k); // n>=k
        ll p = am/price; am%=price;
        if (p){ // 
          ll d=n-k;
          if (p<=d) k+=p;
          else {
            k+=d; p-=d;
            k+=(p/2); n+=(p-p/2);
          }
        }
        nk = n*k;
      }
    }
};

// BEGIN CUT HERE
#include <time.h>
clock_t start_time;
void timer_clear() { start_time = clock(); }
string timer() { clock_t end_time = clock(); double interval = (double)(end_time - start_time)/CLOCKS_PER_SEC; ostringstream os; os << " (" << interval*1000 << " msec)"; return os.str(); }

template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
int verify_case(const long long &Expected, const long long &Received) { if (Expected == Received) cerr << "PASSED" << timer() << endl; else { cerr << "FAILED" << timer() << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } return 0;}

template<int N> struct Case_ {};
char Test_(...);
int Test_(Case_<0>) {
	timer_clear();
	long long n = 2LL; 
	long long k = 1LL; 
	long long price = 2LL; 
	long long target = 10LL; 
	long long RetVal = 4LL; 
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }
int Test_(Case_<1>) {
	timer_clear();
	long long n = 2LL; 
	long long k = 1LL; 
	long long price = 2LL; 
	long long target = 9LL; 
	long long RetVal = 3LL; 
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }
int Test_(Case_<2>) {
	timer_clear();
	long long n = 1LL; 
	long long k = 1LL; 
	long long price = 500000LL; 
	long long target = 1000002LL; 
	long long RetVal = 1000001LL; 
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }
int Test_(Case_<3>) {
	timer_clear();
	long long n = 5LL; 
	long long k = 4LL; 
	long long price = 15LL; 
	long long target = 100LL; 
	long long RetVal = 5LL; 
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }
int Test_(Case_<4>) {
	timer_clear();
	long long n = 1LL; 
	long long k = 1LL; 
	long long price = 1000000000000LL;
	long long target = 1000000000000LL;
	long long RetVal = -1LL; //???
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }
int Test_(Case_<5>) {
	timer_clear();
	long long n = 1000000000000LL;
	long long k = 1000000000000LL;
	long long price = 1000000000000LL;
	long long target = 1000000000000LL;
	long long RetVal = 1LL;
	return verify_case(RetVal, StrongEconomy().earn(n, k, price, target)); }


template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
int main() { Run_<0>(); }
// END CUT HERE


// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// As a serious strategy-games player, you know how important it is for your country to have a strong economy.  In order to make this happen, you've just built n factories and hired k specialists.  Unfortunately, you now have no gold left, and you must figure out the fastest way to raise target units of gold.
In a single round, you earn F*S units of gold, where F is the number of factories and S is the number of specialists you currently have.  At the end of each round, you can build more factories and hire more specialists.  Building one new factory or hiring one new specialist costs price units of gold.  As long as you can afford them, there is no limit to the number of factories and specialists you have.  Return the minimum number of rounds required to earn at least target units of gold.

DEFINITION
Class:StrongEconomy
Method:earn
Parameters:long long, long long, long long, long long
Returns:long long
Method signature:long long earn(long long n, long long k, long long price, long long target)


CONSTRAINTS
-n, k, price and target will each be between 1 and 10^12, inclusive.


EXAMPLES

0)
2
1
2
10

Returns: 4

In the first round you will earn 2*1 = 2 units of gold and must spend them on hiring a new specialist. In each of the rounds that follow, you will earn 2*2 = 4 units of gold. You need 3 more rounds in order to earn at least 10 units of gold.

1)
2
1
2
9

Returns: 3

In the first round you will earn 2*1 = 2 units of gold and must spend them on hiring a new specialist. In the second round you will earn 2*2 = 4 units of gold and must spend them on building a factory and hiring another specialist. In the third round you will earn 3*3 = 9 units of gold.

2)
1
1
500000
1000002

Returns: 1000001

Wait 500000 rounds in order to earn 500000*1*1 = 500000 units of gold. At the end of the 500000th round, spend all your money to build a factory (or to hire a specialist). In each of the rounds that follow, you will earn 2*1 = 2 units of gold, so you need 500001 more rounds in order to earn the required 1000002 units of gold.

3)
5
4
15
100

Returns: 5

Don't spend your gold at all.

*/
// END CUT HERE
