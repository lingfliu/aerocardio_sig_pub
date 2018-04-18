#pragma once
#include <stdio.h>
#include <stdlib.h>

class UTKModel {
public:
	UTKModel ();
	UTKModel(int *data, int dataLen);
	~UTKModel ();
	void setData(int *data, int dataLen);
	int getDataAt(int index);
private:
	int *data;
	int dataLen;

};
