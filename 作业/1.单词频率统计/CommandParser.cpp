#include "CommandParser.h"
unordered_map<string, ControllParam> CommandParser::paramMap =
{
	{ "-c", ControllParam::Char },
	{ "-l", ControllParam::SumLine },
	{ "-w", ControllParam::Word },
	{ "-s", ControllParam::RecursionPrint },
	{ "-a", ControllParam::AdvancedOptions },
};
CommandParser::CommandParser(int num, char** args) :CommandParser(ArgsWrap(num, args))
{
}

vector<string>	CommandParser::ArgsWrap(int num, char** args) const
{
	vector<string> result;
	for(auto i = 0; i < num; i++)
	{
		result.push_back(args[i]);
	}
	return std::move(result);
}
CommandParser::CommandParser(const vector<string>& args) : controllParamList(make_shared<vector<ControllParam>>()), fileNameList(make_shared<vector<string>>())
{
	InitMatchActionMap();
	auto num = args.size();
	this->directoryPathName = args[num - 1];
	SetControllParamList(args);
	this->matchProperty = GetMatchProperty();
	this->pathProperty = GetPathProperty();
	fileNameList = matchActionMap[matchProperty](GetFullPath());
	auto&& findIter = find(controllParamList->begin(), controllParamList->end(), ControllParam::RecursionPrint);
	if(findIter != controllParamList->end())
	{
		controllParamList->erase(findIter);
	}
}
CommandParser::PathProperty											CommandParser::GetPathProperty() const
{
	assert(!directoryPathName.empty());
	return directoryPathName.find(":") == directoryPathName.npos ? PathProperty::Relative : PathProperty::Absolute;
}
CommandParser::MatchProperty										CommandParser::GetMatchProperty() const
{
	assert(!directoryPathName.empty());
	assert(!controllParamList->empty());
	if(find(controllParamList->begin(), controllParamList->end(), ControllParam::RecursionPrint) == controllParamList->end())
	{
		return directoryPathName.find("*.") == directoryPathName.npos ? MatchProperty::MatchOne : MatchProperty::MatchAll;
	}
	else
	{
		return directoryPathName.find("*.") == directoryPathName.npos ? MatchProperty::RecursionMatchOne : MatchProperty::RecursionMatchAll;
	}
}
void									CommandParser::SetControllParamList(const vector<string>& args)
{
	for(size_t i = 1; i < args.size() - 1; i++)
	{
		auto&& tag = CommandParser::paramMap[args[i]];
		if(tag == ControllParam::AdvancedOptions)
		{
			controllParamList->push_back(ControllParam::EmptyLine);
			controllParamList->push_back(ControllParam::NoteLine);
			controllParamList->push_back(ControllParam::CodeLine);
		}
		else
		{
			controllParamList->push_back(tag);
		}
	}
}
void CommandParser::InitMatchActionMap()
{
	auto MatchFile = [](const string& pattern, auto&& iter)
	{
		using iter_type = typename std::decay<decltype(iter)>::type;
		static_assert(
			std::is_same<iter_type, boost::filesystem::recursive_directory_iterator>::value ||
			std::is_same<iter_type, boost::filesystem::directory_iterator>::value,
			"error! iter not except type.");
		auto&& result = make_shared<vector<string>>();
		iter_type end_iter;
		for(; iter != end_iter; iter++)
		{
			try
			{
				if(boost::filesystem::is_regular_file(iter->status()))
				{
					auto&& filename = iter->path().filename().generic_string();
					if(filename.find(pattern) != filename.npos)
					{
						result->push_back(iter->path().string());
					}
				}
			}
			catch(const std::exception & ex)
			{
				std::cout << iter->path().string() << " " << ex.what() << std::endl;
			}
		}
		return move(result);
	};
	matchActionMap.insert(make_pair(MatchProperty::MatchOne, [](const boost::filesystem::path& full_path)->shared_ptr<vector<string>>
	{
		auto&& result = make_shared<vector<string>>();
		result->push_back(full_path.generic_string());
		return move(result);
	}));
	matchActionMap.insert(make_pair(MatchProperty::MatchAll, [&MatchFile](const boost::filesystem::path& full_path)->shared_ptr<vector<string>>
	{
		boost::filesystem::path&& parentPath = full_path.parent_path();
		if(boost::filesystem::is_directory(parentPath))
		{
			return MatchFile(full_path.extension().string(), boost::filesystem::directory_iterator(parentPath));
		}
		assert(false);
		return {};
	}));

	matchActionMap.insert(make_pair(MatchProperty::RecursionMatchOne, [&MatchFile](const boost::filesystem::path& full_path)->shared_ptr<vector<string>>
	{
		if(!boost::filesystem::exists(full_path))
		{
			throw exception("not found this path");
		}
		boost::filesystem::path&& parentPath = full_path.parent_path();
		if(boost::filesystem::is_directory(parentPath))
		{
			return MatchFile(full_path.filename().generic_string(), boost::filesystem::recursive_directory_iterator(parentPath));
		}
		assert(false);
		return {};
	}));

	matchActionMap.insert(make_pair(MatchProperty::RecursionMatchAll, [&MatchFile]( const boost::filesystem::path& full_path)->shared_ptr<vector<string>>
	{
		boost::filesystem::path&& parentPath = full_path.parent_path();
		if(boost::filesystem::is_directory(parentPath))
		{
			return move(MatchFile(full_path.extension().string(), boost::filesystem::recursive_directory_iterator(parentPath)));
		}
		assert(false);
		return {};
	}));
}

boost::filesystem::path CommandParser::GetFullPath() const
{
	assert(!directoryPathName.empty());
	//因为C++缺少对象的null语义.所以这里没法检测是否PathProperty MatchProperty已经调用
	if(pathProperty == PathProperty::Absolute)
	{
		boost::filesystem::path full_path(directoryPathName);
		return move(full_path);
	}
	else
	{
		boost::filesystem::path part_path(directoryPathName);
		auto full_path = system_complete(part_path);
		return move(full_path);
	}
}
string					CommandParser::GetDirectoryPath()		const
{
	return this->directoryPathName;
}
shared_ptr<vector<ControllParam>>	CommandParser::GetControllParamList()	const
{
	return this->controllParamList;
}
ParamInfo				CommandParser::GetParamInfoPacket()		const
{
	ParamInfo result;
	result.fileNameList = GetFileNameList();
	result.ControllParamList = GetControllParamList();
	return move(result);
}
shared_ptr<vector<string>>			CommandParser::GetFileNameList()		const
{
	return this->fileNameList;
}