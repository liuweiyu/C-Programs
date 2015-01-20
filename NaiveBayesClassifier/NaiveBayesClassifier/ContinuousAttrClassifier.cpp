#define PI 3.1415926

#include "ContinuousAttrClassifier.h"
#include<string>
#include<math.h>
#include<iostream>
#include<fstream>
using namespace std;

ContinuousAttrClassifier::ContinuousAttrClassifier(string sAttrName):AttrClassifier(sAttrName)
{
}


ContinuousAttrClassifier::~ContinuousAttrClassifier(void)
{
}

/*
@parameters: lableClassifier: lable's classifier list
@function:maximum likelihood estimator used to estimate mean and standard deviation of attribute's values under lable's each possible value
@overided method: Classifier.EstimateAttrProbability(LableClassifier* lableClassifier, ofstream& file)
@return: no return value
*/
void ContinuousAttrClassifier::EstimateAttrProbability(LableClassifier* lableClassifier){
	string lableName = lableClassifier->GetLableName();
	innerIMap* lableCountMap = lableClassifier->GetLableCountMap();	

	EstimateAttrMean(lableName, lableCountMap);
	EstimateStandardDeviation(lableName, lableCountMap);
}

/*
@parameters: lableName: lable's name
			 lableCountMap: <lable's value, records with lable's current value>
@function: maximum likelihood estimator used to estimate mean of attribute's values under lable's each possible value
@return: no return value
*/
void ContinuousAttrClassifier::EstimateAttrMean(string lableName, innerIMap* lableCountMap){
	//iterate outer map of lableAttrCountMap
	for(outerIMap::iterator i = lableAttrCountMap.begin(); i != lableAttrCountMap.end(); i++){
		string lableValue = i->first;
		innerIMap &im = i->second;
		int curLabelCount = lableCountMap->at(lableValue);
		double subTotal = 0;
		int subCount = 0;
		//iterate inner map of lableAttrCountMap
		for(innerIMap::iterator ii = im.begin(); ii!=im.end(); ii++){
			string attrValue = ii->first;
			int count = ii->second;
			subTotal += (double)atof(attrValue.c_str())*(double)count;
			subCount += count;
		}

		//caculate current mean and insert it into attrMeanMap
		double curMean = subTotal/(double)subCount;
		attrMeanMap.insert(pair<string, double>(lableValue, curMean));		
	} 
}

/*
@parameters: lableName: lable's name
			 lableCountMap: <lable's value, records with lable's current value>
@function: maximum likelihood estimator used to estimate standard deviation of attribute's values under lable's each possible value
	       and write result of both mean and SD's distribution into result file
@return: no return value
*/
void ContinuousAttrClassifier::EstimateStandardDeviation(string lableName, innerIMap* lableCountMap){
	//iterate outer map of lableAttrCountMap
	for(outerIMap::iterator i = lableAttrCountMap.begin(); i != lableAttrCountMap.end(); i++){
		string lableValue = i->first;
		innerIMap &im = i->second;
		double curMean = attrMeanMap.at(lableValue);
		double subTotal = 0;
		int subCount = 0;
		//iterate inner map of lableAttrCountMap
		for(innerIMap::iterator ii = im.begin(); ii!=im.end(); ii++){
			string attrValue = ii->first;
			int count = ii->second;
			subTotal += pow(((double)atof(attrValue.c_str()) - (double)curMean), 2)*(double)count;
			subCount += count;
		}

		//caculate current SD and insert it into attrStandardDeviationMap
		double curSD = subTotal/(double)(subCount);
		attrStandardDeviationMap.insert(pair<string, double>(lableValue, curSD));
	} 	
}

/*
@function: get the probability of certain attribute's value and lable's certain value based on Gaussian distribution
@parameters: attrValue: attribute's value
			 lableValue: lable's value
@return: probability of certain attribute's value and lable's certain value
*/
double ContinuousAttrClassifier::GetCertainAttrCertainLablePro(string attrValue, string lableValue){
	double curMean = attrMeanMap.at(lableValue);
	double curSD = attrStandardDeviationMap.at(lableValue);
	//p = exp(-square(x-mean)/(2*SD))/root(2*PI*SD)
	double fAttrValue = (double)atof(attrValue.c_str());
	double exponent = (pow((fAttrValue - curMean), 2)/(2*curSD))*(-1);
	double attrPro = (double)(exp(exponent)/pow(2*PI*curSD, 0.5));
	return attrPro;
}