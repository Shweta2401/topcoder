// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Several travelers are standing at the entrance of a dark cave.  The travelers must all pass through the cave and stand together at the exit.  Unfortunately, a variety of circumstances can make it impossible for them to all pass through the cave together at the same time.  Therefore, they may have to take turns going through the cave in smaller groups.  There is only one map though, and it is impossible to navigate the cave without it, so whenever a group of travelers is inside the cave, one member of that group must be holding the map.
When a group of travelers walks through the cave, either from the entrance or the exit, they must traverse an old bridge to get to the other side of the cave.  The entire group inside the cave must cross the bridge together at the same time.  The bridge cannot hold more than bridgeStrength kilograms, or it will collapse.  You are given a vector <int> travelersWeights, where the i-th element is the weight of the i-th traveler in kilograms.
Travelers may walk through the cave alone. Although, when travelers walk through the cave in a group of two or more, each traveler must trust at least one of the other travelers in the group. You are given a vector <string> trustTable, where the j-th character of the i-th element is 'Y' if traveler i trusts traveler j, and 'N' otherwise.  Note that the trust relation is not necessarily symmetric.
Travelers walk at different speeds, but when they go through the cave, they must stick together and walk at the same speed.  Therefore, when a group of travelers walks through the cave, they must walk at the speed of the slowest traveler in the group.  You are given a vector <int> travelersTimes, where the i-th element is the amount of time it takes the i-th traveler to walk through the cave in any direction.
Return the minimal total time required for all the travelers to end up together at the exit of the cave.  If it is impossible, return -1 instead.

DEFINITION
Class:CavePassage
Method:minimalTime
Parameters:vector <int>, vector <int>, vector <string>, int
Returns:int
Method signature:int minimalTime(vector <int> travelersWeights, vector <int> travelersTimes, vector <string> trustTable, int bridgeStrength)


CONSTRAINTS
-travelersWeights will contain between 1 and 13 elements, inclusive.
-Each element of travelersWeights will be between 1 and 1000, inclusive.
-travelersTimes will contain the same number of elements as travelersWeights.
-Each element of travelersTimes will be between 1 and 1000, inclusive.
-trustTable will contain the same number of elements as travelersWeights.
-Each element of trustTable will contain exactly n characters, where n is the number of elements in trustTable.
-Each element of trustTable will contain only uppercase letters 'Y' and 'N'.
-The i-th character of the i-th element of trustTable will always be 'Y'.
-bridgeStrength will be between 1 and 5000, inclusive.


EXAMPLES

0)
{ 1, 1, 1 }
{ 2, 3, 4 }
{ "YYY", "YYY", "YYY" }
2

Returns: 9

The travelers can achieve the goal as follows.  First, traveler 0 and traveler 2 go through the cave together.  It normally takes 2 time units for traveler 0 to go through the cave, and it takes 4 time units for traveler 2.  Since they are traveling together in a group, they must walk at the speed of the slower traveler.  So, after 4 time units, both travelers are at the exit.  Then, traveler 0 takes the map and goes back through the cave to the entrance.  This time, it only takes 2 time units because he is alone.  Finally, traveler 0 and traveler 1 go through the cave together in 3 time units and all the travelers end up together at the exit.  The total time is 4 + 2 + 3 = 9.

1)
{ 1, 1, 1 }
{ 2, 3, 4 }
{ "YYY", "YYY", "NYY" }
2

Returns: 10

Here things become a little bit more complicated, because traveler 2 doesn't trust traveler 0.

2)
{ 1, 1, 1 }
{ 7, 13, 19 }
{ "YYN", "NYY", "YNY" }
3

Returns: 19



3)
{ 43 }
{ 23 }
{ "Y" }
42

Returns: -1



*/
// END CUT HERE

#line 76 "CavePassage.cpp"
#include <string>
#include <vector>
// BEGIN CUT HERE
#include <iostream>
#include "cout.h"
#include <time.h>
// END CUT HERE
#include <sstream>
using namespace std;

class CavePassage {
  int nn;

  int calc_weights(int mask, vector<int> weights, int bridgeStrength)
  {
	int w = 0;
	for (int i=0,m=1; i<nn; i++,m<<=1) if (mask & m) w += weights[i];
	//	printf("calc_weights: mask=%x, w=%d, %d\n", mask, w, (w <= bridgeStrength) ? w : -1);
	return (w <= bridgeStrength) ? w : -1;
  }
  int slowest(int mask, vector<int> times)
  {
	int t_max = 0;
	for (int i=0,m=1; i<nn; i++,m<<=1) if (mask & m) t_max = max(t_max, times[i]);
	return t_max;
  }
  int fastest(int mask, vector<int> times)
  {
	int t_min = 9999;
	for (int i=0,m=1; i<nn; i++,m<<=1) {
	  if (mask & m) {
		if (t_min > times[i]) {
		  t_min = times[i];
		  fastest_ones[mask] = m;
		}
	  }
	}
	return t_min;
  }
  bool calc_trusts(int mask, vector<string> trustTable)
  {
	if (__builtin_popcount(mask) == 1) return true;

	for (int i=0,mi=1; i<nn; i++,mi<<=1) {
	  if (mask & mi) {
		int trust_cnt = 0;
		for (int j=0,mj=1; j<nn; j++,mj<<=1) {
		  if (j != i && (mask & mj)) {
			if (trustTable[i][j] == 'Y') trust_cnt++;
		  }
		}
		if (trust_cnt == 0) return false;
	  }
	}
	return true;
  }

  int patterns;
  int all_mask;
  int min_time;
  int *weights;
  int *slowests;
  int *fastests;
  int *fastest_ones;
  bool *trusts;
  bool *possible;

  //  int back(int passed_mask, int lapse)
  int go(int passed_mask, int lapse)
  {
	printf("go(%02x, %d) ;; min_time=%d\n", passed_mask, lapse, min_time);
	if (passed_mask == all_mask) {
	  min_time = lapse;
	  return lapse;
	}

	if (lapse > min_time) return -1;

	int lmin = 0x7fffffff;
	for (int m=all_mask; m>=1; m--) {
	  //cout << "\n<*>" << m;
	  //	  printf("{ possible[%x]=%d }", m, possible[m]);
	  if (possible[m] & (!(m & passed_mask))) {
		if ((passed_mask | m) == all_mask) {
		  lmin = min(lmin, lapse + slowests[m]);
		  //		} else if (m == fastest_ones[m]) {
		} else if (m == fastest_ones[passed_mask|m]) {
		  continue;
		} else {
		  //		  int s = go(passed_mask | (m & ~fastest_ones[m]),
		  //					  lapse + slowests[m] + fastests[m]);
		  printf("s = go( (%x | %x) & ~(%x), %d + %d + %d\n",
				 passed_mask, m, fastest_ones[passed_mask|m],
				 lapse, slowests[m], fastests[passed_mask|m] );
		  int s = go((passed_mask | m) & ~fastest_ones[passed_mask|m],
					  lapse + slowests[m] + fastests[passed_mask|m]);
		  if (s < 0) continue;
		  lmin = min(lmin, s);
		}
	  }
	}
	if (lmin == 0x7fffffff) return -1;
	min_time = min(min_time, lmin);
	return lmin;
  }

public:
  int minimalTime(vector<int> travelersWeights,
				  vector<int> travelersTimes,
				  vector<string> trustTable,
				  int bridgeStrength) {
	
	nn = travelersWeights.size();
	patterns = 1 << nn;
	all_mask = patterns - 1;
	min_time = 0x7fffffff;//100000;
	  /*	  
	  bool tt[13][13];
	  for (int i=0;i<nn;i++)
		for (int j=0;j<nn;j++)
		  tt[i][j] = (trustTable[i][j] == 'Y')?true:false;
	  */
	weights = new int[patterns];
	slowests = new int[patterns];
	fastests = new int[patterns];
	fastest_ones = new int[patterns];
	trusts = new bool[patterns];
	possible = new bool[patterns];
	int possible_count = 0;

	for (int m=1; m<patterns; m++) {
	  weights[m] = calc_weights(m, travelersWeights, bridgeStrength);
	  slowests[m] = slowest(m, travelersTimes);
	  fastests[m] = fastest(m, travelersTimes);
	  trusts[m] = calc_trusts(m, trustTable);
	  
	  //	  printf("m=%x) weights[%x]=%d slowests[%x]=%d trusts[%d]=%d\n",
	  //			 m, m, weights[m],  m, slowests[m],  m,trusts[m]);
	  if ((weights[m] > 0) && (slowests[m] > 0) && (trusts[m] == true)) {
		possible[m] = true;
		possible_count++;
	  } else {
		possible[m] = false;
	  }
	}
	//	cout << "possible count: " << possible_count << endl;
	if (possible_count == 0) return -1;
	/*	("weights: " << weights << endl;
	cout << "times: " << slowests << endl;
	cout << "fastest: " << fastests << endl;
	cout << "trusts:" << trusts << endl;
	cout << "possible:" << possible << endl;
*/
	if ((possible[all_mask] == true) && (weights[all_mask] <= bridgeStrength))
	  return slowests[all_mask];

	/* int retv = */ go(0, 0);
	
	delete[] weights;
	delete[] slowests;
	delete[] fastest_ones;
	delete[] fastests;
	delete[] trusts;
	delete[] possible;

	return (min_time == 0x7fffffff) ? -1 : min_time;
  }

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) {
	  if ((Case == -1) || (Case == 0)) test_case_0();
	  if ((Case == -1) || (Case == 1)) test_case_1();
	  if ((Case == -1) || (Case == 2)) test_case_2();
	  if ((Case == -1) || (Case == 3)) test_case_3();
	  if ((Case == -1) || (Case == 4)) test_case_4();
	  if ((Case == -1) || (Case == 5)) test_case_5();
	  if ((Case == -1) || (Case == 6)) test_case_6();

	  //  if ((Case == -1) || (Case == 15)) test_case_15();
	  //  if ((Case == -1) || (Case == 16)) test_case_16();
	}
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }

  clock_t start;
  void timer_clear()
  {
	start = clock();
  }
  char *timer()
  {
	clock_t end = clock();
	double interval = (double)(end - start)/CLOCKS_PER_SEC;
	
	char *ret = NULL;
	asprintf(&ret, " (%g msec)", interval*1000);
	return ret;
  }
  void verify_case(int Case, const int &Expected, const int &Received) {
	cerr << "Test Case #" << Case << "...";
	if (Expected == Received)
	  cerr << "PASSED" << timer() << endl;
	else {
	  cerr << "FAILED" << timer() << endl;
	  cerr << "\tExpected: \"" << Expected << '\"' << endl;
	  cerr << "\tReceived: \"" << Received << '\"' << endl;
	}
  }

  void verify_case_(int Case, const int &Expected, const int &Received) {
	cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  
  void test_case_0() { 
	timer_clear();
	int Arr0[] = { 1, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "YYY", "YYY", "YYY" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 9; verify_case(0, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }
  
  void test_case_1() {
	timer_clear();
	int Arr0[] = { 1, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "YYY", "YYY", "NYY" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 10; verify_case(1, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }

  void test_case_2() { 
	timer_clear();
	int Arr0[] = { 1, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 7, 13, 19 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "YYN", "NYY", "YNY" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 19; verify_case(2, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }

  void test_case_3() {
	timer_clear();
	int Arr0[] = { 43 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 23 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "Y" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 42; int Arg4 = -1; verify_case(3, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }
  
  void test_case_4() {
	timer_clear();
	int Arr0[] = { 1, 1, 1 };
	vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
	int Arr1[] = { 7, 13, 19 };
	vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
	string Arr2[] = { "YNN", "NYN", "NNY" };
	vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
	int Arg3 = 3; int Arg4 = -1; verify_case(4, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }

  void test_case_5() {
	timer_clear();
	int Arr0[] = { 3, 3, 6 };
	vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
	int Arr1[] = { 1, 1, 1 };
	vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
	string Arr2[] = { "YYY", "YYY", "YYY" };
	vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
	int Arg3 = 6; int Arg4 = 5; verify_case(5, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }

  void test_case_6() {
	timer_clear();
	int Arr0[] = { 20, 20, 10, 10, 1, 1 };
	vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
	int Arr1[] = { 10, 10, 10, 10, 3, 3 };
	vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
	string Arr2[] = { "YNNNYN", "NYNNYN", "NNYNNY", "NNNYNY", "YYYYYY", "YYYYYY" };
	vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
	int Arg3 = 32; int Arg4 = 23; verify_case(6, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }
  
  void test_case_15() { 
	timer_clear();
	int Arr0[] = { 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1 };
	vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
	int Arr1[] = { 7,13,19, 6,12,18, 5,11,17, 4,10,16, 3 };
	vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
	string Arr2[] = { "YYYYNYYYYYNYY",
					  "NYYYYNYYYYYYY",
					  "YYYYYYYYYYYYY",
					  "YYYYYYYYYYNYY",
					  "YYYYYYYYYYYYY",
					  "YYYYYYYYYYYYY",
					  "YYYYYYYYYYYYY",
					  "YYYYNYYYYYYNN",
					  "YYYYYYYYYYYYY",
					  "YYYYYYYYYYYYY",
					  "YYNNYYYYYYYYY",
					  "YYYYYYYYYYYYY",
					  "YYYNNYYYNYYYY" };
	vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
	int Arg3 = 10; int Arg4 = 28; verify_case(15, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3)); }

  void test_case_16() {
	timer_clear();
	int Arr0[] = { 384,645,965,357,468,358,957,735,382,125,474,385,175 };
	vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
	int Arr1[] = { 375,306,382,496,206,783,683,934,395,385,171,864,476 };
	vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
	string Arr2[] = {
	  "YNNYYNYNYNYYN","NYNYYNNYNNNYN","YNYNNYNNYYNYN","YYNYNYYNNYYYN","NYNNYNNNNNNNN",
	  "YYYNNYNNNYNYN","NNNNNNYNNYYYN","NYYYNNNYNNYYN","NNNYYYNNYNNYN","NYYNNYNNNYNNN",
	  "NNYYNNYNNYYNN","NNNYNNYNNNYYN","NNYNNYNNYNNNY"
	};
	vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
	int Arg3 = 2500; int Arg4 = 2658;
	verify_case(16, Arg4, minimalTime(Arg0, Arg1, Arg2, Arg3));
  }

// END CUT HERE

};

// BEGIN CUT HERE
int main(int argc, char **argv) {
	CavePassage ___test;
	if (argc == 2)
	  ___test.run_test(atoi(argv[1]));
	else
	  ___test.run_test(-1);
}
// END CUT HERE
