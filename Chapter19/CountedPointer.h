namespace MyCode
{
	template<typename T>
	class CountedPointer
	{
	public:
		CountedPointer(T&& initialValue) : 
			mValue{ new T{ initialValue } },
			mCounter(new int{1})
		{}

		template<typename P>
		explicit CountedPointer(P initialValue) :
			mValue{ new T{ initialValue } },
			mCounter(new int{ 1 })
		{}

		CountedPointer(const CountedPointer& other) : 
			mValue{ other.mValue },
			mCounter{ other.mCounter }
		{
			++(*mCounter);
		}

		CountedPointer(CountedPointer&& other) :
			mValue{ other.mValue },
			mCounter{ other.mCounter }
		{
			other.mValue = nullptr;
			other.mCounter = nullptr;
		}

		~CountedPointer()
		{
			if (mCounter)
			{
				if (--(*mCounter) <= 0)
				{
					delete mCounter;

					if (mValue)
					{
						delete mValue;
					}
				}
				mCounter = nullptr;
				mValue = nullptr;
			}
		}
		T& operator*()
		{
			return *mValue;
		}
		T* operator->()
		{
			return mValue;
		}
	private:
		T* mValue;
		int* mCounter;
	};
}