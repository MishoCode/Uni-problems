#include<iostream>
#include<functional>
#include<vector>

template<class K, class T>
using MapFunction = const std::function<K(T)>&;

template<class T>
using FilterPred = const std::function<bool(T)>&;

template<class K, class T>
using Reducer = const std::function<K(K, T)>&;

template<class K, class T>   
std::vector<K> map(const std::vector<T>& list, MapFunction<K,T> mapFunc)
{
	std::vector<T> result;
	for (T iter : list)
	{
		result.push_back(mapFunc(iter));
	}
	return result;
}

template<class T>
std::vector<T> filter(const std::vector<T>& list, FilterPred<T> predicate)
{
	std::vector<T> result;
	for (T iter : list)
	{
		if (predicate(iter))
			result.push_back(iter);
	}
	return result;
}

template<class K, class T>
K reduce(const std::vector<T>& list, Reducer<K, T> reducer, const K& initialValue)
{
	K result = initialValue;
	for (T iter : list)
	{
		result = reducer(result, iter);
	}
	return result;
}

int sumOfOddSquares(std::vector<int>& v)
{
	return reduce<int, int>(filter<int>(
		(map<int, int>(v, [](int x) {return x * x; })), [](int x) {return x % 2 != 0; }),
		[](int res, int curr) {return res + curr; },
		0);
}

template<class T>
void printVector(const std::vector<T>& v)
{
	for (T iter : v)
	{
		std::cout << iter << " ";
	}
	std::cout << std::endl;
}
void testMap()
{
	std::vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 1);
	}

	std::vector<int> result = map<int, int>(v1, [](int x) {return x * x; });
	printVector(result);
}
void testFilter()
{
	std::vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 1);
	}

	std::vector<int> result = filter<int>(v1, [](int x) {return x % 2 == 0; });
	printVector(result);
}
void testReduce()
{
	int result = 0;
	std::vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 1);
	}

	result = reduce<int, int>(v1, [](int res, int curr) {return res + curr; }, 0);
	std::cout << result << std::endl;
}

void testSumOfOddSquares()
{
	int result = 0;
	std::vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 1);
	}
	std::cout << sumOfOddSquares(v1) << " " << std::endl;
}

int main()
{
	testMap();
	testFilter();
	testReduce();
	testSumOfOddSquares();
	return 0;
}
