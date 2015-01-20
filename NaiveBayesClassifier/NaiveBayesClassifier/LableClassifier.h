/*
@function: classifier for a discrete lable
*/

#ifndef LABLE_CLASSIFIER_H
#define LABLE_CLASSIFIER_H

#include "DataTypes.h"
#include <string>
#include <fstream>
using namespace std;
using namespace customizedTypes;

class LableClassifier
{
public:
	LableClassifier(string name);
	~LableClassifier(void);

	//store lable's current value into lableCountMap
	void GetNewData(string lable);
	//maximum likelihood estimater for prior probability
	void EstimatePriorProbability();

	//get lable's name
	string GetLableName();
	//get a pointer to lableCountMap
	innerIMap* GetLableCountMap();
	//get a pointer to priorProbability
	innerFMap* GetPriorPro();
	
private:
	//<lable's value, quantity of records with lable's this value>
	innerIMap lableCountMap;	
	//lable's name
	string lableName;
	//<lable's value, probability>
	innerFMap priorProbability;
	//total number of the records
	int numOfElements;
	
	//maximum likelihood estimate prior probability of lable's certain value and write result into result file
	void MaximumLikelihoodPriorPro(string lable, int count);
	//write header info into result file
	void PrintPriorProHeader();	
};

#endif