//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/digamma.hpp>
#include <nt2/include/constants/smallestposval.hpp>

#include <nt2/sdk/exhaustive/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>
#include <boost/math/special_functions/digamma.hpp>
#include <nt2/sdk/error/policies.hpp>
struct raw_digamma
{
  float operator()(float x) const
  {
    return float(boost::math::digamma(x, nt2::nt2_policy()));
  }
};

int main(int argc, char* argv[])
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  float mini = nt2::Smallestposval<float>();
  float maxi = 30.0f;
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);

  nt2::exhaustive_test<n_t> ( mini
                            , maxi
                            , nt2::functor<nt2::tag::digamma_>()
                            , raw_digamma()
                            );

  return 0;
}
