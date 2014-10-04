#include <vector>
#include <iterator>

namespace MyCode
{
	template<typename Iter, typename V>
	Iter find(Iter begin, Iter end, V value)
	{
		while (begin != end)
		{
			if (value == *begin)
			{
				break;
			}
			++begin;
		}
		return begin;
	}

	template<typename T, typename Iter = std::vector<T>::iterator>
	unsigned binarySearch(std::vector<T>& values, const T& searchedValue)
	{
		unsigned leftIndex = 0u;
		unsigned rightIndex = values.size() - 1;
		unsigned middleIndex;
		T middleValue;
		while (leftIndex <= rightIndex)
		{
			middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
			middleValue = values[middleIndex];
			if (middleValue == searchedValue)
			{
				return middleIndex;
			}
			else if (searchedValue < middleValue)
			{
				// limit search to left half
				rightIndex = middleIndex - 1;
			}
			else
			{
				// limit search to right half
				leftIndex = middleIndex + 1;
			}
		}
		return values.size();
	}

	template<typename Iter, typename T>
	bool binarySearch(Iter begin, Iter end, const T& value)
	{
		begin = lowerBound(begin, end, value);
		return ((begin != end) && !(value < *begin));
	}

	template<typename ForwardIterator, typename T>
	ForwardIterator lowerBound(ForwardIterator begin, ForwardIterator end, const T& value)
	{
		ForwardIterator iter;
		std::iterator_traits<ForwardIterator>::difference_type count;
		std::iterator_traits<ForwardIterator>::difference_type step;

		count = std::distance(begin, end);
		while (count > 0)
		{
			iter = begin;
			step = count / 2;
			MyCode::advance(iter, step);
			if (*iter < value)
			{
				begin = ++iter;
				count -= (step + 1);
			}
			else
			{
				count = step;
			}
		}

		return begin;
	}

	template<typename Iter, typename Distance>
	void advance(Iter& it, Distance step)
	{
		_advance(it, step, _getIteratorCategory(it));
	}

	template<typename Iter>
	typename std::iterator_traits<Iter>::iterator_category _getIteratorCategory(const Iter& it)
	{
		std::iterator_traits<Iter>::iterator_category cat;
		return cat;
	}

	template<typename Iter, typename Distance>
	void _advance(Iter& it, Distance step, std::random_access_iterator_tag)
	{
		it += step;
	}

	template<typename Iter, typename Distance>
	void _advance(Iter& it, Distance step, std::bidirectional_iterator_tag)
	{
		for (; 0 < step; --step)
		{
			++it;
		}
		for (; 0 > step; ++step)
		{
			--it;
		}
	}

	template<typename Iter, typename V>
	unsigned count(Iter begin, Iter end, V value)
	{
		unsigned occurences = 0u;
		while (begin != end)
		{
			if (value == *begin++)
			{
				++occurences;
			}
		}
		return occurences;
	}

	template<typename Iter, typename BinaryOperation>
	unsigned count_if(Iter begin, Iter end, BinaryOperation op)
	{
		unsigned occurences = 0u;
		while (begin != end)
		{
			if (op(*begin++))
			{
				++occurences;
			}
		}
		return occurences;
	}
}