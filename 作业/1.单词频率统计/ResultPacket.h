#pragma once
#include "forward.h"
#include "ControllParam.h"
class ResultPacket
{
public:
	ResultPacket() = default;
	ResultPacket(const shared_ptr<unordered_map<string, unordered_map<ControllParam, int>>>& target);

	~ResultPacket();
public:
	shared_ptr<unordered_map<string, unordered_map<ControllParam, int>>> resultMap;
	static unordered_map<ControllParam, string> enumToStringMap;
private:

public:
	void ShowResult();
};
