/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>

// we better include the iterator
#include "btree_iterator.h"

using namespace std;

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;
template <typename T>
ostream& operator<<(ostream& os, const btree<T>& tree);

template <typename T> 
class btree {
 public:
  /** Hmm, need some iterator typedefs here... friends? **/
  friend class btree_iterator<T>;
  friend class const_btree_iterator<T>;
  typedef btree_iterator<T> iterator;
  typedef const_btree_iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
 
  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined zero-arg constructor,
   * copy constructor, operator=, and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
  btree(size_t maxNodeElems = 40);

  /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
  btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
  btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
  btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
  btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
  friend ostream& operator<< <T> (ostream& os, const btree<T>& tree);

  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */
  iterator begin() { return iterator(first_, 0, this); }
  iterator end() { return iterator(nullptr, 0, this); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_iterator begin() const { return const_iterator(first_, 0, this); }
  const_iterator end() const { return const_iterator(nullptr, 0, this); }
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
  const_reverse_iterator rend() const { return reverse_iterator(begin()); }

  const_iterator cbegin() const { return const_iterator(first_, 0, this); }
  const_iterator cend() const { return const_iterator(nullptr, 0, this); }
  const_reverse_iterator crbegin() const { return reverse_iterator(cend()); }
  const_reverse_iterator crend() const { return reverse_iterator(cbegin()); }
  
  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
  iterator find(const T& elem);
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
  const_iterator find(const T& elem) const;
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and 
    * operator= method, and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
  pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
  ~btree();
  
private:
  // The details of your implementation go here
  struct node {
    friend ostream& operator<<(ostream& os, const node& node) {
      for (size_t i = 0; i < node.numVals_; ++i) {
        os << node.vals_[i] << " ";
      }
      return os;
    }
    node(size_t maxNodeElems, node *parent, size_t parentIndex) : nodeSize_(maxNodeElems),
                                                                  numVals_(0),
                                                                  parent_(parent),
                                                                  parentIndex_(parentIndex),
                                                                  children_(nullptr) {
      vals_ = new T[nodeSize_];
    }

    // TODO check const
    node(node *other, node *parent, size_t parentIndex) : nodeSize_(other->nodeSize_),
                                                          numVals_(other->numVals_),
                                                          parent_(parent),
                                                          parentIndex_(parentIndex),
                                                          children_(nullptr) {
      // Copy the values
      vals_ = new T[nodeSize_];
      for (size_t i = 0; i < nodeSize_; ++i) {
          vals_[i] = other->vals_[i];
      }

      // Recursively copy the children TODO check this
      if (numVals_ == nodeSize_) {
        children_ = new node*[nodeSize_ + 1];
        for (size_t i = 0; i < nodeSize_ + 1; ++i) {
          if (other->children_[i] != nullptr) {
            children_[i] = new node(other->children_[i], this, i);
          } else {
            children_[i] = nullptr;
          }
        }
      }
    }

    ~node() {
      delete[] vals_;
      if (numVals_ == nodeSize_) {
        for (size_t i = 0; i < nodeSize_ + 1; ++i) {
          if (children_[i] != nullptr) {
            delete children_[i];
          }
        }
      }
      delete[] children_;
      nodeSize_ = 0;
      numVals_ = 0;
      parent_ = nullptr;
      parentIndex_ = 0;
    }

    size_t nodeSize_;
    size_t numVals_;
    node *parent_;
    size_t parentIndex_;
    T *vals_;
    node **children_;
  };

  size_t nodeSize_;
  node *root_;
  node *first_;
  node *last_;
};


/**
 * The template implementation needs to be visible to whatever
 * translation unit makes use of templatized btree methods.
 * The unconventional practice is to #include the implementation
 * file just before the end of the interface (sort of like
 * sneaking it in and hoping it isn't noticed).  Because the
 * .tem file is included here, the .h file is NOT #included in 
 * the .tem file.  We'd otherwise have circular inclusions
 * and the compiler would be peeved.
 */

#include "btree.tem"

#endif
