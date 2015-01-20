#include "Tools.h"

Tools::Tools(void)
{
}


Tools::~Tools(void)
{
}

/*
@parameters: s: string to be splitted
			 token: separator
@funtion: split s by token into a vector<string> type variable
@return: vector with string elements
*/
vector<string> Tools::StringSplit(string& s, const char* token){
	char *cstr, *p, *next_p = NULL;
    vector<string> res;
    cstr = new char[s.size()+1];
    strcpy_s(cstr, s.size()+1, s.c_str());
    p = strtok_s(cstr, token, &next_p);
    while(p!=NULL){
        res.push_back(p);
        p = strtok_s(NULL, token, &next_p);
    }
    return res;
}
