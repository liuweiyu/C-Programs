#include "DiscreteAttrClassifier.h"
#include <algorithm>
#include <iostream>
#include <fstream>

DiscreteAttrClassifier::DiscreteAttrClassifier(string sAttrName):AttrClassifier(sAttrName)
{
	attrPossibleValueNum = 0;
}


DiscreteAttrClassifier::~DiscreteAttrClassifier(void)
{
}

/*
@parameters: attr: attribute's value; lable: lable's value
@function: storing new data into lableAttrCountMap and keep attributes' all possible values into attrPossibleValues.
@base function: Classifier.GetNewData(string attr, string lable) 
@return: no return value
*/
void DiscreteAttrClassifier::GetNewData(string attr, string lable){
	AttrClassifier::GetNewData(attr, lable);

	if(find(attrPossibleValues.begin(), attrPossibleValues.end(), attr) == attrPossibleValues.end()){
		attrPossibleValues.insert(attrPossibleValues.begin(), attr);
		attrPossibleValueNum++;
	}
}

/*
@parameters:lableClassifier: lableClassifier list
@function: maximum likelihood with Laplace smoothing estimates attribute's probability distribution under lable's all possible values
@overrided method: Classifier.EstimateAttrProbability(LableClassifier* lableClassifier, ofstream& file)
@return: no return value
*/
void DiscreteAttrClassifier::EstimateAttrProbability(LableClassifier* lableClassifier){
	string lableName = lableClassifier->GetLableName();
	innerIMap* lableCountMap = lableClassifier->GetLableCountMap();

	//iterate outter Map of lableAttrCountMap
	for(outerIMap::iterator i = lableAttrCountMap.begin(); i != lableAttrCountMap.end(); i++){
		string lableValue = i->first;
		innerIMap &im = i->second;
		int curLabelCount = lableCountMap->at(lableValue);
		EstimateNonExistingAttrValue(lableValue, im, curLabelCount);

		//iterate inner Map of lableAttrCountMap
		for(innerIMap::iterator ii = im.begin(); ii!=im.end(); ii++){
			string attrValue = ii->first;
			int count = ii->second;
			MaximumLikelihoodLaplaceSmoothingAttrPro(attrValue, lableValue, count, curLabelCount);
		}
	}
}

/*
@parameters: lable: lable's current value
			 im: innerMap related to the key of a lable's current value in lableAttrCountMap
			 curLableCount: number of records with lable's current value
@function: maximum likelihood with Laplace smoothing estimates attribute's non-exsiting value under certain lable's value
@return: no return value
*/
void DiscreteAttrClassifier::EstimateNonExistingAttrValue(string lable, innerIMap im, int curLabelCount){
	if(im.size() != attrPossibleValueNum){
		for(int i = 0; i < attrPossibleValueNum; i++){
			string curAttrPossibleValue = attrPossibleValues.at(i);
			if(im.find(curAttrPossibleValue) == im.end()){
				MaximumLikelihoodLaplaceSmoothingAttrPro(curAttrPossibleValue, lable, 0, curLabelCount);
			}
		}
	}
}

/*
@parameters: attrValue: attribute's current value
			 lableValue: lable's current value
			 curAttrCount: number of records with attribute's current value and lable's current value
			 curLableCount: number of records with lable's current value
@function: caculate the probability of attribute's certain value given lable's certain value
@return: no return value
*/
void DiscreteAttrClassifier::MaximumLikelihoodLaplaceSmoothingAttrPro(string attrValue, string lableValue, 
	int curAttrCount, int curLabelCount){
	double curAttrP = (double)(curAttrCount+1)/(double)(curLabelCount+attrPossibleValueNum);
		
	if(lableAttrProbability.find(lableValue) != lableAttrProbability.end()){
		innerFMap* curAttrProMap = &(lableAttrProbability.at(lableValue));
		curAttrProMap->insert(pair<string, double>(attrValue, curAttrP));
		lableAttrProbability.insert(pair<string, innerFMap>(lableValue, *curAttrProMap));
	}else{
		innerFMap tempAttrProMap;
		tempAttrProMap.insert(pair<string, double>(attrValue, curAttrP));
		lableAttrProbability.insert(pair<string, innerFMap>(lableValue, tempAttrProMap));
	}
}

/*
@parameters: attrValue: attribute's value
			 lableValue: lable's value
@function: return the probability of certain attribute's value and label's certain value
@return: the probability of certain attribute's value and label's certain value
*/
double DiscreteAttrClassifier::GetCertainAttrCertainLablePro(string attrValue, string lableValue){
	return (lableAttrProbability.at(lableValue)).at(attrValue);
}
