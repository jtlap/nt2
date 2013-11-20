//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/exhaustive.hpp>
#include <nt2/include/functions/abs.hpp>
#include <cmath>

#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

struct raw_abs
{
  float operator()(float x) const
  {
    return std::abs(x);
  }
};

int main()
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;

  nt2::exhaustive_test<n_t> ( nt2::Valmin<float>()
                            , nt2::Valmax<float>()
                            , nt2::functor<nt2::tag::abs_>()
                            , raw_abs()
                            );

  return 0;
}
