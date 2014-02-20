//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/expx2.hpp>
#include <nt2/include/constants/minlog.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/functions/sqrt.hpp>
extern "C" { double cephes_expx2(double x);}

#include <nt2/sdk/unit/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

struct raw_expx2
{
  float operator()(float x) const
  {
    return ::cephes_expx2(double(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = sqrt(nt2::Minlog<float>());
  float maxi = sqrt(nt2::Maxlog<float>());
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> ( mini
                              , maxi
                              , nt2::functor<nt2::tag::expx2_>()
                              , raw_expx2()
                              );

  return 0;
}
