#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

using namespace std;

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/
template <typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template <typename T>
class btree_iterator {
public:
    friend class const_btree_iterator<T>;
    typedef ptrdiff_t                  difference_type;
    typedef bidirectional_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;

    reference operator*() const;
    pointer operator->() const {
        return &(operator*());
    }
    btree_iterator& operator++();
    btree_iterator& operator--();
    bool operator==(const btree_iterator& other) const {
        return pointee_ == other.pointee_ && index_ == other.index_;
    }
    bool operator!=(const btree_iterator& other) const {
        return !operator==(other);
    }
    bool operator==(const const_btree_iterator<T>& other) const {
        return pointee_ == other.pointee_ && index_ == other.index_;
    }
    bool operator!=(const const_btree_iterator<T>& other) const {
        return !operator==(other);
    }

    btree_iterator(typename btree<T>::node *pointee = nullptr,
                   size_t index = 0, const btree<T> *tree = nullptr) : pointee_(pointee),
                                                                       index_(index),
                                                                       tree_(tree) {};
    btree_iterator(const btree_iterator<T>& other) : pointee_(other.pointee_),
                                                     index_(other.index_),
                                                     tree_(other.tree_) {};
    btree_iterator(const const_btree_iterator<T>& other) : pointee_(other.pointee_),
                                                           index_(other.index_),
                                                           tree_(other.tree_) {};

private:
    typename btree<T>::node *pointee_;
    size_t index_;
    const btree<T> *tree_;
};

template <typename T>
class const_btree_iterator {
public:
    friend class btree_iterator<T>;
    typedef ptrdiff_t                  difference_type;
    typedef bidirectional_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;

    reference operator*() const;
    pointer operator->() const {
        return &(operator*());
    }
    const_btree_iterator& operator++();
    const_btree_iterator& operator--();
    bool operator==(const const_btree_iterator& other) const {
        return pointee_ == other.pointee_ && index_ == other.index_;
    }
    bool operator!=(const const_btree_iterator& other) const {
        return !operator==(other);
    }
    bool operator==(const btree_iterator<T>& other) const {
        return pointee_ == other.pointee_ && index_ == other.index_;
    }
    bool operator!=(const btree_iterator<T>& other) const {
        return !operator==(other);
    }

    const_btree_iterator(typename btree<T>::node *pointee = nullptr,
                         size_t index = 0, const btree<T> *tree = nullptr) : pointee_(pointee),
                                                                             index_(index),
                                                                             tree_(tree) {};
    const_btree_iterator(const btree_iterator<T>& other) : pointee_(other.pointee_),
                                                           index_(other.index_),
                                                           tree_(other.tree_) {};
    const_btree_iterator(const const_btree_iterator<T>& other) : pointee_(other.pointee_),
                                                                 index_(other.index_),
                                                                 tree_(other.tree_) {};
private:
    typename btree<T>::node *pointee_;
    size_t index_;
    const btree<T> *tree_;
};

#include "btree_iterator.tem"

#endif
