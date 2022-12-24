#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "iterator.hpp"
#include <memory>
#include <cstring>

namespace ft {

#ifdef LINUX
	//typedef unsigned int	nullptr;
#endif

template<class T> struct remove_const { typedef T type; };
template<class T> struct remove_const <const T> { typedef T type; };

typedef unsigned int ptrdiff_t;

class random_access_iterator_tag {};

template <class L>
class iterator_traits {
public:
	typedef ptrdiff_t						difference_type;
	typedef L								value_type;
	typedef L 								*pointer;
	typedef const L							*const_pointer;
	typedef L								&reference;
	typedef const L							&const_reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class T, class Allocator = std::allocator<T> > class vector {
public:
template <typename L> class RandomAccessIterator {
    typedef typename iterator_traits<L>::value_type			value_type;
    typedef typename iterator_traits<L>::pointer			pointer;
    typedef typename iterator_traits<L>::reference			reference;
	typedef typename iterator_traits<L>::const_reference	const_reference;
    typedef typename iterator_traits<L>::difference_type	difference_type;
    typedef pointer											iterator_type;
    // this is for std::functions
    typedef random_access_iterator_tag						iterator_category;

private:
    pointer _ptr;

public:
    RandomAccessIterator(void) : _ptr() {}
    RandomAccessIterator(pointer a) : _ptr(a) {}
    virtual ~RandomAccessIterator(void) {}
//    RandomAccessIterator(RandomAccessIterator &other) : _ptr(&(*other)) {}
//	RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type > & src) : _ptr(&(*src)) {}
//	RandomAccessIterator<value_type> &operator=(RandomAccessIterator<typename remove_const<value_type>::type>
//												const &src)
//	{
//		_ptr = &(*src);
//		return *this;
//	}
    pointer base(void) const { return (_ptr); }
	//const_pointer &base(void) const { return (_ptr); }

    RandomAccessIterator<value_type> &operator=(const RandomAccessIterator<value_type> &other) {
		if (this == &other)
		    return (*this);
		_ptr = other.base();
		return (*this);
    }

    RandomAccessIterator<value_type> &operator=(const RandomAccessIterator<const value_type> &other) {
		_ptr = other.base();
		return (*this);
    }

    reference operator*(void) { return (*_ptr); }
    pointer operator->(void) const { return (this->_ptr); }
    reference operator[](difference_type val) { return (*(_ptr + val)); }
	const_reference operator[](difference_type val) const { return (*(_ptr + val)); }
    RandomAccessIterator operator++(void) {
		++this->_ptr;
		return (*this);
    }
    RandomAccessIterator operator++(int) {
	RandomAccessIterator tmp(*this);

	++this->_ptr;
	return (tmp);
    }
    RandomAccessIterator operator--(void) {
	--this->_ptr;
	return (*this);
    }
    RandomAccessIterator operator--(int) {
	RandomAccessIterator tmp(*this);

	--this->_ptr;
	return (tmp);
    }

    RandomAccessIterator operator+=(int val) {
	this->_ptr += val;
	return (*this);
    }

    RandomAccessIterator operator-=(int val) {
	this->_ptr -= val;
	return (*this);
    }

    RandomAccessIterator operator-(int val) { return (this->_ptr - val); }
    RandomAccessIterator operator+(int val) { return (this->_ptr + val); }
    difference_type operator-(RandomAccessIterator const &other) const {
	return (this->_ptr - other.base());
    }

    bool operator==(RandomAccessIterator const &other) const {
	return (this->_ptr == other.base());
    }

    bool operator!=(RandomAccessIterator const &other) const {
	return (!(*this == other));
    }

    bool operator<(RandomAccessIterator const &other) const {
	return (this->_ptr < other.base());
    }

    bool operator>(RandomAccessIterator const &other) const {
	return (this->_ptr > other.base());
    }

    bool operator>=(RandomAccessIterator const &other) const {
	return (this->_ptr >= other.base());
    }

    bool operator<=(RandomAccessIterator const &other) const {
	return (this->_ptr <= other.base());
    }

};

public:
	typedef T												value_type;
	typedef Allocator										allocator_type;
	typedef size_t											size_type;
	typedef std::ptrdiff_t									difference_type;
	typedef typename Allocator::pointer						pointer;
	typedef typename Allocator::const_pointer				const_pointer;
	typedef RandomAccessIterator<value_type>				iterator;
	typedef RandomAccessIterator<const value_type>			const_iterator;
	typedef T&												reference;
	typedef const T&										const_reference;
	typedef struct s_vector_impl {
		pointer	start;
		pointer current;
		pointer end;
	} t_vector_impl;

	// ft::iterator
	// reverse_iterator; ft::iterator
	// const_reverse_iterator;
private:
	t_vector_impl _ptr;
	size_type _size;
	size_type _capacity;
	allocator_type _allocator;

public:
	vector(void) : _ptr(), _size(0), _capacity(0) {}

	explicit vector(const allocator_type &alloc)
		: _ptr(), _size(0), _capacity(0), _allocator(alloc) {}

	explicit vector(size_type count, const T &value = T(),
		const Allocator &alloc = Allocator());
	template <class InputIt>
		vector(InputIt first, InputIt last, const allocator_type &alloc = allocator_type());
	vector(const vector &other);
	~vector(void)
	{
		if (this->_ptr.start)
		this->_allocator.deallocate(this->_ptr.start,
								  this->_ptr.end - this->_ptr.start);
	}
  	vector &operator=(const vector &other);

	allocator_type get_allocator() const;
	void assign(size_t count, const T &value);
	template<class InputIt>
		void assign(InputIt first, InputIt last);

  /*		 Element access			*/
	reference at(size_type pos);
	const_reference at(size_type pos) const;
	reference operator[](size_type pos);
	const_reference operator[](size_type pos) const;
	reference front(void);
	const_reference front(void) const;
	reference back(void);
	const_reference back(void) const;
	T *data();
	const T *data() const;
  //		// Iterators
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
//	reverse_iterator rbegin();
//	const_reverse_iterator rbegin() const;
  //		// Capacity
	bool empty() const;
	size_type size() const;
	size_type max_size() const;
	void reserve(size_type new_cap);
	size_type capacity() const;
  //		// Modifiers
	void clear();
	iterator insert(iterator pos, const T &value);
	iterator insert(iterator pos, size_type count, const T
  					&value);
  	template<class InputIt>
  	iterator insert(iterator pos, InputIt first, InputIt last);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
  //
  //		void push_back(const T &value);
  //
  //		void pop_back();
  //
  //		void resize(size_type count, T value = T());
  //
  //		void swap(vector &other);
  //
  //		// Operators
  //		template<class T, class Alloc>
  //		bool operator==(const std::vector <T, Alloc> &lhs,
  //						const std::vector <T, Alloc>
  //&rhs);
  //
  //		template<class T, class Alloc>
  //		bool operator!=(const std::vector <T, Alloc> &lhs,
  //						const std::vector <T, Alloc>
  //&rhs);
  //
  //		template<class T, class Alloc>
  //		bool operator<(const std::vector <T, Alloc> &lhs,
  //					   const std::vector <T, Alloc> &rhs);
  //
  //		template<class T, class Alloc>
  //		bool operator<=(const std::vector <T, Alloc> &lhs,
  //						const std::vector <T, Alloc>
  //&rhs);
  //
  //		template<class T, class Alloc>
  //		bool operator>(const std::vector <T, Alloc> &lhs,
  //					   const std::vector <T, Alloc> &rhs);
  //
  //		template<class T, class Alloc>
  //		bool operator>=(const std::vector <T, Alloc> &lhs,
  //						const std::vector <T, Alloc>
  //&rhs);
  //
  //		// std::swap
  //		template<class T, class Alloc>
  //		void swap(std::vector <T, Alloc> &lhs,
  //				  std::vector <T, Alloc> &rhs);
  //
  //		// Iterators invalid
  //		iterator erase(iterator pos);
  //
  //		iterator erase(iterator first, iterator last);
  //
  //		void swap(vector &other);
private:
	pointer			getPtrStart(void) const;
	pointer			getPtrEnd(void) const;
	size_type		getPtrSize(void) const;
	t_vector_impl	getPtr(void) const;
	size_type		getCapacity(void) const;
	pointer			getPtrCurrent(void) const;
	void			copyPtrAttr(t_vector_impl &dst, t_vector_impl const &src);
	void			copy_array(pointer dst, pointer src, size_type count);
};

template < typename T, typename Allocator >
std::ostream	&operator << (std::ostream &os, const vector<T, Allocator> &vec)
{
	std::string	buf;
	int 		size;

	size = static_cast<int>(vec.size());
	for (int i=0; i<size; ++i)
	{
		buf += std::to_string(vec[i]);
		if (i + 1 != size)
			buf += " ";
	}
	os << buf;
	return (os);
}
} // namespace ft

#include "../templates/vector.tcc"

#endif
