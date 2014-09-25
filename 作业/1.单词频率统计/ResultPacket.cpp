#include "ResultPacket.h"
unordered_map<ControllParam, string> ResultPacket::enumToStringMap =
{
	{ ControllParam::Char, "�ַ���" },
	{ ControllParam::CodeLine, "��������" },
	{ ControllParam::EmptyLine, "������" },
	{ ControllParam::NoteLine, "ע������" },
	{ ControllParam::RecursionPrint, "�ݹ��ӡĿ¼" },
	{ ControllParam::SumLine, "������" },
	{ ControllParam::Word, "������" },
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
		cout << "�ļ�·��:" << nameIter.first << endl;
		for (auto& elementIter : nameIter.second)
		{
			cout << enumToStringMap[elementIter.first] << ": " << elementIter.second << endl;
		}
	}
}