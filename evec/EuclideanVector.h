#include <sys/types.h>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
#include <cmath>    

namespace evec {

class EuclideanVector {

 public:
  double *v;
  std::initializer_list<int> num;
  std::vector<double> v_;
  // Constructors
  EuclideanVector() : EuclideanVector(0, 0.0) {}
  template <typename Integer>
  EuclideanVector(const Integer size) : EuclideanVector(size, 0.0) {}
  template <typename Integer, typename Num>
  EuclideanVector(const Integer size, const Num magnitude){
        v = new double[static_cast<uint>(size)];
        v[0] = static_cast<double>(magnitude);
        push_data(v,static_cast<uint>(size));
      }
  template <typename Iter>
  EuclideanVector(const Iter& begin,
                  const Iter& end,
                  typename Iter::iterator_category* p = 0): v_{begin, end} {
      }
  EuclideanVector(std::initializer_list<int> num):v_(num.begin(), num.end()){
  }

  ~EuclideanVector(){
    delete(v);
  }

   // Returns the number of dimensions in a particular vector.

  uint getNumDimensions() const { return static_cast<uint>(v_.capacity()); }
  
   // Returns a double, the value of the magnitude in the dimension given as the
   // function parameter
   
  double get(uint i) const { return v_[i]; }

  void push_data(double a[],int size_of_array){
    for(int i=0;i<size_of_array;i++) v_.push_back(v[0]);
  } 
  // Returns the euclidean norm of the vector as a double. 
  // 
  double getEuclideanNorm() const {
    return sqrt(std::inner_product(v_.begin(), v_.end(), v_.begin(), 0.0));
  }
// Returns a Euclidean vector that is the unit vector of *THIS
  EuclideanVector createUnitVector() const {
    return EuclideanVector(*this) /= getEuclideanNorm();
  }
// (OVER)LOADING ZONE ... WATCH OUT

  double operator[](int i) const { return v_[i]; }  
  double& operator[](int i) { return v_[i]; }    
  
  operator std::vector<double>() const {
    return std::vector<double>(v_.begin(), v_.end());
  }
  operator std::list<double>() const {
    return std::list<double>(v_.begin(), v_.end());
  }
  EuclideanVector& operator+=(const EuclideanVector& rhs);
  EuclideanVector& operator-=(const EuclideanVector& rhs);
  EuclideanVector& operator*=(const double d);
  EuclideanVector& operator/=(const double d);
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  friend bool operator==(const EuclideanVector& lhs,
                         const EuclideanVector& rhs);
  friend double operator*(const EuclideanVector& lhs,
                          const EuclideanVector& rhs);
};

inline bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  return !(lhs == rhs);
}

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
