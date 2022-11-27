#include "vector.hpp"

namespace ft
{
template < typename T, typename Allocator >
vector<T, Allocator>::vector(vector<T, Allocator> const &other)
{
	*this = other;
}

template < typename T, typename Allocator >
vector<T, Allocator>::vector(size_type count, const value_type &value,
							 const allocator_type &alloc)
		: _size(count), _allocator(alloc)
{
	_capacity = count < 10000 ? 2 * count : count;
	this->_ptr.start = this->_allocator.allocate(this->_capacity);
	this->_ptr.current = this->_ptr.start;
	this->_ptr.end = this->_ptr.start + _capacity;
	for (size_type i=0; i < count; ++i)
	{
		this->_allocator.construct(this->_ptr.start + i, value);
		++this->_ptr.current;
	}
}

template < typename T, typename Allocator >
template < class InputIt >
vector<T, Allocator>::vector(InputIt first, InputIt last, const allocator_type &alloc) : _size(last - first + 1), _allocator(alloc)
{
	if (first > last)
		std::length_error("vector");
	this->_capacity = this->_size < 10000 ? 2 * this->_size : this->_size;
	this->_ptr.start = this->_allocator.allocate(this->_capacity);
	this->_ptr.current = this->_ptr.start;
	this->_ptr.end = this->_ptr.start + _capacity;
	for (size_type i=0; last != first; ++i)
	{
		*(this->_ptr.start + i) = first++;
		++this->_ptr.current;
	}
}

template < typename T, typename Allocator >
vector<T, Allocator>	&vector<T, Allocator>::operator = (vector<T, Allocator>
	const &other)
{
	if (this == &other)
		return (*this);
	//if (this->_allocator.propagate_on_container_move_assignment != true)
	//	this->_allocator = other->_allocator;
	size_type const	o_size = other.size();
	if (this->_capacity < o_size)
	{
		pointer	tmp = this->_allocator.allocate(o_size);
		std::memmove(tmp, other.getPtrStart(), other.getPtrFinish()
				- other.getPtrStart());
		this->_allocator.destroy(this->_ptr.start);
		this->_allocator.deallocate(this->_ptr.start, this->_ptr.end
				- this->_ptr.start);
		this->_ptr.start = tmp;
		copyPtrAttr(this->_ptr, other.getPtr());
		//this->_ptr.end = tmp + o_size;
		this->_size = o_size;
		this->_capacity = o_size;
	}
	else if (this->_size >= o_size)
	{
		this->_allocator.destroy(this->_ptr.start);
		std::memmove(this->_ptr.start, other.getPtrStart(), other.getPtrEnd()
				- other.getPtrStart());
		copyPtrAttr(this->_ptr, other.getPtr());
	}
	else
	{
		std::memmove(this->_ptr.start, other.getPtrStart(), other.getPtrEnd()
				- other.getPtrStart());
		copyPtrAttr(this->_ptr, other.getPtr());
	}
	return (*this);
}

template < typename T, typename Allocator >
void	vector<T, Allocator>::copyPtrAttr(t_vector_impl &dst,
		t_vector_impl const &src)
{
	dst.end = dst.start + (src.end - src.start);
	dst.current = dst.start + (src.current - src.start);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::getCapacity(void) const
{
	return (this->_capacity);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::allocator_type	vector<T, Allocator>::get_allocator(void) const
{
	return (this->_allocator);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::t_vector_impl	vector<T, Allocator>::getPtr(void) const
{
	return (this->_ptr);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::size(void) const
{
	return (this->_size);
}
template < typename T, typename Allocator >
typename vector<T, Allocator>::pointer	vector<T, Allocator>::getPtrFinish(void) const
{
	return (this->_ptr.current);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::pointer	vector<T, Allocator>::getPtrEnd(void) const
{
	return (this->_ptr.end);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::pointer	vector<T, Allocator>::getPtrStart(void) const
{
	return (this->_ptr.start);
}
template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::getPtrSize(void) const
{
	return (this->_ptr.end - this->_ptr.start);
}

template < typename T, typename Allocator >
void	vector<T, Allocator>::assign(size_type count, const value_type &value)
{
	if (count > this->_capacity)
	{
		vector<T, Allocator>	new_one(count, value);
		*this = new_one;
		return ;
	}
	vector<T, Allocator>::clear();
	for (size_type i=0; i<count; ++i)
	{
		this->_allocator.construct(this->_ptr.start + i, value);
	}
	this->_size += count;
	this->_ptr.current += count;
}

template < typename T, typename Allocator >
template <class InputIt>
void vector<T, Allocator>::assign(InputIt first, InputIt last)
{
	if (first > last) {
		std::logic_error("lol");
		return;
	}
	vector<T, Allocator>	new_one(first, last);
	*this = new_one;
}

template < typename T, typename Allocator >
void	vector<T, Allocator>::clear(void)
{
	int size;

	size = static_cast<int>(this->_size);
	for (int i = 0; i < size; ++i)
	{
		this->_allocator.destroy(this->_ptr.start + i);
	}
	this->_ptr.current -= size;
	this->_size -= size;
}

template < typename T, typename Allocator >
T&	vector<T, Allocator>::at(size_type pos)
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}

template < typename T, typename Allocator >
T const &	vector<T, Allocator>::at(size_type pos) const
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}

template < typename T, typename Allocator >
T&	vector<T, Allocator>::operator [] (size_type pos)
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}

template < typename T, typename Allocator >
T const &	vector<T, Allocator>::operator [] (size_type pos) const
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}
}
