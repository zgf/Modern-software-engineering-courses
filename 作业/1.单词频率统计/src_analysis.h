/*
Estimate:
先需求分析
给出设计
编写代码
编写单元测试
开始测试
总结评估

需求分析: 21.25
统计源文件的字符数,行数,单词数
用户需求的模式 wc.exe [parameter] directory_name [file_name(regex)]
基本功能:
-c char count
-w word count
-l line count
扩展功能
-s 递归处理目录下符合条件的文件
-a 返回代码行数 空行数 注释行数
空行:本行全部是空格或者格式控制字符(空白符),如果有代码,则只有不超过一个可显示字符.(<=1)
代码行:本行包括多于一个字符的代码(>1)
注释行:本行包括了//或者位于块注释之间
file_name:正则形式给出文件名
文本文件:确定字/句/词
举例:
wc.exe -s -a *.c
返回当前目录下全部的.c结尾的文件的代码行数和空行数,注释行数.

需要学习boost filesystem 遍历文件

设计文档: 22.00
CommandParser class
输入 命令行参数 输出 参数parameter infomation packet
parameter infomation packet struct
结构:
enum值表示功能参数
enum[] 功能参数列表
string	路径名
string	文件名的regex
string[] 文件名列表

FileAnalysis class
输入 info packet
输出 解析后的result packet struct
result packet struct
map<file_name,map<enum,int>> 可能包括 字符数 单词数 总行数 空行数 注释行数 代码行数

static member map<enum,string>枚举值->字符串形式

包括show方法,显示统计结果.

类:
CommandParser
数据成员:
int rawNumber;
char** rawCommandList
构造函数:
CommandParser(int num,char** args)
公有方法:
string[] GetFileNameList()
string GetDirectoryPath()
enum[] GetControlEnumList()
ParamInfo GetParamInfoPacket();

类:
struct ParamInfo  ADT
string[] fileNameList; (全路径的)
enum[] ControllParamList;
类:
FileAnalysis
成员:
ParamInfo paramPacket
构造函数:
FileAnalysis(ParamInfo packet)
公有方法:
ResultPacket GetResultPacket();

类:
ResultPacket
成员:
map<file_name,map<enum,int>> resultMap;
static map<enum,string> enumToStringMap;
公有方法:
void ShowResult();

调用:
CommandParser parser(num,args);
FileAnalysis analyzer(parser.GetParamInfoPacket());
auto result = analyzer.GetResultPacket();
result.ShowResult();
*/
/*
代码规范
变量名 驼峰式
类型名 函数名 首字符大写
宏名 全字符大写加下划线
*/
/*
具体编码 22.45
0 30暂停
夜里1小时45分钟
下午一个半小时
晚上1个半小时
*/
