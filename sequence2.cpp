//FILE: sequence2.cpp(part of namespace main_savitch_4)
//CLASS implemented : sequence (see sequence2.h for documentation) 
//INVARIANT for the sequence class :
//1. The number of items in the sequence is in the member variable used.
//2. The actual items of the bag are stored in a partially filled array.
//	 The array is a dynamic array, pointed to by the member variable data.
//3. The size of the dynamic array is in the member variable capacity.
//4. For an empty sequence we do not care for the current_index. Once an item 
//	 is placed in the sequence that item's index is store in current_index. 
//	 Manipulating the current_index with the member functions
//	 allows you to insert, attach, or erase any item in the sequence while maintaing its order.
#include <algorithm>//Provides copy function
#include <cassert> //Provides assert function
#include "sequence2.h"

namespace main_savitch_4
{

	const sequence::size_type sequence::DEFAULT_CAPACITY;

	sequence::sequence(size_type initial_capacity)
	{
		data = new value_type[initial_capacity];
		capacity = initial_capacity;
		used = 0;
	}

	sequence::sequence(const sequence& source)
	{
		data = new value_type[source.capacity];
		capacity = source.capacity;
		used = source.used;
		current_index = source.current_index;
		std::copy(source.data, source.data + used, data);
	}

	sequence::~sequence()
	{
		delete[] data;
	}

	void sequence::start()
	{
		if (current_index)
			current_index = 0;
	}

	void sequence::advance()
	{
		assert(is_item());

		current_index++;
	}

	void sequence::insert(const value_type& entry)
	{
		if (used == capacity)
			resize(used + 1);


		if (is_item())
		{

			for (size_t i = used; i > current_index; i--)
			{

				data[i] = data[i - 1];

			}
			data[current_index] = entry;
			used++;
		}
		else
		{
			for (size_t i = (used + 1); i > 0; i--)
			{
				data[i] = data[i - 1];
			}
			data[0] = entry;
			used++;
			current_index = 0;
		}
	}


	void sequence::attach(const value_type& entry)
	{
		if (used == capacity)
			resize(used + 1);

		if (is_item())
		{

			for (size_t i = used; i > (current_index + 1); i--)
			{

				data[i] = data[i - 1];

			}
			data[current_index + 1] = entry;
			used++;
			current_index++;
		}
		else
		{

			data[used] = entry;
			current_index = used;
			used++;
		}
	}


	void sequence::remove_current()
	{
		assert(is_item());
		for (size_t i = current_index; i < (used - 1); i++)
		{
			data[i] = data[i + 1];
		}
		used--;
	}


	void sequence::resize(size_type new_capacity)
	{
		if (new_capacity == capacity)
			return;
		if (new_capacity < used)
			new_capacity = used;



		value_type *temp;
		temp = new value_type[new_capacity];
		std::copy(data, data + used, temp);
		delete[] data;
		data = temp;
		capacity = new_capacity;


	}

	void sequence::operator=(const sequence& source)
	{
		value_type *new_data;

		if (this == &source)
			return;


		if (capacity != source.capacity)
		{
			new_data = new value_type[source.capacity];
			delete[] data;
			data = new_data;
			capacity = source.capacity;

		}

		current_index = source.current_index;
		used = source.used;
		std::copy(source.data, source.data + used, data);


	}

	void sequence::operator+=(const sequence& y)
	{
		if(used + y.used > capacity)
			resize(used + y.used);
		
		std::copy(y.data, y.data + y.used, data + used);
		used = used + y.used;
	}

	sequence sequence::operator+(const sequence& y)
	{
		sequence sum(used + y.used);
		std::copy(data, data + used, sum.data);
		std::copy(y.data, y.data + y.used, sum.data + used);
		sum.used = y.used + used;
		return sum;
	}

	sequence::size_type sequence::size() const
	{
		return used;
	}

	bool sequence::is_item() const
	{
		if (current_index < used && current_index >= 0)
			return 1;
		else
			return 0;
	}

	sequence::value_type sequence::current() const
	{
		assert(is_item());
		return data[current_index];
	}

	sequence::value_type sequence::operator[](size_type index) const
	{
		return data[index];
	}
}