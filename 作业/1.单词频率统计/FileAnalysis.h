#pragma once
#include "CommandParser.h"
#include "ResultPacket.h"

class FileAnalysis
{
public:
	FileAnalysis() = delete;
	FileAnalysis(const ParamInfo& target);
	~FileAnalysis();

private:
	ParamInfo infoPacket;
	unordered_set<ControllParam> stauts;
	bool noteStauts;
	shared_ptr<unordered_map<string, unordered_map<ControllParam, int>>> resultMap;
	unordered_map<ControllParam, std::function <int(const string&)>> actionMap;
private:
	vector<string> GetFileContent(string fileName);
	//输入文件名.输出 填充 map content->controll->int
	unordered_map<ControllParam, int> GetFileInfo( const vector<string>& content);
	void InitActionMap();
	void InitResultMap();
public:
	bool GetNoteLineStauts() const;
	void SetNoteLineStauts(bool chose);
	ResultPacket GetResultPacket();
};
