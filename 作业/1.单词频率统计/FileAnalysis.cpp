#include "FileAnalysis.h"
FileAnalysis::FileAnalysis(const ParamInfo& target) :infoPacket(target), noteStauts(false),
resultMap(make_shared<unordered_map<string, unordered_map<ControllParam, int>>>())
{
	for(auto& Iter : *(infoPacket.ControllParamList))
	{
		stauts.insert(Iter);
	}
	InitActionMap();
	InitResultMap();
}
void FileAnalysis::SetNoteLineStauts(bool chose)
{
	noteStauts = chose;
}
bool FileAnalysis::GetNoteLineStauts() const
{
	return noteStauts;
}
void FileAnalysis::InitActionMap()
{
	actionMap.insert(make_pair(ControllParam::Char, [this](const string& lineContent)->int
	{
		//会有换行符
		return lineContent.size()+1;
	}));
	actionMap.insert(make_pair(ControllParam::Word, [this](const string& lineContent)->int
	{
		auto count = 0;
		regex regex_parser(R"(\b\w+\b)");
		smatch match_result;
		string Line = lineContent;
		while(regex_search(Line, match_result, regex_parser))
		{
			count += match_result.size();
			Line = match_result.suffix().str();
		}
		return count;
	}));
	actionMap.insert(make_pair(ControllParam::SumLine, [this](const string& lineContent)->int
	{
		return 1;
	}));
	actionMap.insert(make_pair(ControllParam::NoteLine, [this](const string& lineContent)->int
	{
		//这里效率低了
		if(this->GetNoteLineStauts() == true)
		{
			//处在注释中
			//需要判断注释是否结束
			if(lineContent.find("*/") != lineContent.npos)
			{
				this->SetNoteLineStauts(false);
			}
		}
		else if(lineContent.find("/*") != lineContent.npos)
		{
			this->SetNoteLineStauts(true);
		}
		else if(lineContent.find("//") == lineContent.npos)
		{
			return 0;
		}
		return 1;
	}));
	actionMap.insert(make_pair(ControllParam::EmptyLine, [this](const string& lineContent)->int
	{
		if(lineContent.size() != 0)
		{
			auto count = 0;
			for(size_t index = 0; index < lineContent.size(); index++)
			{
				if(lineContent[index] != ' ' || lineContent[index] != '	')
				{
					count++;
				}
				if(count > 1)
				{
					return 0;
				}
			}
		}

		return 1;
	}));
	actionMap.insert(make_pair(ControllParam::CodeLine, [this](const string& lineContent)->int
	{
		return actionMap[ControllParam::EmptyLine](lineContent) ? 0 : actionMap[ControllParam::NoteLine](lineContent) ? 0 : 1;
	}));
}

void FileAnalysis::InitResultMap()
{
	for(auto& name : *infoPacket.fileNameList)
	{
		resultMap->insert(make_pair(name, GetFileInfo(GetFileContent(name))));
	}
}
FileAnalysis::~FileAnalysis()
{
}

vector<string> FileAnalysis::GetFileContent(string fileName)
{
	ifstream input(fileName);
	if(!input.is_open())
	{
		throw exception("file not found or can't open");
	}
	vector<string> result;
	char* lineBuff = new char[1024];
	while(!input.peek() == input.eof())
	{
		input.getline(lineBuff, 1024);
		result.emplace_back(lineBuff);
		memset(lineBuff, 0, 1024);
	}
	input.close();
	return move(result);
}
//输入文件名.输出 填充 map Content->controll->int
unordered_map<ControllParam, int> FileAnalysis::GetFileInfo(const vector<string>& content)
{
	unordered_map<ControllParam, int> result;
	for(auto& Iter : stauts)
	{
		result.insert(make_pair(Iter, 0));
	}

	for(auto& lineIter : content)
	{
		for(auto& controllIter : result)
		{
			controllIter.second += actionMap[controllIter.first](lineIter);
		}
	}
	//去除最后一个换行符
	if(stauts.find(ControllParam::Char)!=stauts.end())
	{
		--result[ControllParam::Char];
	}
	return move(result);
}
ResultPacket FileAnalysis::GetResultPacket()
{
	ResultPacket result;
	result.resultMap = this->resultMap;
	return move(result);
}