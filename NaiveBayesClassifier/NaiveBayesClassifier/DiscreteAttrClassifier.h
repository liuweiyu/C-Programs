/*
@description: Classifier for a discrete attribute
@base class: Classifier
*/

#ifndef DCLASSIFIER_H
#define DCLASSIFIER_H

#include "AttrClassifier.h"
#include "LableClassifier.h"
#include "DataTypes.h"

#include <string>
#include <fstream>
using namespace std;
using namespace customizedTypes;

class DiscreteAttrClassifier : public AttrClassifier
{
public:
	DiscreteAttrClassifier(string sAttrName);
	~DiscreteAttrClassifier(void);

	//extended from GetNewData in base class: storing new data into lableAttrCountMap and keep attributes' all possible values into attrPossibleValues
	void GetNewData(string attr, string lable);

	//maximum likelihood with Laplace smoothing estimates attribute's probability distribution under lable's all possible values 
	void EstimateAttrProbability(LableClassifier* lableClassifier);
	//get the probability of attribute's certain value and lable's certain value
	double GetCertainAttrCertainLablePro(string attrValue, string lableValue);

private:
	//map for attribute's probability distribution among lable's all possible values:<lable's value, <attribute's value, probability>>
	outerFMap lableAttrProbability;	
	//vector for attributes' all possible values
	strVector attrPossibleValues;
	//number of attributes' possible values
	int attrPossibleValueNum;

	//maximum likelihood with Laplace smoothing estimates attribute's non-exsiting value under certain lable's value
	void EstimateNonExistingAttrValue(string lable, innerIMap im , int curLabelCount);
	//caculate the probability of attribute's certain value given lable's certain value
	void MaximumLikelihoodLaplaceSmoothingAttrPro(string attrValue, string lableValue, int curAttrCount, int curLabelCount);		
};

#endif
