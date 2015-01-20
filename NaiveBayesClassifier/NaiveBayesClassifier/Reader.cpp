#include "Reader.h"
#include "Tools.h"

#include <iostream>
#include <fstream>
using namespace std;

Reader::Reader(void)
{	
	LoadConfigFile(attrConfig, ATTRTYPEINFO_FILE, 2);
	attrAndLableNum = attrConfig.size();
	LoadRawDataFile(rawData, RAWDATA_FILE);
}


Reader::~Reader(void)
{
}

/*
@parameters: result: attrConfig map
			 fileName:  file's name
			 elemNum: expected amount of elements in each line
@function: load data from attrConfig file into attrConfig map
@return:
*/
void Reader::LoadConfigFile(outerStrVector& result, string fileName, int elemNum){	
	Tools tools;
	ifstream file;
	file.open(fileName);
	if(!file.is_open()){
		cout << "Problem opening file " << fileName << endl;
		return;
	}
	int line = 1;
	string curLine = "";
	while(getline(file, curLine)){
		strVector elements = tools.StringSplit(curLine, SPLIT_TOKEN);
		if(elements.size() != elemNum){
			cout << "Incomplete record at line "
				 << line << endl;
		}else{
			result.push_back(elements);
		}	
		line++;
	}

	cout << "Successfully loaded attrConfig file." << endl;
	file.close();
}

/*
@function: load data from "abalone.data" file to member variable rawData, and set rawDataLen, trainDataLen and testDataLen
@parameters: rawData: member variable
			 fileName: raw data file name
@return: no return value
*/
void Reader::LoadRawDataFile(outerStrVector& rawData, string fileName){
	Tools tools;
	ifstream file;
	file.open(RAWDATA_FILE);
	if(!file.is_open()){
		cout << "Problem opening file " << RAWDATA_FILE << endl;
		return;
	}else{
		int line = 0;
		string curLine = "";
		while(getline(file, curLine)){
			strVector elements = tools.StringSplit(curLine, SPLIT_TOKEN);
			if(elements.size() != attrAndLableNum){
				cout << "Incomplete record at line " << line + 1 << " in file " << RAWDATA_FILE << endl;
			}else{
				rawData.insert(rawData.end(), elements);				
			}
			line++;
		}
		rawDataLen = line;
		trainDataLen = (int)(rawDataLen*TRAIN_DATA_PERCENTAGE);
		testDataLen = rawDataLen - trainDataLen;
	}
}

/*
@parameters: attrClassifiers: array of all attributes' classifier
			 lableClassifier: lable's classifier
			 test: Test object
@function: load raw data from raw data file "abalone.data" to attributes' classifiers, lable's classifier and test object
@return: no return value
*/
void Reader::LoadTrainDataAndTestData(vector<AttrClassifier*>* attrClassifiers, LableClassifier* lableClassifier, Test* test){
	//set the first percentage of TRAIN_DATA_PERCENTAGE to train data
	for(int i = 0; i < trainDataLen; i++){
		strVector elements = rawData.at(i);
		string curLableValue = elements[attrAndLableNum - 1];
		for(int i = 0; i < attrAndLableNum-1; i++){
			string cur = elements.at(i);
			(attrClassifiers->at(i))->GetNewData(cur, curLableValue);				
		}
		lableClassifier->GetNewData(curLableValue);
	}	

	//set the rest data as test data
	for(int j = trainDataLen; j < rawDataLen; j++){
		strVector elements = rawData.at(j);
		test->GetNewData(elements);
	}
}

/*
@parameters: none
@function: get pointer to attrConfig map
@return: pointer to attrConfig map
*/
outerStrVector* Reader::GetAttrConfig(){
	return &attrConfig;
}

/*
@parameters: none
@function: get attrNum
@return: attrNum
*/
int Reader::GetAttrNum(){
	return attrAndLableNum;
}