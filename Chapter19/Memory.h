namespace MyCode
{
	template<typename T>
	class UniquePointer
	{
	public:
		UniquePointer(T* value)
		{
			mValue = value;
		}

		UniquePointer(UniquePointer&& other)
		{
			if (&other != this)
			{
				mValue = other.mValue;
				other.mValue = nullptr;
			}
		}

		~UniquePointer()
		{
			reset();
		}

		T* operator->()
		{
			return mValue;
		}

		T& operator*()
		{
			return *mValue;
		}

		T* release()
		{
			T* valueToReturn = mValue;
			mValue = nullptr;
			return valueToReturn;
		}

		void reset()
		{
			if (mValue)
			{
				delete mValue;
				mValue = nullptr;
			}
		}

	private:
		UniquePointer(const UniquePointer& other)
		{}
		
		void operator=(const UniquePointer& other)
		{}

		T* mValue;
	};
}