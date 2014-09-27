#pragma once
#include "ParamInfo.h"

class CommandParser
{
public:
	CommandParser() = delete;
	CommandParser(int num, char** args);
	CommandParser(const vector<string>& args);
	~CommandParser() = default;
	enum class PathProperty
	{
		Absolute,
		Relative,
	};
	enum class MatchProperty
	{
		MatchAll,
		MatchOne,
		RecursionMatchAll,
		RecursionMatchOne,
	};
public:
	shared_ptr<vector<string>>								GetFileNameList()									const;
	string													GetDirectoryPath()									const;
	shared_ptr<vector<ControllParam>>						GetControllParamList()								const;
	ParamInfo												GetParamInfoPacket()								const;
private:
	void													InitMatchActionMap();
	PathProperty											GetPathProperty() const;
	MatchProperty											GetMatchProperty() const;
	vector<string>											ArgsWrap(int num, char** args)						const;
	void													SetControllParamList(const vector<string>& args);
	boost::filesystem::path									GetFullPath()										const;
private:
	shared_ptr<vector<string>>													fileNameList;
	string																		directoryPathName;
	PathProperty																pathProperty;
	MatchProperty																matchProperty;
	shared_ptr<vector<ControllParam>>											controllParamList;
	unordered_map < MatchProperty, function < shared_ptr<vector<string>>( const boost::filesystem::path&) >> matchActionMap;
public:
	static unordered_map<string, ControllParam> paramMap;
	static void									InitParamMap();
};
