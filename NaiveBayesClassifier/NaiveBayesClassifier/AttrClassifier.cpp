#include "AttrClassifier.h"

#include <string>
#include <map>
#include <iostream>
using namespace std;

AttrClassifier::AttrClassifier(string sAttrName)
{
	attrName = sAttrName;
	numOfElements = 0;
}

AttrClassifier::~AttrClassifier(void)
{
}

/*
@parameters: attr: attribute's value
             lable: lable's value
@function: insert current attribute and lable's value and the quantity of this kind's record(s) into lableAttrCountMap
@return: no return value
*/
void AttrClassifier::GetNewData(string attr, string lable){
	if(lableAttrCountMap.find(lable) != lableAttrCountMap.end()){
		innerIMap* curAttrCountMap = &(lableAttrCountMap.at(lable));
		if(curAttrCountMap->find(attr) != curAttrCountMap->end()){
			curAttrCountMap->at(attr) += 1;
		}else{
			curAttrCountMap->insert(pair<string, int>(attr, 1));
			lableAttrCountMap.insert(pair<string, map<string, int>>(lable, *curAttrCountMap));
		}
	}else{
		innerIMap tempAttrCountMap;
		tempAttrCountMap.insert(pair<string, int>(attr, 1));
		lableAttrCountMap.insert(pair<string, map<string, int>>(lable, tempAttrCountMap));
	}

	numOfElements++;
}