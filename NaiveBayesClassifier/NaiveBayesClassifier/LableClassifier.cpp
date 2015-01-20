#include "LableClassifier.h"
#include <iostream>

LableClassifier::LableClassifier(string name)
{
	lableName = name;
	numOfElements = 0;
}

LableClassifier::~LableClassifier(void)
{
}

/*
@parameters: lable: lable's value
@function: store lable's current value into lableCountMap
@return: no return value
*/
void LableClassifier::GetNewData(string lable){
	if(lableCountMap.find(lable) != lableCountMap.end()){
		lableCountMap.at(lable) += 1;
	}else{
		lableCountMap.insert(pair<string, int>(lable, 1));
	}
	numOfElements++;
}

/*
@parameters: none
@function: maximum likelihood estimater for prior probability
@return: no return value
*/
void LableClassifier::EstimatePriorProbability(){
	for(innerIMap::iterator i = lableCountMap.begin(); i!=lableCountMap.end(); i++){
		string lable = i->first;
		int count = i->second;
		MaximumLikelihoodPriorPro(lable, count);
	}
	cout << "Successfully estimated prior probability." << endl;
}

/*
@parameters: lable: lable's value
			 count: quantity of recordes with lable's this value
@function: maximum likelihood estimate the probability of lable's certain value and write the result into result file
@return: no return value
*/
void LableClassifier::MaximumLikelihoodPriorPro(string lable, int count){
	double curPriorP = (double)count/(double)numOfElements;
	priorProbability.insert(pair<string, double>(lable, curPriorP));
}



/*
@parameters: none
@function: return lable's name
@return: lable's name
*/
string LableClassifier::GetLableName(){
	return lableName;
}

/*
@parameters: none
@function: return the address of lableCountMap
@return: a pointer to lableCountMap
*/
innerIMap* LableClassifier::GetLableCountMap(){
	return &lableCountMap;
}

/*
@parameters: none
@function: get a pointer to priorProbability
@return: a pointer to priorProbability
*/
innerFMap* LableClassifier::GetPriorPro(){
	return &priorProbability;
}