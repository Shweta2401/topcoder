#line 2 "LargestCircle.cpp"
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
#define sz(a)  int((a).size())
#define pb  push_back
#define all(c)  (c).begin(),(c).end()
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);var++)
#define found(s,e)  ((s).find(e)!=(s).end())

class LargestCircle {
  int in(int x,int y,int r, int u,int v){
    return (u-x)*(u-x) + (v-y)*(v-y) - r*r;
  }
 public:
  int radius(vector<string> grid) {
	int h=sz(grid), w=sz(grid[0]);
    if (h==1 || w==1) return 0;
    int R = 0;
    for(int x=1;x<=w-1;x++){
      int dxmax=min(x,w-x);
      for(int y=1;y<=h-1;y++){
        int dymax=min(y,h-y);
        int rmax=min(dxmax,dymax);
        for(int r=rmax;r>=1;r--){
// BEGIN CUT HERE
          //printf("(x0:%d,y0:%d)..r:%d\n", x,y,r);
          // (x-x0)^2 + (y-y0)^2 = r^2
// END CUT HERE
          bool ok=true;
          for(int u=0;u<w;u++){
            for(int v=0;v<h;v++){
              if(grid[v][u]=='#'){
// BEGIN CUT HERE
                // (u,v)   (u+1,v)
                // (u,v+1) (u+1,v+1)
// END CUT HERE
                int a = in(x,y,r, u,v);
                int b = in(x,y,r, u+1,v);
                int c = in(x,y,r, u,v+1);
                int d = in(x,y,r, u+1,v+1);
                if ((a>=0 && b>=0 && c>=0 && d>=0) || (a<=0 && b<=0 && c<=0 && d<=0)) {
// BEGIN CUT HERE
                  //printf("  o [u=%d,v=%d] a:%d b:%d c:%d d:%d\n", u,v, a,b,c,d);
                  // ok
// END CUT HERE
                } else {
// BEGIN CUT HERE
                  //printf("  x [u=%d,v=%d] a:%d b:%d c:%d d:%d\n", u,v, a,b,c,d);
// END CUT HERE
                  ok=false; goto out;
                }
              }
            }
          }
       out:
// BEGIN CUT HERE
          //if (ok) R<?=r;
// END CUT HERE
          if (ok) R>?=r;
        }
      }
    }
    return R;
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
	string grid_[] = { "####",
  "#..#",
  "#..#",
  "####" };
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 1; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<1>) {
	timer_clear();
	string grid_[] = { "############",
  "###......###",
  "##.######.##",
  "#.########.#",
  "#.##..####.#",
  "#.##..####.#",
  "#.########.#",
  "#.########.#",
  "#.########.#",
  "##.######.##",
  "###......###",
  "############" };
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 5; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<2>) {
	timer_clear();
	string grid_[] = { ".........." };
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 0; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<3>) {
	timer_clear();
	string grid_[] = { "#######",
  "#######",
  "#######",
  "#######",
  "#######" };
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 0; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<4>) {
	timer_clear();
	string grid_[] = { "#####.......",
  "#####.......",
  "#####.......",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............" };
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 4; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<5>) {
	timer_clear();
	string grid_[] = { "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#.#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#." }
;
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 0; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }
int Test_(Case_<6>) {
	timer_clear();
	string grid_[] = { ".........................#........................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  ".................................................." }
;
	  vector <string> grid(grid_, grid_+sizeof(grid_)/sizeof(*grid_)); 
	int RetVal = 24; 
	return verify_case(RetVal, LargestCircle().radius(grid)); }

template<int N> void Run_() { cerr << "Test Case #" << N << "..." << flush; Test_(Case_<N>()); Run_<sizeof(Test_(Case_<N+1>()))==1 ? -1 : N+1>(); }
template<>      void Run_<-1>() {}
int main() { Run_<0>(); }
// END CUT HERE


// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
NOTE: This problem statement contains images that may not display properly if viewed outside of the applet.



Given a regular square grid, with some number of squares marked, find
the largest circle you can draw on the grid that does not pass through
any of the marked squares.  The circle must be centered on a grid point
(the corner of a square) and the radius must be an integer.
Return the radius of the circle.


The grid will be given as a vector <string>, with each character
representing a square.  A '.' represents an empty square, and a '#'
represents a marked square.


The circle may intersect the corner of a marked square, but may not pass
through the interior.  For example, given the grid:



  { "############",
    "###......###",
    "##.######.##",
    "#.########.#",
    "#.##..####.#",
    "#.##..####.#",
    "#.########.#",
    "#.########.#",
    "#.########.#",
    "##.######.##",
    "###......###",
    "############" }


two circles can be drawn with radii 1 and 5, as shown below:







Therefore, your method should return 5.


Circles may not extend outside of the grid, and must have a radius of
at least 1.  If no such circle exists, return 0.


DEFINITION
Class:LargestCircle
Method:radius
Parameters:vector <string>
Returns:int
Method signature:int radius(vector <string> grid)


CONSTRAINTS
-grid will contain between 1 and 50 elements, inclusive.
-Each element of grid will contain between 1 and 50 characters, inclusive.
-Each element of grid will contain the same number of characters.
-Each element of grid will contain only the characters '.' and '#'.


EXAMPLES

0)
{ "####",
  "#..#",
  "#..#",
  "####" }

Returns: 1

Only one circle fits in this grid -- a circle of radius 1, in the center of the grid.

1)
{ "############",
  "###......###",
  "##.######.##",
  "#.########.#",
  "#.##..####.#",
  "#.##..####.#",
  "#.########.#",
  "#.########.#",
  "#.########.#",
  "##.######.##",
  "###......###",
  "############" }

Returns: 5

This is the example from the problem statement.

2)
{ ".........." }

Returns: 0

The grid must be at least two squares wide and tall in order for any circles to fit.

3)
{ "#######",
  "#######",
  "#######",
  "#######",
  "#######" }

Returns: 0

4)
{ "#####.......",
  "#####.......",
  "#####.......",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............",
  "............" }

Returns: 4

A circle of radius 4 fits in this grid, as shown here:




5)
{ "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#..",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  ".#...#...#...#...#...#...#...#...#...#...#...#...#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.",
  "...#...#...#...#...#...#...#...#...#...#...#...#.#",
  "#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#." }


Returns: 0

6)
{ ".........................#........................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  "..................................................",
  ".................................................." }


Returns: 24

*/
// END CUT HERE