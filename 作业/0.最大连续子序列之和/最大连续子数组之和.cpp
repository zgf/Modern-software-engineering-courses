// 最大连续子数组之和.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//动态规划
int DynamicProgramming(const vector<int>& Array)
{
	//从i到j的最大值保存在这里
	//i<=j
	//状态转移方程: list[i][j] = array[i](i==j)
	//						   max(list[i][j-1] + array[j],list[i][j-1])
	vector<vector<int>> MaxList(Array.size());
	for (auto&& Element : MaxList)
	{
		Element.resize(Array.size());
	}
	for(auto i = 0; i < MaxList.size();i++)
	{
		MaxList[i][i] = Array[i];
	}
	for(auto j = 1; j < MaxList.size();j++)
	{
		for(auto i = 0; i <=j ;i++)
		{
			MaxList[i][j] = MaxList[i][j - 1] + Array[j];
		}
	}
	auto max_element = MaxList[0][0];
	for(auto i = 0; i < MaxList.size();i++)
	{
		for(auto j = i; j < MaxList.size();j++)
		{
			if(MaxList[i][j] > max_element)
			{
				max_element = MaxList[i][j];
			}
		}
	}
	return max_element;
}
int GetMiddleMax(const vector<int>& Array, const int Low,const int Mid, const int High)
{
	auto left_max = Array[Mid - 1];
	auto right_max = Array[Mid];

	std::reverse_iterator<decltype(Array.begin())> beginIter(Array.begin()+ Mid);
	std::reverse_iterator<decltype(Array.begin())> endIter(Array.begin() + Low);

	auto accumulater = [](auto&& beginIter,auto&& endIter,auto&& init,auto&& MaxDirect)
	{
		accumulate(beginIter, endIter, init, [&MaxDirect](auto&& Sum, auto&& Element)
		{
			Sum += Element;
			if(Sum > MaxDirect)
			{
				MaxDirect = Sum;
			}
			return Sum;
		});
		return MaxDirect;
	};
	return accumulater(beginIter, endIter, 0, left_max) + accumulater(Array.begin() + Mid, Array.begin() + High, 0, right_max);
}
//分治法
void CirculationAlgorithm(const vector<int>& Array,vector<vector<int>>& MaxList,const int Low,const int High)
{
	if(High == Low + 1)
	{
		MaxList[Low][High] = Array[Low];
	}
	else if(High > Low+1)
	{
		auto Mid = (High + Low) / 2;
		CirculationAlgorithm(Array, MaxList, Low, Mid);
		CirculationAlgorithm(Array, MaxList, Mid, High);
		vector<int> ChoseList = { MaxList[Low][Mid], MaxList[Mid][High], GetMiddleMax(Array, Low, Mid, High) };
		MaxList[Low][High] = *max_element(ChoseList.begin(), ChoseList.end());
	}
}
int CirculationAlgorithm(const vector<int>& Array)
{
	auto Low = 0;
	auto High = Array.size();
	vector<vector<int>> MaxList(Array.size()+1);
	for(auto&& Element : MaxList)
	{
		Element.resize(Array.size()+1);
	}
	CirculationAlgorithm(Array, MaxList, Low, High);
	return MaxList[Low][High];
}
//动态规划 O(n)算法
//假设a[n]表示以a[n]结尾的连续子数组的最大连续子数组之和
//所以a[n+1] = max(a[n]+array[n+1],array[n+1])
//当我们已经知道了a[n]的结果的时候,a[n+1]的结果,要么包含a[n],a[n+1] = a[n] +array[n+1],要么是array[n+1];
int DynamicProgrammingOn(const vector<int>& Array)
{
	vector<int> MaxList(Array.size());
	MaxList[0] = Array[0];
	for(auto i = 1; i < MaxList.size(); i++)
	{
		MaxList[i] = std::max(Array[i] + MaxList[i - 1], Array[i]);
	}
	return *std::max_element(MaxList.begin(), MaxList.end());
}
void Test_Value(const vector<int>& Array)
{
	if (!Array.empty())
	{
		auto Result1 = CirculationAlgorithm(Array);
		auto Result2 = DynamicProgramming(Array);
		auto Result3 = DynamicProgrammingOn(Array);
		assert(Result1 == Result2&& Result2 == Result3);
	}
	else
	{
		abort();
	}
}

int main()
{
	Test_Value({ 1, 4, -1, 3, -1, 4 });
	Test_Value({ 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 });
	Test_Value({1, -53,- 58 });
	Test_Value({ -1, -53, -58 });

	return 0;
}

