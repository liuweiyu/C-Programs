/*
@function: object for testing
*/

#ifndef TEST_H
#define TEST_H

#define OUTPUT_FILE "result.data"

#include "DataTypes.h"
#include "AttrClassifier.h"
using namespace customizedTypes;

class Test
{
public:
	Test(void);
	~Test(void);

	//caculate the probability of lable's each possible value in each testing instance and write the result into file
	void PredictResults(vector<AttrClassifier*>* attrClassifiers, LableClassifier* lableClassifier);
	//store test data into member variable testData
	void GetNewData(strVector element);

private:
	//number of attributes
	int attrNum;
	//<<each element in each line of the raw data for testing>>
	outerStrVector testData;
	//final result:<instance, lable's value, probability>
	outerFMap instanLableProMap;
	//number of instance predicted successfully
	int predictSuccessNum;
	//percentage of successful prediction
	double predictSuccessPercentage;

	//caculate the probability of lable's each possible value given current instance
	void CaculateCurInstnPro(vector<AttrClassifier*>* attrClassifiers, innerFMap*priorProMap, strVector curElement, ofstream& file);
	//divide numerator by denominator in formula 2
	void DivideProductByCurInstAllLablesPro(innerFMap* lableInstanAttrProProductMap, double instanProAllLableSum, strVector curElement, ofstream& file);
	//caculate the product of each attribute's probability given lable's value in one instance
	double CalculateCurInstanceProGivenLable(vector<AttrClassifier*>* attrClassifiers, strVector curElement, string lableValue);
	//add result into memeber variable instanLableProMap
	void addCurInstantProMapIntoAllInstanProMap(innerFMap* lableCurInstanProMap, strVector curElement);

	//print header info for each testing instance
	void PrintHeader(int index, strVector curInstance, ofstream& file);
};

#endif
