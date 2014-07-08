//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/constants/minlog10.hpp>
#include <nt2/include/constants/maxlog10.hpp>

#include <nt2/sdk/exhaustive/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

struct raw_exp10
{
  float operator()(float x) const
  {
    return float(::exp10(double(x)));
  }
};

int main(int argc, char* argv[])
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  float mini = nt2::Minlog10<float>(); // exp10 is 0 under
  float maxi = nt2::Maxlog10<float>(); // exp10 is inf above
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);

  nt2::exhaustive_test<n_t> ( mini
                            , maxi
                            , nt2::functor<nt2::tag::exp10_>()
                            , raw_exp10()
                            );

  return 0;
}


