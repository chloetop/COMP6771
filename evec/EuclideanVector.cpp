

#include "EuclideanVector.h"
#include <iostream>
#include <cassert>
#include <numeric>
#include <math.h>  

namespace evec {

// sorted according to order in header file

EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& rhs) {
  assert(this->getNumDimensions() == rhs.getNumDimensions() &&
         "sizes don't match");
  auto end = v_.end();
  std::transform(v_.begin(), end, rhs.v_.begin(), v_.begin(),
                 std::plus<double>());
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& rhs) {
  assert(this->getNumDimensions() == rhs.getNumDimensions() && "sizes don't match");
  auto end = v_.end();
  std::transform(v_.begin(), end, rhs.v_.begin(), v_.begin(),
                 std::minus<double>());
  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double d) {
  auto end = v_.end();
  std::for_each(v_.begin(), end, [d](double& x) { x *= d; });
  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double d) {
  auto end = v_.end();
  std::for_each(v_.begin(), end, [d](double& x) { x /= d; });
  return *this;
}

std::ostream& operator<<(std::ostream& os, const evec::EuclideanVector& v) {
  os << "[";
  for (uint i = 0; i < v.getNumDimensions(); ++i)
    os << (i > 0 ? " " : "") << v[i];
  os << "]";
  return os;
}

bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  auto end = lhs.v_.end();
  return lhs.getNumDimensions() == rhs.getNumDimensions() &&
         std::equal(lhs.v_.begin(), end, rhs.v_.begin());
}

// operator* :: EuclideanVector -> EuclideanVector -> double
// [] `operator*` _ = 0
// (x:xs) `operator*` (y:ys) = x * y + (xs .operator* ys)
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  assert(lhs.getNumDimensions() == rhs.getNumDimensions() &&
         "sizes don't match");
  auto end = lhs.v_.end();
  return std::inner_product(lhs.v_.begin(), end, rhs.v_.begin(), 0.0,
                            std::plus<double>(), std::multiplies<double>());
}

}  // namespace evec
