//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/rec.hpp>

#include <nt2/sdk/unit/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>
#include <cmath>

struct raw_hypot
{
  float operator()(float x) const
  {
    return ::hypotf(x, nt2::rec(x));
  }
};
struct hypot0
{
  float operator()(float x) const
  {
    return boost::simd::hypot(x, nt2::rec(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = nt2::Valmin<float>();
  float maxi = nt2::Valmax<float>();
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> (  mini
                              , maxi
                              , hypot0()
                              , raw_hypot()
                              );

  return 0;
}
