#ifndef __ARRAY__
#define __ARRAY__

template <typename T>
class array
{
private:
	T* block;
	size_t size;

	void copy(const array<T>& rhs)
	{
		block = new (std::nothrow) T[rhs.size];
		if(block)
		{			
			size = rhs.size;
			for(register int i = 0 ; i < rhs.size ; ++i)
			{
				block[i] = rhs.block[i];
			}
		}
	}

	bool isValid(const int i) const
	{
		return (i >= 0) && (i < size);
	}

	void clear()
	{
		if(block)
		{
			delete[] block;
			size = 0;
		}
	}

public:

	class arrayIterator
	{
	private:
		T* arr;
		size_t currPos;

	public:
		arrayIterator() : arr(nullptr), currPos(0) {}

		arrayIterator(T* begin_arg, size_t currPos_arg) : arr(begin_arg), currPos(currPos_arg) {}

		arrayIterator& operator++()
		{
			++currPos;
			return *this;
		}

		arrayIterator operator++(int)
		{
			++currPos;
			return *this;
		}

		arrayIterator& operator--()
		{
			--currPos;
			return *this;
		}

		arrayIterator operator--(int)
		{
			--currPos;
			return *this;
		}

		inline T& operator*()
		{
			return arr[currPos];
		}

		inline bool operator!=(const array<T>::arrayIterator& rhs) const
		{
			return arr != rhs.arr ? true : currPos != rhs.currPos;
		}
	};

	inline arrayIterator begin()
	{
		array<T>::arrayIterator it(block, 0);
		return it;
	}

	inline arrayIterator end()
	{
		array<T>::arrayIterator it(block, size - 1);
		return it;
	}

	array(size_t size_arg) : size(size_arg)
	{
		block = new (std::nothrow) T[size];
		if(block)
		{
			size = size_arg;
		}
	}

	array(const array<T>& rhs) : size(rhs.size)
	{
		copy(rhs);
	}

	array& operator=(const array<T>& rhs)
	{
		if(this != &rhs)
		{
			if(block)
			{
				clear();
				copy(rhs);
			}

		}
	}

	T& operator[](const int i)
	{
		if(isValid(i))
		{
			return block[i];
		}
		return block[0];
	}

	void printAll() const
	{
		for(int i = 0 ; i < size ; ++i)
			std::cout << block[i] << " ";
		std::cout << std::endl;
	}

	size_t inline Size() const
	{
		return this->size;
	}

	~array()
	{
		clear();
	}

};

#endif