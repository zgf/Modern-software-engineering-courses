/*
Estimate:
���������
�������
��д����
��д��Ԫ����
��ʼ����
�ܽ�����

�������: 21.25
ͳ��Դ�ļ����ַ���,����,������
�û������ģʽ wc.exe [parameter] directory_name [file_name(regex)]
��������:
-c char count
-w word count
-l line count
��չ����
-s �ݹ鴦��Ŀ¼�·����������ļ�
-a ���ش������� ������ ע������
����:����ȫ���ǿո���߸�ʽ�����ַ�(�հ׷�),����д���,��ֻ�в�����һ������ʾ�ַ�.(<=1)
������:���а�������һ���ַ��Ĵ���(>1)
ע����:���а�����//����λ�ڿ�ע��֮��
file_name:������ʽ�����ļ���
�ı��ļ�:ȷ����/��/��
����:
wc.exe -s -a *.c
���ص�ǰĿ¼��ȫ����.c��β���ļ��Ĵ��������Ϳ�����,ע������.

��Ҫѧϰboost filesystem �����ļ�

����ĵ�: 22.00
CommandParser class
���� �����в��� ��� ����parameter infomation packet
parameter infomation packet struct
�ṹ:
enumֵ��ʾ���ܲ���
enum[] ���ܲ����б�
string	·����
string	�ļ�����regex
string[] �ļ����б�

FileAnalysis class
���� info packet
��� �������result packet struct
result packet struct
map<file_name,map<enum,int>> ���ܰ��� �ַ��� ������ ������ ������ ע������ ��������

static member map<enum,string>ö��ֵ->�ַ�����ʽ

����show����,��ʾͳ�ƽ��.

��:
CommandParser
���ݳ�Ա:
int rawNumber;
char** rawCommandList
���캯��:
CommandParser(int num,char** args)
���з���:
string[] GetFileNameList()
string GetDirectoryPath()
enum[] GetControlEnumList()
ParamInfo GetParamInfoPacket();

��:
struct ParamInfo  ADT
string[] fileNameList; (ȫ·����)
enum[] ControllParamList;
��:
FileAnalysis
��Ա:
ParamInfo paramPacket
���캯��:
FileAnalysis(ParamInfo packet)
���з���:
ResultPacket GetResultPacket();

��:
ResultPacket
��Ա:
map<file_name,map<enum,int>> resultMap;
static map<enum,string> enumToStringMap;
���з���:
void ShowResult();

����:
CommandParser parser(num,args);
FileAnalysis analyzer(parser.GetParamInfoPacket());
auto result = analyzer.GetResultPacket();
result.ShowResult();
*/
/*
����淶
������ �շ�ʽ
������ ������ ���ַ���д
���� ȫ�ַ���д���»���
*/
/*
������� 22.45
0 30��ͣ
ҹ��1Сʱ45����
����һ����Сʱ
����1����Сʱ
*/
