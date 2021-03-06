// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A big box contains marbles of one or more colors. You're given a vector <int> colors, each element of which denotes the number of marbles there are of a particular color. You draw n marbles randomly from the box, leaving each marble outside the box after taking it. Return the probability that all marbles drawn will be the same color.

DEFINITION
Class:DrawingMarbles
Method:sameColor
Parameters:vector <int>, int
Returns:double
Method signature:double sameColor(vector <int> colors, int n)


NOTES
-Every time we draw a marble, all marbles in the box are equally likely to be chosen.
-A return value with either an absolute or relative error of less than 1.0E-9 is considered correct.


CONSTRAINTS
-colors will contain between 1 and 50 elements, inclusive.
-Each element of colors will be between 1 and 50, inclusive.
-n will be between 1 and the sum of all elements of colors, inclusive.


EXAMPLES

0)
{ 13 }
8

Returns: 1.0

All the marbles are the same color, so obviously all drawn marbles will be the same color too.

1)
{ 5, 7 }
1

Returns: 1.0



2)
{ 5, 6, 7 }
2

Returns: 0.3006535947712418

The probability that the first drawn marble will be of the color 0 is 5 / 18 (there are 5 marbles of color 0 out of 18). If the first drawn marble is of the color 0, then the probability that the second drawn marble will be of the color 0 is 4 / 17 (there are 4 marbles of color 0 left out of 17). So the probability that both drawn marbles will be of the color 0 is (5 / 18) * (4 / 17) = 0.0653594771... . Similarly, the probability that both drawn marbles will be of the color 1 is (6 / 18) * (5 / 17) = 0.0980392156..., and that both drawn marbles will be of the color 2 is (7 / 18) * (6 / 17) = 0.1372549019... . The answer is the sum of these 3 probabilities.

3)
{ 12, 2, 34, 13, 17 }
4

Returns: 0.035028830818304504



*/
// END CUT HERE

#line 63 "DrawingMarbles.cpp"
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
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);var++)


double c(int n, int r)
{
  if (n == 0 || r == 0 || r == n) return 1.0;
  if (r > n-r) r = n-r;
  return c(n-1,r-1) * n / r;
}

class DrawingMarbles {
 public:
  double sameColor(vector<int> colors, int n) {
	int cn=sz(colors);
    double r=0.0;
    int total=0LL;
    tr(colors,it) total+=(*it);
    double denom=c(total,n);
    rep(i,cn){
      int ci=colors[i]; total+=ci;
      if(ci>=n) r+=c(ci,n)/denom;
    }
    return r;
  }
};

// BEGIN CUT HERE
#include <time.h>
clock_t start_time;
void timer_clear() { start_time = clock(); }
string timer() { clock_t end_time = clock(); double interval = (double)(end_time - start_time)/CLOCKS_PER_SEC; ostringstream os; os << " (" << interval*1000 << " msec)"; return os.str(); }

template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
int verify_case(const double &Expected, const double &Received) { double diff = Expected - Received; if (diff < 0) diff = -diff; if (diff < 1e-9) cerr << "PASSED" << timer() << endl; else { cerr << "FAILED" << timer() << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } return 0;}

template<int N> struct Case_ {};
char Test_(...);
int Test_(Case_<0>) {
	timer_clear();
	int colors_[] = { 13 };
	  vector <int> colors(colors_, colors_+sizeof(colors_)/sizeof(*colors_)); 
	int n = 8; 
	double RetVal = 1.0; 
	return verify_case(RetVal, DrawingMarbles().sameColor(colors, n)); }
int Test_(Case_<1>) {
	timer_clear();
	int colors_[] = { 5, 7 };
	  vector <int> colors(colors_, colors_+sizeof(colors_)/sizeof(*colors_)); 
	int n = 1; 
	double RetVal = 1.0; 
	return verify_case(RetVal, DrawingMarbles().sameColor(colors, n)); }
int Test_(Case_<2>) {
	timer_clear();
	int colors_[] = { 5, 6, 7 };
	  vector <int> colors(colors_, colors_+sizeof(colors_)/sizeof(*colors_)); 
	int n = 2; 
	double RetVal = 0.3006535947712418; 
	return verify_case(RetVal, DrawingMarbles().sameColor(colors, n)); }
int Test_(Case_<3>) {
	timer_clear();
	int colors_[] = { 12, 2, 34, 13, 17 };
	  vector <int> colors(colors_, colors_+sizeof(colors_)/sizeof(*colors_)); 
	int n = 4; 
	double RetVal = 0.035028830818304504; 
	return verify_case(RetVal, DrawingMarbles().sameColor(colors, n)); }
int Test_(Case_<4>) {
	timer_clear();
	int colors_[] = { 50,50,50,50,50,50,50,50,50,50 };
	  vector <int> colors(colors_, colors_+sizeof(colors_)/sizeof(*colors_)); 
	int n = 10; 
	double RetVal = 4.178940467970992E-10;
	return verify_case(RetVal, DrawingMarbles().sameColor(colors, n)); }

template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
int main() { Run_<0>(); }
// END CUT HERE

