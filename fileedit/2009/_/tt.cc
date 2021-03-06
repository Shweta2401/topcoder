// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Twin Towns are towns which are paired together to encourage human contact and cultural links.  The government of your country has decided to establish such relationships among a given set of towns.  The following rules must be followed:

Each town must have between 0 and maxPartners twins, inclusive.
The distance between each pair of twin towns must be at least minDistance.  The distance between two towns located at (x1, y1) and (x2, y2) is defined as |x1-x2| + |y1-y2|.



The government will establish as many relationships as possible.  If there are multiple ways to do this, the government will choose the one that minimizes the sum of the distances between each pair of twin towns.  You are given vector <int>s x and y, where (x[i], y[i]) are the coordinates of the i-th town.  Return a vector <int> containing exactly two elements, where the first element is the number of relationships the government will establish, and the second element is the sum of the distances between each pair of twin towns.

DEFINITION
Class:TwinTowns
Method:optimalTwinTowns
Parameters:vector <int>, vector <int>, int, int
Returns:vector <int>
Method signature:vector <int> optimalTwinTowns(vector <int> x, vector <int> y, int maxPartners, int minDistance)


CONSTRAINTS
-maxPartners will be between 1 and 3, inclusive.
-x and y will contain between 1 and 10 elements, inclusive.
-x and y will contain the same number of elements.
-Each element of x and y will be between 0 and 1,000, inclusive.
-minDistance will be between 1 and 2,000, inclusive.
-No two towns will have the same coordinates.


EXAMPLES

0)
{0,0,10}
{0,10,4}
1
1

Returns: {1, 10 }

We have 3 towns here at coordinates (0,0), (0,10), and (10,4).  Each town can have at most one twin.  Since we have only 3 towns, we can establish at most one pair of twin towns.  The best solution pairs the first and second towns, where the distance is 10.

1)
{0,0,10}
{0,10,4}
1
11

Returns: {1, 14 }

These are the same towns from Example 0, but minDistance is now 11.  The first and second towns cannot be twins.  The best solution is to pair the first and third towns, where the distance is 14.

2)
{0,10,0,10}
{0,0,20,20}
1
1

Returns: {2, 20 }

Here we have 4 towns located at the vertices of a rectangle.  Each town can have at most one twin.  The best solution is to pair the first town with the second, and the third town with the fourth.  The distance between each pair is 10.


3)
{0,10,0,10}
{0,0,20,20}
2
10

Returns: {4, 60 }

These are the same towns from Example 2, but now, each town can have up to two twins.  The best solution establishes 4 pairs of twin towns:

the first city at (0,0) with the second city at (10,0), where the distance is 10
the first city at (0,0) with the third city at (0,20), where the distance is 20
the second city at (10,0) with the fourth city at (10,20), where the distance is 20
the third city at (0,20) with the fourth city at (10,20), where the distance is 10

The sum of the distances is 60.

4)
{0,0,0,0,0,0,0,0,0}
{1,2,3,4,5,6,7,8,9}
3
6

Returns: {6, 40 }

We can pair the following list of towns (indexed from 1): 1-7, 1-8, 1-9, 2-8, 2-9, 3-9.

*/
// END CUT HERE

#line 94 "TwinTowns.cpp"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
// BEGIN CUT HERE
#include <iostream>
#include "cout.h"
// END CUT HERE
#include <sstream>
#include <cmath>
using namespace std;

#define sz(a)  int((a).size())
#define pb  push_back
#define all(c)  (c).begin(),(c).end()
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);var++)

// BEGIN CUT HERE
/*
template <typename T>
  vector<vector<T> > combinations(const vector<T>& list, int r)
{
  int n = list.size();
  int nCr = c(n, r);
  vector<vector<T> > result(nCr);
  vector<int> curr(r); for (int i=0; i<r; i++) curr[i] = i;

  for (int idx=0; idx<nCr; idx++) {
	result[idx].resize(r);
	for (int i=0; i<r; i++) result[idx][i] = list[curr[i]];

	for (int i=r-1; i>=0; i--) {
	  if (curr[i] == n-(r-i)) {
		if (i == 0) return result;
		continue;
	  } else {
		int ofs = curr[i] - i + 1;
		for (int j=i; j<r; j++) curr[j] = j + ofs;
		break;
	  }
	}
  }
}
*/
// END CUT HERE

class TwinTowns {
  int n, maxP;
  int distance[10][10];
  int available[10], pat[10];

public:
  vector<int> sub(int st)
  {
	///printf("sub(%d): \n", st);
	if (st == n) {
	  vector<int> ans(2,0);
	  return ans;
	}

	int mp = maxP;
	for (int i=0,m=1; i<st; i++,m<<=1) if (pat[st] & m) mp--;
	if (mp < 0) {
	  vector<int> ans(2,0);
	  return ans;
	}
	
	int a = 1 << (n-st-1);

	int cmax = 0, dmin = INT_MAX;

	rep(p,a) {
	  int popc = __builtin_popcount(p);
	  if (popc <= mp) {
		if ((available[st] & p) == p) {
		  /*printf(" p=%d, popc=%d, available[%d] = %d\n",
			p, popc, st, available[st] );*/
		  int k = pat[st];
		  pat[st] |= (p << (st+1));
		  vector<int> ans = sub(st+1);
		  if (ans[0] > cmax) {
			cmax = ans[0];
			dmin = ans[1];
		  } else if (ans[0] == cmax) {
			if (ans[1] < dmin) dmin = ans[1];
		  }
		  pat[st] = k;
		}
	  }
	}
	
	vector<int> ans(2,0);
	ans[0] = cmax; ans[1] = dmin;
	return ans;
  }

  vector<int> optimalTwinTowns(vector<int> x, vector<int> y, int maxPartners, int minDistance) {
	n = x.size();
	maxP = maxPartners;
// BEGIN CUT HERE
	// maxPartners: 1-3
	// n:1-10, 座標値は0-1000
	// minDistance:1-2000
// END CUT HERE
	rep(j,n) {
	  available[j] = 0;
	  for (int i=0,m=1; i<n; i++,m<<=1) {
		if (i == j) continue;
		int dist = abs(x[i]-x[j]) + abs(y[i]-y[j]);
		distance[i][j] = distance[j][i] = dist;
		available[i] |= (1 << j);
		available[j] |= (1 << i);
	  }
	}

	rep(i,n) pat[i] = 0;
	return sub(0);
	

	/*

	int cnt=0,dist=0;
		
	//cout << "pat: i=" << i << endl;
	
	for (int st=0; st<n-1; st++) {
	  int b=1<<(n-st-1);
	  for (int i=0;i<b;i++) {
		if (__builtin_popcount(i) > maxP) continue; // break;..oops
		for (int j=1;j<n;j++) { pat[st][j] = pat[j][st] = false; } // clear


	  int maxP = maxPartners;
	  for (int j=0;j<st;j++) if (pat[st][j]) maxP--;
	  if (maxP < 0) goto invalid;

		//printf("st=%d, maxP=%d, b=%d\n",st,maxP,b);
		if (__builtin_popcount(j) > maxP) continue; // break;..oops
		//printf("  j=%d,st+1=%d,n=%d\n", j,st+1,n);
		for (int k=st+1;k<n;k++) { pat[st][k] = pat[k][st] = false; }
		c=0;
		for (int m=1,q=st+1;m<b;m<<=1,q++) {
		  if (m & j == 0) continue;
		  //printf("  q = %d\n", q);
		  if (p[st][q]) {
			pat[st][q] = pat[q][st] = true;
			c++;
		  }
		}
	  }
	}

	  for (int st=0;st<n;st++) {
		c=0;
		for (int j=0;j<n;j++) {
		  if (j == st) continue;
		  if (pat[st][j]) c++;
		}
		if (c > maxPartners) {
		  //printf("over<st=%d>\n", st);
		  goto invalid;
		}
	  }

	  cout << pat << endl;

	  for (int y=0;y<n;y++) {
		for (int x=y+1;x<n;x++) {
		  if (pat[y][x]) { cnt++; dist+=d[y][x]; }
		}
	  }
	  if (cnt > cmax) { cmax = cnt; dmin = dist; }
	  else if (cnt == cmax && dist < dmin) { dmin = dist; }

	  invalid:;
	  //}

	vector<int> ans(2,0);
	ans[0] = cmax; ans[1] = dmin;
	return ans;
	*/
  }
};

// BEGIN CUT HERE
#include <time.h>
clock_t start_time;
void timer_clear() { start_time = clock(); }
string timer() { clock_t end_time = clock(); double interval = (double)(end_time - start_time)/CLOCKS_PER_SEC; ostringstream os; os << " (" << interval*1000 << " msec)"; return os.str(); }

template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
int verify_case(const vector <int> &Expected, const vector <int> &Received) { if (Expected == Received) cerr << "PASSED" << timer() << endl; else { cerr << "FAILED" << timer() << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } return 0;}

template<int N> struct Case_ {};
char Test_(...);
int Test_(Case_<0>) {
	timer_clear();
	int x_[] = {0,0,10};
	  vector <int> x(x_, x_+sizeof(x_)/sizeof(*x_)); 
	int y_[] = {0,10,4};
	  vector <int> y(y_, y_+sizeof(y_)/sizeof(*y_)); 
	int maxPartners = 1; 
	int minDistance = 1; 
	int RetVal_[] = {1, 10 };
	  vector <int> RetVal(RetVal_, RetVal_+sizeof(RetVal_)/sizeof(*RetVal_)); 
	return verify_case(RetVal, TwinTowns().optimalTwinTowns(x, y, maxPartners, minDistance)); }
int Test_(Case_<1>) {
	timer_clear();
	int x_[] = {0,0,10};
	  vector <int> x(x_, x_+sizeof(x_)/sizeof(*x_)); 
	int y_[] = {0,10,4};
	  vector <int> y(y_, y_+sizeof(y_)/sizeof(*y_)); 
	int maxPartners = 1; 
	int minDistance = 11; 
	int RetVal_[] = {1, 14 };
	  vector <int> RetVal(RetVal_, RetVal_+sizeof(RetVal_)/sizeof(*RetVal_)); 
	return verify_case(RetVal, TwinTowns().optimalTwinTowns(x, y, maxPartners, minDistance)); }
int Test_(Case_<2>) {
	timer_clear();
	int x_[] = {0,10,0,10};
	  vector <int> x(x_, x_+sizeof(x_)/sizeof(*x_)); 
	int y_[] = {0,0,20,20};
	  vector <int> y(y_, y_+sizeof(y_)/sizeof(*y_)); 
	int maxPartners = 1; 
	int minDistance = 1; 
	int RetVal_[] = {2, 20 };
	  vector <int> RetVal(RetVal_, RetVal_+sizeof(RetVal_)/sizeof(*RetVal_)); 
	return verify_case(RetVal, TwinTowns().optimalTwinTowns(x, y, maxPartners, minDistance)); }
int Test_(Case_<3>) {
	timer_clear();
	int x_[] = {0,10,0,10};
	  vector <int> x(x_, x_+sizeof(x_)/sizeof(*x_)); 
	int y_[] = {0,0,20,20};
	  vector <int> y(y_, y_+sizeof(y_)/sizeof(*y_)); 
	int maxPartners = 2; 
	int minDistance = 10; 
	int RetVal_[] = {4, 60 };
	  vector <int> RetVal(RetVal_, RetVal_+sizeof(RetVal_)/sizeof(*RetVal_)); 
	return verify_case(RetVal, TwinTowns().optimalTwinTowns(x, y, maxPartners, minDistance)); }
int Test_(Case_<4>) {
	timer_clear();
	int x_[] = {0,0,0,0,0,0,0,0,0};
	  vector <int> x(x_, x_+sizeof(x_)/sizeof(*x_)); 
	int y_[] = {1,2,3,4,5,6,7,8,9};
	  vector <int> y(y_, y_+sizeof(y_)/sizeof(*y_)); 
	int maxPartners = 3; 
	int minDistance = 6; 
	int RetVal_[] = {6, 40 };
	  vector <int> RetVal(RetVal_, RetVal_+sizeof(RetVal_)/sizeof(*RetVal_)); 
	return verify_case(RetVal, TwinTowns().optimalTwinTowns(x, y, maxPartners, minDistance)); }

template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
//int main() { Run_<0>(); }
int main(int argc, char *argv[])
{
  int n = (argc == 2)? atoi(argv[1]) : -1;
  if (n >= 0) {
	cerr << "Test Case #" << n << "..." << flush;
	switch (n) {
	case 0:	Test_(Case_<0>()); break;
	case 1:	Test_(Case_<1>()); break;
	case 2:	Test_(Case_<2>()); break;
	case 3:	Test_(Case_<3>()); break;
	case 4:	Test_(Case_<4>()); break;
	  //	case 5:	Test_(Case_<5>()); break;
	  //case 6:	Test_(Case_<6>()); break;
	default: Run_<0>(); break;
	}
  } else {
	Run_<0>();
  }
}
// END CUT HERE

