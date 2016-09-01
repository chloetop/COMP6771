
#include "EuclideanVector.h"

#include <iostream>
#include <cassert>

void say(std::string);
void print(evec::EuclideanVector e);

int main() {
  {
    say("basic constructor");
    evec::EuclideanVector empty;
    print(empty);
    evec::EuclideanVector a(3);  // basic constructor
    print(a);
    unsigned int i = 3;
    evec::EuclideanVector z(i);  // basic constructor
    print(z);
    assert(a == z);
    std::cout << "passed." << std::endl;
  }

  {
    say("magnitude constructor");
    evec::EuclideanVector a(2, 4);
    evec::EuclideanVector b(2, 4.0);  // magnitude constructor
    assert(a[0] == 4);
    assert(b[0] == 4);
    unsigned int x = 2;
    double y = 4.0;
    evec::EuclideanVector z(x, y);  // magnitude constructor
    assert(b == z);
    std::cout << "passed." << std::endl;
  }

  {
    //    say("number of dimensions");
    evec::EuclideanVector b(2, 4.0);
    assert(b.getNumDimensions() == 2);  // number of dimensions
  }

  {
    //    say("euclidean norm");
    evec::EuclideanVector a(2, 3.0);
    std::cout << a.getEuclideanNorm() << std::endl;  // euclidean normal
  }

  {
    //    say("operator equality");
    evec::EuclideanVector a(3, 3.0);
    evec::EuclideanVector b(3, 4.0);
    evec::EuclideanVector c(3, 4.0);
    //    say(a);
    //    say(b);
    assert(a != b);  // operator equality
    assert(b == c);  // operator equality
  }

  {
    //    say("copy constructor");
    evec::EuclideanVector v(4, 3.0);
    evec::EuclideanVector a(v);
    assert(a == v);  // copy constructor
  }

  {
    //    say("copy assignment");
    evec::EuclideanVector v(4, 3.0), a = v;
    //    say(a);
    //    say(v);
    assert(a == v);  // copy assignment
  }

  {
    //    say("implicit constructor");
    evec::EuclideanVector a = 3;  // use an implicit constructor
    //    say(a);

    unsigned int i = 5;
    evec::EuclideanVector b = i;
    //    say(b);

    // expect:

    // [0 0 0]
    // [0 0 0 0 0]
  }

  {
    //    say("operator[]");
    evec::EuclideanVector a = 4;
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;
    std::cout << a << std::endl;
    std::cout << a[3] << std::endl;

    // expect:

    // [1 2 3 0]
    // 0
  }

  {
    say("+=, +, -=, -");
    evec::EuclideanVector a{4, 5}, b{4, 2};
    a += b;
    print(a);
    evec::EuclideanVector c = a + b;
    print(c);
    c -= b;
    print(c);
    c = a - b;
    print(c);
  }

  {
    say("unit vector");
    evec::EuclideanVector a(4);
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    std::cout << a.getEuclideanNorm() << std::endl;
    print(a.createUnitVector());
  }

  {
    say("*=, *, /=, /");
    evec::EuclideanVector a(4, 1);
    print(a *= 2);
    evec::EuclideanVector b = a * 3;
    print(b);
    double m = a * b;
    std::cout << m << std::endl;
    evec::EuclideanVector c = m * b;
    print(c);
  }

  {
    say("move constructor");
    evec::EuclideanVector f{2, 3};
    evec::EuclideanVector g = std::move(f);
    std::cout << g << std::endl;
  }

  {
    say("range");
    std::vector<double> a{1, 2, 3};
    evec::EuclideanVector b{a.begin(), a.end()};
    print(b);
    std::list<double> c{1, 2, 3};
    evec::EuclideanVector d{c.begin(), c.end()};
    print(d);
  }

  //  /*
  {
    say("type casting");
    evec::EuclideanVector a{2, 13};
    std::vector<double> vf = a;
    std::cout << vf[1] << std::endl;
    std::vector<double> lf = a;
    std::cout << lf[1] << std::endl;
  }
  //   */

  {  // const correctness

    std::list<double> l{1.0, 2.0, 3.0, 4.0};

    const evec::EuclideanVector e{(l.begin())++, l.end()};
    evec::EuclideanVector f = 6;
    std::cout << e << std::endl
              << e.getNumDimensions() << std::endl
              << e.get(1) << " " << e[2] << std::endl
              << e.getEuclideanNorm() << std::endl
              << e.createUnitVector() << std::endl
              << std::boolalpha << (f == e) << std::endl;
    std::cout << evec::EuclideanVector{4, 5} + e << std::endl;
    f = evec::EuclideanVector{4, 5.0} + e;
    std::cout << f << std::endl
              << static_cast<std::list<double>>(e).front() << std::endl;

    // expect:

    //  [1 2 3 4]
    //  4
    // 2 3
    // 5.47723
    // [0.182574 0.365148 0.547723 0.730297]
    // false
    // [6 7 8 9]
    // 1
  }

  {
    evec::EuclideanVector a_rval{1};

    unsigned int ui = 2;
    evec::EuclideanVector a2{ui};

    const int ci = 3;
    evec::EuclideanVector a3{ci};

    const unsigned int cui = 4;
    evec::EuclideanVector a4{cui};

    short unsigned si = 5;
    evec::EuclideanVector a5{si};

    std::list<int> l{1, 2, 4};
    evec::EuclideanVector b{l.begin(), l.end()};

    std::vector<unsigned int> v2{4, 5, 6, 7};
    evec::EuclideanVector c{v2.begin(), v2.begin() + 3};

    std::vector<double> a1{5, 4, 3.1, 2, 1.0};
    evec::EuclideanVector d{a1.begin(), a1.end()};

    evec::EuclideanVector e{1, 4};

    const int mag = 5;
    evec::EuclideanVector e2{ci, mag};

    evec::EuclideanVector e3{ui, 4.9};

    double d1 = 3.14;
    evec::EuclideanVector e4{cui, d1};
  }

  {
    say("----");
    evec::EuclideanVector a{2};  // use a constructor

    std::list<double> l{1, 2, 3};
    evec::EuclideanVector b{l.begin(), l.end()};

    std::vector<double> v2{4, 5, 6, 7};
    evec::EuclideanVector c{v2.begin(), v2.end()};

    std::vector<double> a1{5, 4, 3, 2, 1};
    evec::EuclideanVector d{a1.begin(), a1.end()};

    std::list<double> a2{9, 0, 8, 6, 7};
    evec::EuclideanVector e{a2.begin(), a2.end()};

    // use the copy constructor
    evec::EuclideanVector f{e};

    std::cout << a.getNumDimensions() << ": " << a << std::endl;
    std::cout << "D1:" << b.get(1) << " " << b << std::endl;
    std::cout << c << " Euclidean Norm = " << c.getEuclideanNorm() << std::endl;
    std::cout << d << " Unit Vector: " << d.createUnitVector()
              << " L = " << d.createUnitVector().getEuclideanNorm()
              << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;

    // test the move constructor
    evec::EuclideanVector g = std::move(f);
    std::cout << g << std::endl;

    // try operator overloading
    e += d;
    std::cout << e << std::endl;

    evec::EuclideanVector h = e - g;
    std::cout << h << std::endl;

    // test scalar multiplication
    h *= 2;
    std::cout << h << std::endl;

    evec::EuclideanVector j = b / 2;
    std::cout << j << std::endl;

    std::cout << "dot product = " << j * b << std::endl;

    if (g == (e - d))
      std::cout << "true" << std::endl;
    if (j != b)
      std::cout << "false" << std::endl;

    j[0] = 1;
    std::cout << j << std::endl;

    // type cast from EuclideanVector to a std::vector
    std::vector<double> vj = j;

    // type cast from EuclideanVector to a std::vector
    std::list<double> lj = j;

    for (auto d : lj) {
      std::cout << d << std::endl;
    }
  }

  {
    say("mutability");
    evec::EuclideanVector a{2, 3}, b{2, 4};
    evec::EuclideanVector c = a + b;
    print(a);
  }

  /*
{
  say("fail");
  evec::EuclideanVector a{2, 3}, b{3, 4};
  print(a + b);
}
   */
  return 0;
}

void say(std::string s) {
  std::cout << "--------\n" << s << std::endl;
}
void print(evec::EuclideanVector e) {
  std::cout << e << std::endl;
}
