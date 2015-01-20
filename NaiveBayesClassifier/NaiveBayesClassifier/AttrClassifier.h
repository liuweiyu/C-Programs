/*
@author: Liu Weiyu
@data: 06/09/2014
@decription: classifier for an attribute.
*/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "DataTypes.h"
#include "LableClassifier.h"

#include<string>
#include<map>
using namespace std;
using namespace customizedTypes;

class AttrClassifier
{
public:	
	AttrClassifier(string sAttrName);
	~AttrClassifier(void);

	//insert data, including lable's value, attribute's value and the quantity of this kind of record, into lableAttrCountMap
	virtual void GetNewData(string attr, string lable);
	//estimate attribute's probability distribution given lable's each possible value
	virtual void EstimateAttrProbability(LableClassifier* lableClassifier){};
	//get probability of certain attribute's value and lable's certain value
	virtual double GetCertainAttrCertainLablePro(string attrValue, string lableValue){return 0;};

protected:
	//raw data:<lable's value, <attribute's value, amount>>
	outerIMap lableAttrCountMap;

	//number of total records
	int numOfElements;
	//attribute's name
	string attrName;

	//update lableAttrCountMap with new data(lable's value, attribute's value)
	void UpdateLableAttrCountMap(string attr, string lable);
};

#endif

