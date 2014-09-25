#include "FileAnalysis.h"
#include "boost/filesystem.hpp"
int main()
{
	vector<string> args =
	{
		"qwewq.exe",
		"-l",
		"-c",
		"-w",
		"-a",
		"-s",
		R"(F:\MyProjects\Modern-software-engineering-courses\Modern-software-engineering-courses\��ҵ\1.����Ƶ��ͳ��\ParamInfo.h)",
	};
	CommandParser parser(args);
	parser.GetParamInfoPacket();
	FileAnalysis analyzer(parser.GetParamInfoPacket());
	analyzer.GetResultPacket().ShowResult();
	return 0;
}