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
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<string> vs;
typedef vector<long long> vll;
#define sz(a)  int((a).size())
#define pb  push_back
#define all(c)  (c).begin(),(c).end()
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);var++)
#define FOR(var,from,to) for(int var=(from);var<=(to);var++)
#define RFOR(var,from,to) for(int var=(to);var>=(from);var--)
#define found(s,e)  ((s).find(e)!=(s).end())
#define mset(arr,val)  memset(arr,val,sizeof(arr))
 
typedef pair<int,int> i_i;
typedef pair<ll,ll> ll_ll;
typedef pair<double,double> d_d;
typedef pair<int,pair<int,int> > i_ii;
 
class PlanarGraphShop {
  vector<int> xs; int xsn;
  //map<int,int> m0;
  vector<int> m,m0;
  
  int cost(int v, int e){
    return v*v*v + e*e;
  }
  int sub(int n){
    if(m[n]<INT_MAX) return m[n];
    priority_queue<int> pq;
    tr(m0,it){
      int x=*it; if(x>n) continue; if(x==n)return 1;
      pq.push(-(1+m[n-x]));
    }
    return -pq.top();
  }
 public:
  int bestCount(int N) {
    double r = pow((double)N, 1.0/3);
    int rc = (int)floor(r + .00001);
 
    set<int> cs;
    FOR(n,1,rc){
      /// FOR(e,0,max(0,n*2-3)){
      FOR(e,0,max(0,n<3?n-1:n*3-6)){
        int c=cost(n,e);
        if(c>N) continue;
        if(c==N) return 1;
        cs.insert(c);
      }
    }
    xs.assign(all(cs)); xsn=sz(xs);
    m0.clear();
    m.resize(N+1); FOR(i,0,N) m[i]=INT_MAX;
    tr(xs,it) { m0.pb(*it); m[*it]=1; }
 
    FOR(i,1,N){
      if (m[i] < INT_MAX) continue;
      m[i] = sub(i);
    }
    return m[N];
  }
};
 
 
 
 
 
// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003] customized by cafelier, timer support by naoya_t
// Powered by CodeProcessor
#include "cout.h"
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
	int N = 36; 
	int RetVal = 1; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<1>) {
	timer_clear();
	int N = 7; 
	int RetVal = 7; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<2>) {
	timer_clear();
	int N = 72; 
	int RetVal = 2; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<3>) {
	timer_clear();
	int N = 46; 
	int RetVal = 3; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<4>) {
	timer_clear();
	int N = 1; 
	int RetVal = 1; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<5>) { // #40
	timer_clear();
	int N = 100; 
	int RetVal = 1; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<6>) {
	timer_clear();
	int N = 50000; 
	int RetVal = 2; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
int Test_(Case_<7>) {
	timer_clear();
	int N = 100; 
	int RetVal = 1; 
	return verify_case(RetVal, PlanarGraphShop().bestCount(N)); }
template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
int main() { Run_<0>(); }
