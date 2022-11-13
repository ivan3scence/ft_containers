#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP


template <class T, class Allocator = std::allocator<T>> class vector
{
private:
	typedef T   value_type;
	typedef Allcator	allocator_type;
	typedef size_t	size_type;
	typedef std::ptrdiff_t	difference_type;
	value_type	&reference;
	const value_type	&const_reference;
	Allocator::pointer	pointer;
	Allocator::const_pointer	const_pointer;
	//ft::iterator	iterator;
	//ft::iterator	const_iterator;
	//ft::iterator	reverse_iterator;
	//ft::iterator	const_reverse_terator;
public:
	vector(void);
	explicit vector(const Allocator& alloc);
	explicit vector(size_type count,
					 const T& value = T(),
					 const Allocator& alloc = Allocator());
	template< class InputIt >
		vector( InputIt first, InputIt last,
				const Allocator& alloc = Allocator() );
	vector( const vector& other );

	~vector(void);

	vector& operator=( const vector& other );

	allocator_type get_allocator() const;

	void	assign(size_t count, const T &value);
	template< class InputIt >
		void assign(InputIt first, InputIt last);
	void assign( std::initializer_list<T> ilist );

	// Element access
	reference at( size_type pos );
	const_reference at( size_type pos ) const;
	reference operator[]( size_type pos );
	const_reference operator[]( size_type pos ) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	T* data();
	const T* data() const;

	// Iterators
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	// Capacity
	bool empty() const;
	size_type size() const;
	size_type max_size() const;
	void reserve( size_type new_cap );
	size_type capacity() const;

	// Modifiers
	void clear();
	iterator insert( const_iterator pos, const T& value );
	iterator insert( const_iterator pos, size_type count, const T& value );
	template< class InputIt >
		iterator insert( const_iterator pos, InputIt first, InputIt last );
	iterator erase( iterator pos );
	iterator erase( iterator first, iterator last );
	void push_back( const T& value );
	void pop_back();
	void resize( size_type count, T value = T() );
	void swap( vector& other );

	// Operators
	template< class T, class Alloc >
	bool operator==( const std::vector<T,Alloc>& lhs,
					 const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator!=( const std::vector<T,Alloc>& lhs,
					 const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<=( const std::vector<T,Alloc>& lhs,
					 const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>( const std::vector<T,Alloc>& lhs,
					const std::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>=( const std::vector<T,Alloc>& lhs,
					 const std::vector<T,Alloc>& rhs );

	// std::swap
	template< class T, class Alloc >
	void swap( std::vector<T,Alloc>& lhs,
			   std::vector<T,Alloc>& rhs );

	// Iterators invalid
	iterator erase( iterator pos );
	iterator erase( iterator first, iterator last );
	void swap( vector& other );
};