#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
using namespace std;

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template<typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template<typename T> class btree_iterator {
public:
	typedef ptrdiff_t                  	difference_type;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T 						   	value_type;
	typedef T* 							pointer;
	typedef T& 							reference;
	friend class const_btree_iterator<T>;

	reference       operator *() const;
	pointer         operator->() const { return &(operator*()); }
	btree_iterator& operator++();
	btree_iterator& operator--();
	btree_iterator  operator++(int);
	btree_iterator  operator--(int);
	btree_iterator& operator =(const btree_iterator& other);
	bool			operator==(const btree_iterator& other) const;
	bool            operator==(const const_btree_iterator<T>& other) const;
	bool			operator!=(const btree_iterator& other) const
											{ return !operator==(other); }
	bool            operator!=(const const_btree_iterator<T>& other) const
											{ return !operator==(other); }
	btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t idx = 0,
			 const btree<T> *btree = nullptr) :
			pointee_(pointee), idx_(idx), btree_(btree) {}
private:
	/**
	 * helper functions
	 */
    void asc_up(const T& e);
    void asc_down();
    void desc_up(const T& e);
    void desc_down();
    /**
     * private parameters
     */
	typename btree<T>::Node *pointee_;
	size_t idx_;
	const btree<T> *btree_;
};

template<typename T> class const_btree_iterator {
public:
	typedef ptrdiff_t                  	difference_type;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T 						   	value_type;
	typedef const T* 					pointer;
	typedef const T& 					reference;
	friend class btree_iterator<T>;

	reference       	  operator*()  const;
	pointer        		  operator->() const { return &(operator*()); }
	const_btree_iterator& operator++();
	const_btree_iterator& operator--();
	const_btree_iterator  operator++(int);
	const_btree_iterator  operator--(int);
	const_btree_iterator& operator =(const const_btree_iterator& other);
	bool				  operator==(const const_btree_iterator& other) const;
	bool            	  operator==(const btree_iterator<T>& other) const;
	bool				  operator!=(const const_btree_iterator& other) const	{ return !operator==(other); }
	bool            	  operator!=(const btree_iterator<T>& other) const		{ return !operator==(other); }
	const_btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t idx = 0,
			const btree<T> *btree = NULL) :
			pointee_(pointee), idx_(idx), btree_(btree) {}
	const_btree_iterator(const btree_iterator<T>& rhs) :
			pointee_(rhs.pointee_), idx_(rhs.idx_), btree_(rhs.btree_) {}
private:
	/**
	 * helper functions
	 */
    void asc_up(const T& e);
    void asc_down();
    void desc_up(const T& e);
    void desc_down();

    /**
     * private parameters
     */
    typename btree<T>::Node *pointee_;
	size_t idx_;
	const btree<T> *btree_;
};

#include "btree_iterator.tem"
//#include "btree_iterator.tem.cpp"
#endif
