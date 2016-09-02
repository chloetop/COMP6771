#include <sys/types.h>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
#include <cmath>    

namespace evec {

class EuclideanVector {
 private:
  std::vector<double> v_;
  std::initializer_list<int> num;

 public:
  // constructors
  EuclideanVector() : EuclideanVector(0, 0.0) {}

  template <typename Integer>
  EuclideanVector(const Integer size) : EuclideanVector(size, 0.0) {}

  template <typename Integer, typename Num>
  EuclideanVector(const Integer size, const Num magnitude)
      : v_(static_cast<uint>(size), static_cast<double>(magnitude)) {}

  // range
  template <typename Iter>
  EuclideanVector(const Iter& begin,
                  const Iter& end,
                  typename Iter::iterator_category* p = 0)
      : v_{begin, end} {}

  EuclideanVector(std::initializer_list<int> num):v_(num.begin(), num.end()){}

  // Big 5 synthesized

  // utilities

  /**
   * Returns an unsigned int containing the number of dimensions in a particular
   * vector.
   */
  uint getNumDimensions() const { return static_cast<uint>(v_.capacity()); }
  /**
   * Returns a double, the value of the magnitude in the dimension given as the
   * function parameter
   */
  double get(uint i) const { return v_[i]; }
  /**
   * Returns the euclidean norm of the vector as a double. The euclidean norm is
   * the square root of the sum of the squares of the magnitudes in each
   * dimension.
   */
  double getEuclideanNorm() const {
    return sqrt(std::inner_product(v_.begin(), v_.end(), v_.begin(), 0.0));
  }
  /**
   * Returns a Euclidean vector that is the unit vector of *this vector, where
   * the magnitude for each dimension in the unit vector is the original
   * vector's magnitude divided by the euclidean norm.
   */
  EuclideanVector createUnitVector() const {
    return EuclideanVector(*this) /= getEuclideanNorm();
  }

  // operators
  double operator[](int i) const { return v_[i]; }  // getter
  double& operator[](int i) { return v_[i]; }       // setter
  EuclideanVector& operator+=(const EuclideanVector& rhs);
  EuclideanVector& operator-=(const EuclideanVector& rhs);
  EuclideanVector& operator*=(const double d);
  EuclideanVector& operator/=(const double d);

  // casting
  operator std::vector<double>() const {
    return std::vector<double>(v_.begin(), v_.end());
  }
  operator std::list<double>() const {
    return std::list<double>(v_.begin(), v_.end());
  }

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  friend bool operator==(const EuclideanVector& lhs,
                         const EuclideanVector& rhs);
  friend double operator*(const EuclideanVector& lhs,
                          const EuclideanVector& rhs);
};

inline bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  return !(lhs == rhs);
}

// depend on existing {+,-,*,/}= operators

inline EuclideanVector operator+(EuclideanVector lhs,
                                 const EuclideanVector& rhs) {
  return lhs += rhs;
}

inline EuclideanVector operator-(EuclideanVector lhs,
                                 const EuclideanVector& rhs) {
  return lhs -= rhs;
}

inline EuclideanVector operator*(EuclideanVector lhs, const double factor) {
  return lhs *= factor;
}

inline EuclideanVector operator*(const double factor, EuclideanVector rhs) {
  return rhs *= factor;
}

inline EuclideanVector operator/(EuclideanVector lhs, const double factor) {
  return lhs /= factor;
}

}
