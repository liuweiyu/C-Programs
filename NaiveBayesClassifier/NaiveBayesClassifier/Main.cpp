#include "Reader.h"
#include "DiscreteAttrClassifier.h"
#include "ContinuousAttrClassifier.h"
#include "LableClassifier.h"
#include "Test.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main(){
	//read attrConfig file
	Reader r;
	outerStrVector* nameAndType = r.GetAttrConfig();
	int attrAndLableNum = r.GetAttrNum();

	//create attrClassifier object for each attribute
	vector<AttrClassifier*> attrClassifiers;
	for(int i = 0; i < attrAndLableNum - 1; i++){
		string name = (nameAndType->at(i)).at(0);
		string type = (nameAndType->at(i)).at(1);

		if(type == "d"){			
			attrClassifiers.push_back(new DiscreteAttrClassifier(name));
		}else if(type == "c"){
			attrClassifiers.push_back(new ContinuousAttrClassifier(name));
		}else{
			cout << "Illegal Attr Type " << type <<endl;
		}
	}	
	//create lableClassifier for lable
	LableClassifier lableClassifier(nameAndType->at(attrAndLableNum - 1).at(0));
	//create a Test object
	Test test;
	cout << "Successfully created classifiers for all attribute, lable and Test object." << endl;

	//load raw data from file into each related classifier object
	r.LoadTrainDataAndTestData(&attrClassifiers, &lableClassifier, &test);
	cout << "Successfully loaded train data and test data into related objects." << endl;

	//train data: get major parameters for attributes
	for(int k = 0; k < attrAndLableNum - 1; k++){
			(attrClassifiers.at(k))->EstimateAttrProbability(&lableClassifier);
	}
	//estimate prior probability
	lableClassifier.EstimatePriorProbability();
	cout << "Successfully trained data." << endl;

	//predict the probability of lable's each possible value in each testing instance based on trained data
	test.PredictResults(&attrClassifiers, &lableClassifier);		
	cout << "Successfully predicted data and genertaed result file." << endl;

	system("pause");
	return 0;
}