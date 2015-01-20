/*
@function: load data from attribute configuration file and raw data file
*/

#define RAWDATA_FILE "abalone.data"
#define ATTRTYPEINFO_FILE "attrConfig.data"
#define SPLIT_TOKEN ","
#define TRAIN_DATA_PERCENTAGE 0.9

#include <string>
#include <vector>
#include "AttrClassifier.h"
#include "LableClassifier.h"
#include "Test.h"
using namespace std;

class Reader
{
public:
	Reader(void);
	~Reader(void);

	//get a pointer to attrConfig map
	outerStrVector* GetAttrConfig();
	//get attrNum
	int GetAttrNum(); 
	//load raw data from raw data file "abalone.data" to attributes' classifiers, lable's classifier and test object
	void LoadTrainDataAndTestData(vector<AttrClassifier*>* attrClassifiers, LableClassifier* lableClassifier, Test* test);

private:
	//attributes and lable's quantity
	int attrAndLableNum;
	//total length of raw data
	int rawDataLen;
	//length of train data
	int trainDataLen;
	//length of test data
	int testDataLen;

	//<attribute's name, attribute's data type("d" for discrete and "c" continuous)>
	outerStrVector attrConfig;
	//rawData, including train data and test data <<each item in a line in raw data>>>
	outerStrVector rawData;

	//load attributes' name and data type into attrConfig map from attrConfig.data file
	void LoadConfigFile(outerStrVector& result, string fileName, int elemNum);	
	//load raw data from "abalone.data" file to rawData
	void LoadRawDataFile(outerStrVector& rawData, string fileName);
};

