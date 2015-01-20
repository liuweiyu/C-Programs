#include "Test.h"
#include <iostream>
using namespace std;

Test::Test(void)
{
	attrNum = 0;
	predictSuccessNum = 0;
	predictSuccessPercentage = 0;
}


Test::~Test(void)
{
}

/*
@function: store incoming data into testData
@parameters: element: new line
@return: no return value
*/
void Test::GetNewData(strVector element){
	testData.insert(testData.end(), element);
}

/*
@function: caculate the proability of lable's each possible value in each testing instance
@parameters: attrClassifiers: attributes' classifiers
			 lableClassifier: lable's classifier
@return: no return value
*/
void Test::PredictResults(vector<AttrClassifier*>* attrClassifiers, LableClassifier* lableClassifier){
	attrNum = attrClassifiers->size();
	
	ofstream file;
	file.open(OUTPUT_FILE);
	if(!file.is_open()){
		cout << "Problem with opeing file " << OUTPUT_FILE <<endl;
		return;
	}else{		
		//iterate each testing instance and caculate the result
		int testDataLen = testData.size();
		for(int i = 0; i < testDataLen; i++){			
			strVector curElement = testData.at(i);
			PrintHeader(i, curElement, file);

			innerFMap* priorProMap = lableClassifier->GetPriorPro();
			CaculateCurInstnPro(attrClassifiers, priorProMap, curElement, file);	

			file << endl;
		}		
		
		//get the percentage of successful prediction and write it into result file
		predictSuccessPercentage = (double)predictSuccessNum/(double)testDataLen;
		file << "The percentage of successful prediction is " << predictSuccessPercentage << endl;
		file.close();

		cout << "Result file has been successfully generated." << endl;		
	}
}

/*
@function: caculate the probability of lable's each possible value for one instance 
@parameters: attrClassifiers: attributes' classifiers
			 priorProMap: priorProbability map
			 file: result file writing stream
@return: no return value
*/
void Test::CaculateCurInstnPro(vector<AttrClassifier*>* attrClassifiers, innerFMap*priorProMap, strVector curElement, ofstream& file){
	innerFMap lableInstanAttrProProductMap;
	double instanProAllLableSum = 0;
	//iterate lable's each possible value, caculate P(Y=Yk)*P(X1|Y=Yk)*...*P(X8|Y=Yk) and (j)P(Y=Yj)*P(X1|Y=Yj)*...*P(X8|Y=Yj)
	for(innerFMap::iterator i = priorProMap->begin(); i != priorProMap->end(); i++){
		string lableValue = i->first;
		double curLablePro = i->second;
		//caculate P(X1|Y=Yk)*...*P(X8|Y=Yk)
		double curAttrsProProduct = CalculateCurInstanceProGivenLable(attrClassifiers, curElement, lableValue);
		double curInstancePro = curLablePro*curAttrsProProduct;

		lableInstanAttrProProductMap.insert(pair<string, double>(lableValue, curInstancePro));
		instanProAllLableSum += curInstancePro;				
	}
	
	//divide each P(Y=Yk)*P(X1|Y=Yk)*...*P(X8|Y=Yk) by (j)P(Y=Yj)*P(X1|Y=Yj)*...*P(X8|Y=Yj) and get the final result
	DivideProductByCurInstAllLablesPro(&lableInstanAttrProProductMap, instanProAllLableSum, curElement, file);
}

/*
@function: Divide each P(Y=Yk)*P(X1|Y=Yk)*...*P(X8|Y=Yk) by (j)P(Y=Yj)*P(X1|Y=Yj)*...*P(X8|Y=Yj) and get the final result
@parameters: lableInstanAttrProProductMap: <Yk, P(Y=Yk)*P(X1|Y=Yk)*...*P(X8|Y=Yk)>
@return: no return value
*/
void Test::DivideProductByCurInstAllLablesPro(innerFMap* lableInstanAttrProProductMap, double instanProAllLableSum, strVector curElement, ofstream& file){
	innerFMap lableCurInstanProMap;
	double maxLablePro = 0;
	string maxPossibleLable = "";
	for(innerFMap::iterator j = lableInstanAttrProProductMap->begin(); j != lableInstanAttrProProductMap->end(); j++){
		string lableValue = j->first;
		double instanceProGivenLable = j->second;
		double instancePro = instanceProGivenLable/instanProAllLableSum;
		lableCurInstanProMap.insert(pair<string, double>(lableValue, instancePro));
		if(instancePro > maxLablePro){
			maxLablePro = instancePro;
			maxPossibleLable = lableValue;
		}
		file << "      " << lableValue << "             " << instancePro << endl;
	}

	//add final result into member variable		
	addCurInstantProMapIntoAllInstanProMap(&lableCurInstanProMap, curElement);
	string curLableValue = curElement.at(attrNum);
	if(maxPossibleLable == curLableValue){
		predictSuccessNum++;
	}
}

/*
@function: caculate P(X1|Y=Yk)*...*P(X8|Y=Yk)
@parameters: attrClassifiers: attributes' classifiers
			 curElement: current testing instance
			 lableValue: lable's value, Yk
@return: result of P(X1|Y=Yk)*...*P(X8|Y=Yk)
*/
double Test::CalculateCurInstanceProGivenLable(vector<AttrClassifier*>* attrClassifiers, strVector curElement, string lableValue){
	double curInstanceProGivenLable = 1;
	//iterate each attribute's value
	for(int i = 0; i < attrNum; i++){
		string curAttrValue = curElement.at(i);
		//get the probability of current lable's value and attribute's value
		double curAttrLablePro = (attrClassifiers->at(i))->GetCertainAttrCertainLablePro(curAttrValue, lableValue);
		curInstanceProGivenLable =  curInstanceProGivenLable * curAttrLablePro;
	}
	return curInstanceProGivenLable;
}

/*
@function: add final result into memeber variable, instanLableProMap
@parameters: lableCurInstanProMap: current instance's prediction result
			 curElement: current testing instance
@return: no return value
*/
void Test::addCurInstantProMapIntoAllInstanProMap(innerFMap* lableCurInstanProMap, strVector curElement){
	string curInstanAttrsValue = "";
	for(int k = 0; k < attrNum; k++){
		curInstanAttrsValue += curElement.at(k);
	}

	instanLableProMap.insert(pair<string,innerFMap>(curInstanAttrsValue, *lableCurInstanProMap));
}

/*
@function: print header info for each instance
@parameters: index: index of current instance
			 curInstance: current instance
			 file: result file's writing stream
@return: no return result
*/
void Test::PrintHeader(int index, strVector curInstance, ofstream& file){
	//get attributes' value for printing
	string attrValues = "";
	for(int i = 0; i < attrNum; i++){
		attrValues += curInstance.at(i);
		if(i != attrNum - 1){
			attrValues += ", ";
		}		
	}

	string lableValue = curInstance.at(attrNum);

	file << index << "th instance:" <<endl
		 << "Its attributes' values are: " << attrValues << endl
		 << "Its lable's value is: " << lableValue << endl
		 << "Label's Value #### Probability" << endl;
}
