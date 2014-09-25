#pragma once
#include "forward.h"
#include "ControllParam.h"
 class ParamInfo
{
public:
	ParamInfo() = default;
	~ParamInfo() = default;
public:
	shared_ptr<vector<string>> fileNameList;
	shared_ptr<vector<ControllParam>> ControllParamList;
};