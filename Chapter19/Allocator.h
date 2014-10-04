#include <math.h>
#include <memory>
#include <new>
#include <utility>

namespace MyCode
{
	typedef long Align;

	union header
	{
		struct
		{
			union header *nextBlock;
			unsigned blockSize;
		} s;
		Align x;
	};

	typedef union header Header;

	class Arena
	{
	public:
		Arena(unsigned size) : mSize(size), mData{ new char[size] }
		{
			debugClear(&(*mData), mSize, 'z');
		}
		void* getData()
		{
			return &(*mData);
		}
		unsigned getSize()
		{
			return mSize;
		}
	private:
		void debugClear(char *array, unsigned size, char clearValue)
		{
			for (unsigned i = 0; i < size; ++i)
			{
				array[i] = clearValue;
			}
		}

		std::unique_ptr<char> mData;
		unsigned mSize;
	};

	template<typename T> 
	class Allocator
	{
	public:
		Allocator(Arena* arena) : mArena(arena)
		{
			if (mArena->getSize() >= 2 * sizeof(Header))
			{
				mFreeBlock = static_cast<Header*>(arena->getData());
				mFreeBlock->s.nextBlock = mFreeBlock;
				mFreeBlock->s.blockSize = convertFromBytesToHeaderUnits(arena->getSize());
			}
			else
			{
				mFreeBlock = nullptr;
			}
		}

		T* allocate(unsigned count)
		{
			T *allocation = nullptr;

			if ((count > 0) && mFreeBlock)
			{
				unsigned allocationSizeInBlocks = convertFromBytesToHeaderUnits(count * sizeof(T)) + 1;
				if (allocationSizeInBlocks <= mFreeBlock->s.blockSize)
				{
					Header* specialHeader = (mFreeBlock + mFreeBlock->s.blockSize) - allocationSizeInBlocks;
					if (specialHeader != mFreeBlock)
					{
						mFreeBlock->s.blockSize -= allocationSizeInBlocks;
						specialHeader->s.blockSize = allocationSizeInBlocks;
						specialHeader->s.nextBlock = nullptr;
					}
					else
					{
						mFreeBlock = nullptr;
					}
					allocation = reinterpret_cast<T*>(specialHeader + 1);
				}
			}
			return allocation;
		}
		void deallocate(T* array)
		{
			if (array)
			{
				Header* freedBlockHeader = reinterpret_cast<Header*>(array) - 1;
				if (mFreeBlock == nullptr)
				{
					mFreeBlock = freedBlockHeader;
					mFreeBlock->s.nextBlock = mFreeBlock;

					freedBlockHeader = mFreeBlock;
				}
				else
				{
					Header *leftBlockHeader = getLeftBlockHeaderFor(freedBlockHeader);
					if ((leftBlockHeader + leftBlockHeader->s.blockSize) == freedBlockHeader)
					{
						leftBlockHeader->s.blockSize += freedBlockHeader->s.blockSize;

						freedBlockHeader = leftBlockHeader;
					}
					else
					{
						freedBlockHeader->s.nextBlock = leftBlockHeader->s.nextBlock;
						leftBlockHeader->s.nextBlock = freedBlockHeader;
					}

					Header *rightBlockHeader = getRightBlockHeaderFor(freedBlockHeader);
					if ((freedBlockHeader + freedBlockHeader->s.blockSize) == rightBlockHeader)
					{
						freedBlockHeader->s.blockSize += rightBlockHeader->s.blockSize;
						freedBlockHeader->s.nextBlock = rightBlockHeader->s.nextBlock;

						if (rightBlockHeader == mFreeBlock)
						{
							mFreeBlock = freedBlockHeader;
						}
					}
				}
				debugClear(freedBlockHeader);
			}
		}

		void construct(T*& object)
		{
			T* allocatedSpace = allocate(sizeof(T));
			object = new (allocatedSpace)T();
		}
		void construct(T*& object, const T& defaultValue)
		{
			T* allocatedSpace = allocate(sizeof(T));
			object = new (allocatedSpace) T(defaultValue);
		}
		void construct(T*& object, T&& defaultValue)
		{
			T* allocatedSpace = allocate(sizeof(T));
			object = new (allocatedSpace)T(std::forward<T>(defaultValue));
		}
		void destroy(T*& object)
		{
			if (object)
			{
				object->~T();
				deallocate(object);
				object = nullptr;
			}
		}

		unsigned getAvailableFreeSpace()
		{
			unsigned freeSpace = 0;
			if (mFreeBlock)
			{
				Header *freeBlocksIterator = mFreeBlock;
				do
				{
					freeSpace += (freeBlocksIterator->s.blockSize - BLOCKS_OF_OVERHEAD);
				} while ((freeBlocksIterator = freeBlocksIterator->s.nextBlock) != mFreeBlock);
			}
			return (freeSpace * sizeof(Header));
		}

		unsigned getTotalFreeSpace()
		{
			unsigned freeSpace = 0;
			if (mFreeBlock)
			{
				Header *freeBlocksIterator = mFreeBlock;
				do
				{
					freeSpace += freeBlocksIterator->s.blockSize;
				} while ((freeBlocksIterator = freeBlocksIterator->s.nextBlock) != mFreeBlock);
			}
			return (freeSpace * sizeof(Header));
		}

		static const unsigned BLOCKS_OF_OVERHEAD = 1;
		static const unsigned BYTES_OF_OVEHEAD_PER_ALLOCATION = BLOCKS_OF_OVERHEAD * sizeof(Header);
	private:
		unsigned convertFromBytesToHeaderUnits(unsigned bytesCount)
		{
			return ((bytesCount + sizeof(Header)-1) / sizeof(Header));
		}

		Header* getLeftBlockHeaderFor(Header* blockHeader)
		{
			Header* leftBlockHeader = nullptr;
			Header* blockHeaderIterator = mFreeBlock;
			while ((blockHeaderIterator = blockHeaderIterator->s.nextBlock) != mFreeBlock)
			{
				if (blockHeaderIterator < blockHeader)
				{
					if ((leftBlockHeader == nullptr) || (blockHeaderIterator > leftBlockHeader))
					{
						leftBlockHeader = blockHeaderIterator;
					}
				}
			}
			return (leftBlockHeader ? leftBlockHeader : mFreeBlock);
		}

		Header* getRightBlockHeaderFor(Header* blockHeader)
		{
			Header* rightBlockHeader = nullptr;
			Header* blockHeaderIterator = mFreeBlock;
			while ((blockHeaderIterator = blockHeaderIterator->s.nextBlock) != mFreeBlock)
			{
				if (blockHeaderIterator > blockHeader)
				{
					if ((rightBlockHeader == nullptr) || (blockHeaderIterator < rightBlockHeader))
					{
						rightBlockHeader = blockHeaderIterator;
					}
				}
			}
			return (rightBlockHeader ? rightBlockHeader : mFreeBlock);
		}

		void debugClear(Header *blockHeader)
		{
			unsigned sizeOfAllocationInBytes = (blockHeader->s.blockSize - 1) * sizeof(Header);
			char *iter = reinterpret_cast<char*>(blockHeader + 1);
			for (unsigned i = 0; i < sizeOfAllocationInBytes; ++i)
			{
				*iter++ = 'z';
			}
		}

		std::unique_ptr<Arena> mArena;
		Header *mFreeBlock;
	};
}