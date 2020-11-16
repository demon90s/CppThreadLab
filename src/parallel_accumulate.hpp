#pragma once

#include <algorithm>
#include <numeric>
#include <thread>
#include <vector>

template<typename Iterator, typename T>
struct AccumulateBlock
{
	void operator()(Iterator first, Iterator last, T& res)
	{
		res = std::accumulate(first, last, res);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	size_t length = std::distance(first, last);
	if (length <= 0)
	{
		return init;
	}

	static const int MIN_PER_THREAD = 25;
	size_t max_thread = (length + MIN_PER_THREAD - 1) / MIN_PER_THREAD;

	size_t hardware_threads = std::thread::hardware_concurrency();
	if (hardware_threads <= 0)
	{
		hardware_threads = 2;
	}

	size_t num_thread = std::min(hardware_threads, max_thread);

	std::vector<T> result(num_thread);
	std::vector<std::thread> threads(num_thread - 1);	// 留一个主线程

	size_t block_sz = length / num_thread;

	Iterator block_start = first;
	for (size_t i = 0; i < num_thread - 1; i++)
	{
		Iterator block_end = std::next(block_start, block_sz);

		// 切分block给分支线程计算
		threads[i] = std::thread(AccumulateBlock<Iterator, T>(), block_start, block_end, std::ref(result[i]));

		block_start = block_end;
	}
	AccumulateBlock<Iterator, T>()(block_start, last, std::ref(result[num_thread - 1])); // 最后一个block留给主线程

	for (size_t i = 0; i < num_thread - 1; i++)
	{
		threads[i].join();
	}

	return std::accumulate(result.begin(), result.end(), init);
}
