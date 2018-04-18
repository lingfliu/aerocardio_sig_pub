#pragma once

class __declspec(dllexport) UTKMModel {
public:
	int *data;
	int dataLen;
	UTKMModel();
	~UTKMModel();
	static UTKMModel* getInstance();
};
static UTKMModel *utk_model_instance;
