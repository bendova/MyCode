#pragma once

namespace MyCode
{
    template<typename T>
	T&& Move(T&& x)
	{
		return static_cast<T&&>(x);
	}

    template<typename T>
	void Swap(T& a, T& b)
	{
		T c(Move(a));
		a = Move(b);
		b = Move(c);
	}

    template<typename Iter>
	void Sort(Iter iter, Iter end)
	{
		for (; iter != end; ++iter)
		{
			for (Iter iter2 = iter + 1; iter2 != end; ++iter2)
			{
				if ((*iter < *iter2) == false)
				{
					Swap(*iter, *iter2);
				}
			}
		}
	}
}