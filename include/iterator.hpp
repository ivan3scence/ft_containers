#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {
typedef unsigned int ptrdiff_t;
class random_access_iterator_tag {};
template <class T> class iterator_traits {
public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};
template <typename T> class VectorIterator {
  typedef typename iterator_traits<T *>::value_type value_type;
  typedef typename iterator_traits<T *>::pointer pointer;
  typedef typename iterator_traits<T *>::reference reference;
  typedef typename iterator_traits<T *>::difference_type difference_type;
  typedef pointer iterator_type;
  // this is for std::functions
  typedef random_access_iterator_tag iterator_category;

private:
  pointer _ptr;

public:
  VectorIterator(void) : _ptr() {}
  VectorIterator(pointer a) : _ptr(a) {}
  virtual ~VectorIterator(void) {}
  VectorIterator(const VectorIterator &other) : _ptr(other.base()) {}
  pointer &base(void) { return (_ptr); }
  VectorIterator &operator=(const VectorIterator &other) {
	if (this == *other)
	  return (*this);
	_ptr = other.base();
	return (*this);
  }
  reference operator*(void) const { return (*this->_ptr); }
  pointer operator->(void) const { return (this->_ptr); }
  value_type operator[](int val) const { return (*(_ptr + val)); }
  VectorIterator operator++(void) {
	++this->_ptr;
	return (*this);
  }
  VectorIterator operator++(int) {
	VectorIterator tmp(*this);

	++this->_ptr;
	return (tmp);
  }
  VectorIterator operator--(void) {
	--this->_ptr;
	return (*this);
  }
  VectorIterator operator--(int) {
	VectorIterator tmp(*this);

	--this->_ptr;
	return (tmp);
  }
  VectorIterator operator+=(int val) {
	this->_ptr += val;
	return (*this);
  }
  VectorIterator operator-=(int val) {
	this->_ptr -= val;
	return (*this);
  }
  VectorIterator operator-(int val) { return (*this->_ptr - val); }
  VectorIterator operator+(int val) { return (*this->_ptr + val); }
  difference_type operator-(VectorIterator const &other) const {
	return (this->_ptr - other.base());
  }
  bool operator==(VectorIterator const &other) const {
	return (this->_ptr == other.base());
  }
  bool operator!=(VectorIterator const &other) const {
	return (!(*this == other));
  }
  bool operator<(VectorIterator const &other) const {
	return (this->_ptr < other.base());
  }
  bool operator>(VectorIterator const &other) const {
	return (this->_ptr > other.base());
  }
  bool operator>=(VectorIterator const &other) const {
	return (this->_ptr >= other.base());
  }
  bool operator<=(VectorIterator const &other) const {
	return (this->_ptr <= other.base());
  }
};

} // namespace ft
//	template
//	<
//			class Category,
//			class T,
//			class Distance = std::ptrdiff_t,
//			class Pointer = T *,
//			class Reference = T &
//	> class iterator
//	{
//	public:
//		typedef T			value_type;
//		typedef Pointer		pointer;
//		typedef Reference	reference;
//		typedef Distance	difference_type;
//		typedef Category	iterator_category;
//	};
//

//
//	class bidirectional_iterator_tag {};
//	template <class T>
//		class bidirectional_iterator :
//ft::iterator<bidirectional_iterator_tag, T>
//		{
//			typedef typename
//ft::iterator<ft::bidirectional_iterator_tag, T>::iteratorc_category
//iterator_category; 			typedef typename
//ft::iterator<ft::bidirectional_iterator_tag, T>::value_type
//value_type; 			typedef typename ft::iterator<ft::bidirectional_iterator_tag,
//T>::difference_type		difference_type; 			typedef typename
//ft::iterator<ft::bidirectional_iterator_tag, T>::reference
//reference; 			typedef typename ft::iterator<ft::bidirectional_iterator_tag,
//T>::pointer				pointer; 		private: 			pointer	_elem;
//		};
//
//	template < class Iter >
//		class reverse_iterator
//		{
//		public:
//			typedef Iterator	iterator_type;
//			typedef typename
//ft::iterator_traits<Iter>::iterator_category	iterator_category; 			typedef
//typename ft::iterator_traits<Iter>::difference_type 	difference_type; 			typedef
//typename ft::iterator_traits<Iter>::value_type value_type; 			typedef typename
//ft::iterator_traits<Iter>::pointer				pointer; 			typedef
//typename ft::iterator_traits<Iter>::reference			reference;
//
//			reverse_iterator(void) : _elem() {}
//			explicit reverse_iterator( iterator_type x ) : _elem(x)
//{} 			template< class U > 				reverse_iterator( const reverse_iterator<U>& other ) :
//_elem(other.base()) {} 			~reverse_iterator(void);
//
//			template< class U >
//				reverse_iterator& operator=( const
//reverse_iterator<U>& other );
//
//			iterator_type base() const { return (_elem); }
//			reference operator*() const { return (*(_elem - 1)); }
//		};
//}
//
#endif
