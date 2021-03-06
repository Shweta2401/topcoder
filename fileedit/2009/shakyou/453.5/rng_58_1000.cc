#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

typedef long long ll;

ll precalc[100] = {38230451,38230365,38230565,38230195,38230717,38230288,38230358,38230621,38230592,38230401,38230316,38230428,38230478,38230591,38230656,38230433,38230394,38230388,38230396,38230396,38230429,38230249,38230515,38230623,38230468,38230513,38230543,38230413,38230466,38230442,38230427,38230418,38230418,38230307,38230378,38230261,38230293,38230473,38230492,38230491,38230419,38230499,38230530,38230357,38230748,38230444,38230457,38230622,38230506,38230436,38230447,38230433,38230534,38230394,38230499,38230365,38230392,38230340,38230564,38230285,38230395,38230491,38230461,38230293,38230466,38230355,38230426,38230529,38230374,38230486,38230392,38230444,38230449,38230453,38230598,38230486,38230482,38230613,38230439,38230484,38230491,38230514,38230482,38230343,38230570,38230662,38230355,38230425,38230485,38230435,38230538,38230457,38230393,38230426,38230503,38230535,38230413,38230535,38230376,38230339};

#define MOD 100000000ll

vector <ll> small,big;

class TheAlmostLuckyNumbers{
  public:
  
  ll gcd(ll x, ll y){
    return x ? gcd(y%x,x) : y;
  }
  
  ll lcm(ll x, ll y){
    return x / gcd(x,y) * y;
  }
  
  void dfs(int digits, ll N){
    if(N != 0 && (N%4 != 0 || N == 4) && (N%7 != 0 || N == 7)){
      if(digits <= 4) small.push_back(N);
      else big.push_back(N);
    }
    if(digits == 10) return;
    dfs(digits+1,N*10+4);
    dfs(digits+1,N*10+7);
  }
  
  ll func(ll low, ll high){
    int sz=small.size(),i,j;
    ll ans = 0;
    
    REP(i,(1<<sz)) if(i != 0){
      int cnt = __builtin_popcount(i);
      ll D = 1;
      REP(j,sz) if(i&(1<<j)){
        D = lcm(D,small[j]);
        if(D > high) break;
      }
      ll tmp = high / D - (low - 1) / D;
      if(cnt%2 == 1) ans += tmp; else ans -= tmp;
    }
    
    REP(i,big.size()) for(ll x=big[i];x<=high;x+=big[i]){
      if(x < low) continue;
      bool flag = true;
      REP(j,small.size()) if(x % small[j] == 0) {flag = false; break;}
      if(!flag) continue;
      REP(j,i) if(x % big[j] == 0) {flag = false; break;}
      if(!flag) continue;
      ans++;
    }
    
    return ans;
  }
  
  ll count2(ll high){
    if(high == 0) return 0;
    
    ll low=1,ans=0;
    int i=0;
    
    while(1){
      if(low + MOD > high) break;
      low += MOD; ans += precalc[i]; i++;
    }
    
    ans += func(low,high);
    return ans;
  }

  long long count(long long low, long long high){
    dfs(0,0);
    ll ans = count2(high) - count2(low-1);
    return ans;
  }

};
