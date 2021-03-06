#include <string>
#include <vector>
using namespace std;

class BinaryCode {
public:
  vector<string> decode(string message);
};

vector<string>
BinaryCode::decode(string message)
{
	vector<string> result(2);
	
	int len = message.length();
	char decoded[2][len];
	int possible[2] = {1,1};

	decoded[0][0] = 0; decoded[1][0] = 1;
	
	int c = message[0] - '0';
	if (c == 0 || c == 1) decoded[0][1] = c;
	else possible[0] = 0;
	if (c == 1 || c == 2) decoded[1][1] = c - 1;
	else possible[1] = 0;
	
    for (int i=1; i<len-1; i++) {
      c = message[i] - '0';
      for (int t=0; t<2; t++)
        if (possible[t]) {
          int d = c - decoded[t][i] - decoded[t][i-1];
          if (d == 0 || d == 1) decoded[t][i+1] = d;
          else possible[t] = 0;
        }
    }
    
    for (int t=0; t<2; t++) {
      if (possible[t])
        for (int i=0; i<len; i++) {
          int d = decoded[t][i];
          if (d < 0 || 1 < d) { possible[t] = 0; break; }          
          else decoded[t][i] = '0' + d;
        }
      result[t] = possible[t] ? string(decoded[t],len) : "NONE";
    }
    
	return result;
}


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
