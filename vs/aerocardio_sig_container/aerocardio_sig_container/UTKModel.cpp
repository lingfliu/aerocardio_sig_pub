#include "stdafx.h"
#include "UTKModel.h"

int UTKModel::getDataAt(int index) {
	if (index < dataLen) {
		return data[index];
	}
	else {
		return 0;
	}
}

void UTKModel::setData(int *data, int dataLen) {
	this->data = data;
	this->dataLen = dataLen;
}


UTKModel::UTKModel(int *data, int dataLen)
{
	if (data != NULL) {
		this->data = data;
		this->dataLen = dataLen;
	}
	else {
		this->data = NULL;
		this->dataLen = -1;
	}

}
UTKModel::UTKModel()
{
	data = NULL;
	dataLen = -1;
}

UTKModel ::~UTKModel()
{
	if (data != NULL) {
		free(data);
	}
	data = NULL;
	dataLen = -1;
}