#ifndef _MY_CODE_VECTOR_H_
#define _MY_CODE_VECTOR_H_

#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <sstream>
#include <utility>
#include <iostream>

namespace MyCode
{
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first != last)
		{
			*result = *first;
			++result;
			++first;
		}
		return result;
	}

	template<typename T, typename A>
	struct VectorBase
	{
		A mAllocator;
		T* mElements;
		int mSize;
		int mCapacity;

		VectorBase(const A& allocator, int size):
			mAllocator{ allocator }, mSize{ size }, mCapacity{ size }
		{
			mElements = mAllocator.allocate(size);
		}

		VectorBase(const A& allocator, std::initializer_list<T> list) :
			mAllocator{ allocator }, mSize{ list.size() }, mCapacity{ list.size() }
		{
			mElements = mAllocator.allocate(mSize);
			copy(list.begin(), list.end(), mElements);
		}

		VectorBase(const VectorBase& other) :
			mAllocator{ other.mAllocator }, mSize{ other.mSize }, mCapacity{ other.mCapacity }
		{
			mElements = mAllocator.allocate(mSize);
			copy(other.mElements, (other.mElements + mSize), mElements);
		}

		VectorBase(VectorBase&& other) :
			mAllocator{ other.mAllocator }, mSize{ other.mSize }, mCapacity{ other.mCapacity },
			mElements{ other.mElements }
		{
			other.mSize = 0;
			other.mCapacity = 0;
			other.mElements = nullptr;
		}

		void operator=(const VectorBase& other)
		{
			mAllocator.deallocate(mElements, mSize);
			
			mAllocator = other.mAllocator;
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			
			mElements = mAllocator.allocate(mSize);
			copy(other.mElements, (other.mElements + mSize), mElements);
		}

		void operator=(VectorBase&& other) 	
		{
			mAllocator.deallocate(mElements, mSize);

			mAllocator = other.mAllocator;
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mElements = other.mElements;

			other.mSize = 0;
			other.mCapacity = 0;
			other.mElements = nullptr;
		}

		~VectorBase()
		{
			mAllocator.deallocate(mElements, mSize);
		}
	};

	template<typename T>
	class VectorIterator
	{
	public:
		explicit VectorIterator(T* value) : mValue(value)
		{}

		VectorIterator(const VectorIterator& other) : mValue(other.mValue)
		{}

		VectorIterator(VectorIterator&& other) 
			: mValue(other.mValue)
		{
			other.mValue = nullptr;
		}

		void operator=(const VectorIterator& other)
		{
			mValue = other.mValue;
		}

		bool operator==(const VectorIterator<T>& other)
		{
			return (mValue == other.mValue);
		}

		bool operator!=(const VectorIterator<T>& other)
		{
			return !(*this == other);
		}

		VectorIterator<T>& operator++() // pre-increment
		{
			++mValue;
			return *this;
		}

		VectorIterator<T>& operator--() // pre-increment
		{
			--mValue;
			return *this;
		}

		VectorIterator<T> operator++(int) // post-increment
		{
			VectorIterator<T> temp (*this);
			++mValue;
			return temp;
		}

		VectorIterator<T> operator--(int) // post-decrement
		{
			VectorIterator<T> temp(*this);
			--mValue;
			return temp;
		}

		T& operator*()
		{
			return *mValue;
		}
	private:
		T* mValue;
	};

	template<typename T>
	class VectorIteratorReverse
	{
	public:
		explicit VectorIteratorReverse(T* value)
			: mForwardIterator(value)
		{}
		void operator=(const VectorIteratorReverse& other)
		{
			mForwardIterator = other.mForwardIterator;
		}

		bool operator==(const VectorIteratorReverse<T>& other)
		{
			return (mForwardIterator == other.mForwardIterator);
		}

		bool operator!=(const VectorIteratorReverse<T>& other)
		{
			return !(*this == other);
		}

		VectorIteratorReverse<T>& operator++() // pre-increment
		{
			--mForwardIterator;
			return *this;
		}

		VectorIteratorReverse<T>& operator--() // pre-increment
		{
			++mForwardIterator;
			return *this;
		}

		VectorIteratorReverse<T> operator++(int) // post-increment
		{
			VectorIteratorReverse<T> temp(*this);
			--mForwardIterator;
			return temp;
		}

		VectorIteratorReverse<T> operator--(int) // post-decrement
		{
			VectorIteratorReverse<T> temp(*this);
			++mForwardIterator;
			return temp;
		}

		T& operator*()
		{
			return *mForwardIterator;
		}

	private:
		VectorIterator<T> mForwardIterator;
	};

	template <typename T, typename A = std::allocator<T>>
	class Vector
	{
	public:
		using iterator = VectorIterator < T > ;
		using reverse_iterator = VectorIteratorReverse < T >;

		Vector(int size = 0, A& allocator = A()) : mBase(allocator, size)
		{
			for (int i = 0; i < mBase.mSize; ++i)
			{
				mBase.mElements[i] = 0;
			}
		}

		Vector(std::initializer_list<T> list) : mBase(A(), list)
		{}

		Vector(const Vector& other) : mBase(other.mBase)
		{}

		Vector(Vector&& other) : mBase(std::forward<VectorBase<T, A>>(other.mBase))
		{}

		Vector& operator=(const Vector& other)
		{
			if (&other != this)
			{
				VectorBase<T, A> newBase(other.mBase);

				copy(other.mBase.mElements, (other.mBase.mElements + other.mBase.mSize), newBase.mElements);

				std::swap<VectorBase<T, A>>(mBase, newBase);
			}
			return *this;
		}

		Vector& operator=(Vector&& other)
		{
			VectorBase<T, A> newBase(other.mBase);
			std::swap<VectorBase<T, A>>(mBase, newBase);

			return *this;
		}

		~Vector()
		{}

		T& operator[](int index)
		{
			return mBase.mElements[index];
		}

		const T& operator[](int index) const
		{
			return mBase.mElements[index];;
		}

		int size() const
		{
			return mBase.mSize; 
		}
		T get(int index)
		{
			checkIfIndexIsInRange(index);
			return mBase.mElements[index];
		}
		void set(int index, T newValue)
		{
			checkIfIndexIsInRange(index);
			mBase.mElements[index] = newValue;
		}

		void reserve(int newCapacity)
		{
			if (newCapacity > mBase.mCapacity)
			{
				VectorBase<T, A> newBase(mBase.mAllocator, newCapacity);
				newBase.mSize = mBase.mSize;
				for (int i = 0; i < mBase.mSize; ++i)
				{
					mBase.mAllocator.construct(&newBase.mElements[i], mBase.mElements[i]);
				}
				for (int i = 0; i < mBase.mSize; ++i)
				{
					mBase.mAllocator.destroy(&mBase.mElements[i]);
				}
				std::swap<VectorBase<T, A>>(mBase, newBase);
			}
		}

		void push_back(const T& value)
		{
			if (mBase.mCapacity == 0)
			{
				reserve(DEFAULT_INITIAL_CAPACITY);
			}
			else if (mBase.mSize == mBase.mCapacity)
			{
				reserve(2 * mBase.mCapacity);
			}

			mBase.mAllocator.construct(&mBase.mElements[mBase.mSize++], value);
		}

		void resize(int newSize, T defaultValue = T())
		{
			if (newSize != mBase.mSize)
			{
				reserve(newSize);
				if (newSize < mBase.mSize)
				{
					for (int i = newSize; i < mBase.mSize; ++i)
					{
						T* element = &mBase.mElements[i];
						mBase.mAllocator.destroy(element);
					}
				}
				else
				{
					for (int i = mBase.mSize; i < newSize; ++i)
					{
						mBase.mAllocator.construct(&mBase.mElements[i], defaultValue);
					}
				}

				mBase.mSize = newSize;
			}
		}

		iterator begin()
		{
			return VectorIterator<T>(mBase.mElements);
		}

		iterator end()
		{
			return VectorIterator<T>(&mBase.mElements[mBase.mSize]);
		}

		reverse_iterator rbegin()
		{
			return VectorIteratorReverse<T>(&mBase.mElements[mBase.mSize - 1]);
		}

		reverse_iterator rend()
		{
			return VectorIteratorReverse<T>(mBase.mElements - 1);
		}

	private:
		void checkIfIndexIsInRange(int index) const
		{
			if ((index < 0) || (index >= mSize))
			{
				std::ostringstream errorMessage; 
				errorMessage << "Out of range index: " << index << std::endl;

				throw std::out_of_range(errorMessage.str());
			}
		}

		VectorBase<T, A> mBase;
		const int DEFAULT_INITIAL_CAPACITY = 10;
	};

	template<typename T, typename A>
	std::ostream& operator<<(std::ostream& out, Vector<T, A>& vec)
	{
		std::cout << "[";
		int lastIndex = vec.size() - 1;
		for (int i = 0; i < lastIndex; ++i)
		{
			std::cout << vec[i] << ",";
		}
		std::cout << vec[lastIndex] << "]";
		return out;
	}
}

#endif //_MY_CODE_VECTOR_H_