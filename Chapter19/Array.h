#include <initializer_list>

namespace MyCode
{
	template<typename T, int N>
	class Array
	{
	public:
		Array() {}
		Array(std::initializer_list<T> list)
		{
			int index = 0;
			auto listBegin = list.begin();
			auto listEnd = list.end();
			while ((listBegin != listEnd) && (index < N))
			{
				elements[index++] = *listBegin++;
			}
		}

		T& operator[] (int index) 
		{
			return elements[index];
		}

		const T& operator[] (int index) const 
		{
			return elements[index];
		}

		T* data()
		{
			return elements;
		}
		const T* data() const
		{
			return elements;
		}

		int size()
		{
			return N;
		}

	private: 
		T elements[N];
	};
}