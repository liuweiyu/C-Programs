/*
@function: classifier for a continuous attribute
@base class: Classifier
*/

#ifndef CCLASSIFIER_H
#define CCLASSIFIER_H

#include "AttrClassifier.h"
#include <string>
#include <map>
#include <fstream>
using namespace std;

class ContinuousAttrClassifier : public AttrClassifier
{
public:
	ContinuousAttrClassifier(string sAttrName);
	~ContinuousAttrClassifier(void);

	//maximum likelihood estimator used to estimate mean and standard deviation of attribute's values under lable's each possible value
	void EstimateAttrProbability(LableClassifier* lableClassifier);	
	//get the probability of attribute's certain value and lable's certain value
	double GetCertainAttrCertainLablePro(string attrValue, string lableValue);

private:
	//map for attribute's mean under lable's each possible value: <lable's value, attribute's mean given lable's present value>
	innerFMap attrMeanMap;
	//map for attribute's SD under lable's each possible value: <lable's value, attribute's SD given lable's present value>
	innerFMap attrStandardDeviationMap;

	//maximum likelihood estimator used to estimate mean of attribute's values under lable's each possible value
	void EstimateAttrMean(string lableName, innerIMap* lableCountMap);
	//maximum likelihood estimator used to estimate standard deviation of attribute's values under lable's each possible value
	void EstimateStandardDeviation(string lableName, innerIMap* lableCountMap);
};

#endif