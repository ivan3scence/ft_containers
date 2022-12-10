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
typename vector<T, Allocator>::reference	vector<T, Allocator>::operator [] (size_type pos)
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::operator [] (size_type pos) const
{
	if (pos > this->_size || pos < 0)
		throw std::out_of_range("vector at out of range");
	return (*(this->_ptr.start + pos));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::reference	vector<T, Allocator>::front(void)
{
	return (*(this->_ptr.start));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::front(void) const
{
	return (*(this->_ptr.start));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::reference	vector<T, Allocator>::back(void)
{
	return (*(this->_ptr.start + this->_ptr.current));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::back(void) const
{
	return (*(this->_ptr.start + this->_ptr.current));
}

template < typename T, typename Allocator >
const T	*vector<T, Allocator>::data(void) const
{
	return (this->_ptr.start);
}

template < typename T, typename Allocator >
T	*vector<T, Allocator>::data(void)
{
	return (this->_ptr.start);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::iterator	vector<T, Allocator>::begin(void)
{
	return (iterator(this->_ptr.start));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::begin(void) const
{
	return (const_iterator(this->_ptr.start));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::iterator	vector<T, Allocator>::end(void)
{
	return (iterator(this->_ptr.start + this->_size));
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::end(void) const
{
	return (const_iterator(this->_ptr.start + this->_size));
}


template < typename T, typename Allocator >
bool	vector<T, Allocator>::empty(void) const
{
	return (this->_ptr.start == this->_current);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::size(void) const
{
	return (this->_size);
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size(void) const
{
	return (this->_allocator.max_size());
}

template < typename T, typename Allocator >
void	vector<T, Allocator>::reserve(size_type new_cap)
{
	if (this->_capacity >= new_cap)
		return ;
	vector<value_type, allocator_type>	tmp(new_cap, 0, this->_allocator);
	tmp = *this;
	*this = tmp;
	_capacity = this->end - this->start;
}

template < typename T, typename Allocator >
typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity(void) const
{
	return (this->_capacity);
}

template < typename T, typename Allocator >
void	vector<T, Allocator>::clear(void)
{
	for (size_type i=0; i<this->_size; ++i)
		_allocator.destroy(this->_ptr.start + i);
	_size = 0;
	this->_ptr.current = this->_ptr.start;
}

template < typename T, typename Allocator >
typename vector<T,Allocator>::iterator	vector<T, Allocator>::insert(iterator pos, const T &value)
{
	iterator		end = this->end();
	iterator		begin = this->begin();
	iterator		ret = pos - 1;

	if (pos < begin || pos-- > end)
	{
		std::logic_error("wrong pos\n");
		return (pos);
	}
	if (this->_size == this->_capacity)
		this->reserve(this->_size + 1);
	for (unsigned int i = end - begin - 1; i >= pos - begin; --i)
	{
		*(this->_ptr.start + i + 1) = *(this->_ptr.start + i);
	}
	*pos = value;
	return (ret);
}

template < typename T, typename Allocator >
typename vector<T,Allocator>::iterator	vector<T, Allocator>::insert(iterator pos, size_type count, const T &value)
{
	iterator		end = this->end();
	iterator		begin = this->begin();
	iterator		ret = pos - count;

	if (pos < begin || pos > end || count > pos - begin)
	{
		std::logic_error("wrong pos\n");
		return (pos);
	}
	this->reserve(this->_size + count);
	for (iterator i = end + count; i >= pos; --i)
	{
		*i = *(i - count);
	}
	while (count-- > 0)
		*(--pos) = value;
	return (pos);
}

//template < typename T, typename Allocator >
//template < class InputIt >
//typename vector<T,Allocator>::iterator	vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
//{
//	iterator		end = this->end();
//	iterator		begin = this->begin();
//	size_type		len = last - first;
//	iterator		ret = pos - len;
//
//	if (pos < begin || pos > end || first > last || len > pos - begin)
//	{
//		std::logic_error("wrong pos\n");
//		return (pos);
//	}
//		this->reserve(this->_size + len);
//	for (iterator i = end; i >= pos; --i)
//	{
//		*i = *(i - len);
//	}
//	while (len-- > 0)
//		*(--pos) = len;
//	return (ret);
//}

}
