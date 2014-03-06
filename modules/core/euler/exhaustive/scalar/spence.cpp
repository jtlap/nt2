//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/spence.hpp>

#include <nt2/sdk/unit/exhaustive.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

extern "C" { double cephes_spence(double x); }


struct raw_spence
{
  float operator()(float x) const
  {
    return ::cephes_spence(double(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = nt2::Zero<float>();
  float maxi = nt2::Valmax<float>();
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> ( mini
                              , maxi
                              , nt2::functor<nt2::tag::spence_>()
                              , raw_spence()
                              );

  return 0;
}
