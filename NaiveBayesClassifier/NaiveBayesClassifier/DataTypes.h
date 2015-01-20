/*
@function: definition of a namespace contatining several customized data type
*/

#include <map>
#include <string>
#include <vector>
using namespace std;

namespace customizedTypes{
	typedef map<string, double> innerFMap;
	typedef map<string, innerFMap> outerFMap;

	typedef map<string, int> innerIMap;
	typedef map<string, innerIMap> outerIMap;

	typedef vector<string> strVector;
	typedef vector<vector<string>> outerStrVector;
}