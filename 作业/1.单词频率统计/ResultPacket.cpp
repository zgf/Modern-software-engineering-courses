#include "ResultPacket.h"
unordered_map<ControllParam, string> ResultPacket::enumToStringMap =
{
	{ ControllParam::Char, "字符数" },
	{ ControllParam::CodeLine, "代码行数" },
	{ ControllParam::EmptyLine, "空行数" },
	{ ControllParam::NoteLine, "注释行数" },
	{ ControllParam::RecursionPrint, "递归打印目录" },
	{ ControllParam::SumLine, "总行数" },
	{ ControllParam::Word, "单词数" },
};

ResultPacket::ResultPacket(const shared_ptr<unordered_map<string, unordered_map<ControllParam, int>>>& target) :resultMap(target)
{
}

ResultPacket::~ResultPacket()
{
}
void ResultPacket::ShowResult()
{
	for (auto& nameIter : *resultMap)
	{
		cout << "文件路径:" << nameIter.first << endl;
		for (auto& elementIter : nameIter.second)
		{
			cout << enumToStringMap[elementIter.first] << ": " << elementIter.second << endl;
		}
	}
}