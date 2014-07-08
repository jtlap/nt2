//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        J.T. Lapreste
//         Copyright 2014        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/sdk/exhaustive/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

extern "C" { double cephes_lgam(double x); }
extern "C" { float cephes_lgamf(float x); }

struct raw_gammaln
{
  float operator()(float x) const
  {
    return ::cephes_lgam(double(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = 0.0f;
  float maxi = 2.035093e36f;
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> ( mini
                              , maxi
                              , nt2::functor<nt2::tag::gammaln_>()
                              , raw_gammaln()
                              );

  return 0;
}
