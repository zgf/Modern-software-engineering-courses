#include "FileAnalysis.h"

bool except_eq(unordered_map<string, unordered_map<ControllParam, int>>& result, const unordered_map<string, unordered_map<ControllParam, int>>& except)
{
	vector<bool> test_result;
	for(auto& fileIter : except)
	{
		auto& element = result[fileIter.first];
		auto real_result = vector<pair<ControllParam, int>>(element.begin(), element.end());
		auto except_result = vector<pair<ControllParam, int>>(fileIter.second.begin(), fileIter.second.end());
		std::sort(real_result.begin(), real_result.end());
		std::sort(except_result.begin(), except_result.end());
		auto bool_result = std::equal(real_result.begin(), real_result.end(), except_result.begin());
		if(bool_result == false)
		{
			cout << "文件名:" << fileIter.first << endl;
			for(size_t i = 0; i < real_result.size(); i++)
			{
				cout << ResultPacket::enumToStringMap[real_result[i].first] << ": real value:" << real_result[i].second << " except value:" << except_result[i].second << endl;
			}
		}
		test_result.push_back(false);
	}
	return	std::any_of(test_result.begin(), test_result.end(), [](auto&& element)
	{
		return element == false;
	});
}
void test(const vector<string>& args, const unordered_map<string, unordered_map<ControllParam, int>>& except)
{
	CommandParser parser(args);
	parser.GetParamInfoPacket();
	FileAnalysis analyzer(parser.GetParamInfoPacket());
	auto result = analyzer.GetResultPacket().GetResultMap();
	assert(except_eq(*result, except));
}

void test_all()
{
	string prefix = R"(F:\MyProjects\Modern-software-engineering-courses\Modern-software-engineering-courses\作业\1.单词频率统计\test\)";
	unordered_map<string, vector<pair< ControllParam, int>>> data(
	{
		{
			prefix + "nullfile.txt",
			{
				{ ControllParam::Char, 0 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 0 },
				{ ControllParam::SumLine, 0 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "onechar.txt",
			{
				{ ControllParam::Char, 1 },
				{ ControllParam::CodeLine, 1 },
				{ ControllParam::EmptyLine, 1 },
				{ ControllParam::NoteLine, 0 },
				{ ControllParam::SumLine, 1 },
				{ ControllParam::Word, 1 },
			}
		},
		{
			prefix + "note1.txt",
			{
				{ ControllParam::Char, 2 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 1 },
				{ ControllParam::SumLine, 1 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note2.txt",
			{
				{ ControllParam::Char, 4 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 1 },
				{ ControllParam::SumLine, 1 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note3.txt",
			{
				{ ControllParam::Char, 5 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 2 },
				{ ControllParam::SumLine, 2 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note4.txt",
			{
				{ ControllParam::Char, 7 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 2 },
				{ ControllParam::SumLine, 2 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note5.txt",
			{
				{ ControllParam::Char, 8 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 3 },
				{ ControllParam::SumLine, 3 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note6.txt",
			{
				{ ControllParam::Char, 7 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 2 },
				{ ControllParam::SumLine, 2 },
				{ ControllParam::Word, 0 },
			}
		},
		{
			prefix + "note7.txt",
			{
				{ ControllParam::Char, 8 },
				{ ControllParam::CodeLine, 0 },
				{ ControllParam::EmptyLine, 0 },
				{ ControllParam::NoteLine, 3 },
				{ ControllParam::SumLine, 3 },
				{ ControllParam::Word, 0 },
			}
		},
	});
	unordered_map<string, unordered_map<ControllParam, int>> except;
	for(auto& Iter : data)
	{
		except.insert({ Iter.first, unordered_map<ControllParam, int>(Iter.second.begin(), Iter.second.end()) });
	}
	test({
		"qwewq.exe",
		"-l",
		"-c",
		"-w",
		"-a",
		"-s",
		R"(F:\MyProjects\Modern-software-engineering-courses\Modern-software-engineering-courses\作业\1.单词频率统计\test\*.txt)",
	}, except);
}
int main(int argc, char** argv)
{
	try
	{
		test_all();
	}

	catch(const exception& e)
	{
		cout << e.what();
	}

	return 0;
}