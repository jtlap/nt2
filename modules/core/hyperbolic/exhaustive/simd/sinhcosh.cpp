//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/minlog.hpp>

#include <nt2/sdk/unit/exhaustive.hpp>
extern "C" { double cephes_sinh( double); }
extern "C" { double cephes_cosh( double); }

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

struct raw_cosh
{
  float operator()(float x) const
  {
    return float(cephes_cosh(double(x)));
  }
};
struct raw_sinh
{
  float operator()(float x) const
  {
    return float(cephes_sinh(double(x)));
  }
}; struct my_sinhcosh2
{
  template < class T >
  T operator()(T x) const
  {
    T a1, a2;
    nt2::sinhcosh(x, a1, a2);
    return a2;
  }
};
struct my_sinhcosh1
{
  template < class T >
  T operator()(T x) const
  {
    T a1, a2;
    nt2::sinhcosh(x, a1, a2);
    return a1;
  }
};
int main(int argc, char* argv[])
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  float mini = nt2::Minlog<float>();
  float maxi = nt2::Maxlog<float>();
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);

  nt2::exhaustive_test<n_t> ( mini
                            , maxi
                            , my_sinhcosh2()
                            , raw_cosh()
                            );
  nt2::exhaustive_test<n_t> ( mini
                            , maxi
                            , my_sinhcosh1()
                            , raw_sinh()
                            );

  return 0;
}
