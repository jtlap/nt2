//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        J.T. Lapreste
//         Copyright 2014        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gamma.hpp>
#include <nt2/sdk/unit/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>


struct raw_gamma
{
  float operator()(float x) const
  {
    return nt2::gamma(double(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = -36.0f;
  float maxi = 36.0f;
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> ( mini
                              , maxi
                              , nt2::functor<nt2::tag::gamma_>()
                              , raw_gamma()
                              );

  return 0;
}
