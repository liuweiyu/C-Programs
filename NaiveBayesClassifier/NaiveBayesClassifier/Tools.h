/*
@function: common tools
*/

#include<string>
#include<vector>
#include <cstring>
using namespace std;

class Tools
{
public:
	Tools(void);
	~Tools(void);

	//split a string into a vector by a token
	vector<string> StringSplit(string& s, const char* token);
};