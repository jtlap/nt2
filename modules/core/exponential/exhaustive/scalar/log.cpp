//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/log.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/valmax.hpp>

#include <nt2/sdk/unit/exhaustive.hpp>
#include <cmath>
#include <cstdlib>

struct raw_log
{
  float operator()(float x) const
  {
    return std::log(double(x));
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
                              , nt2::functor<nt2::tag::log_>()
                              , raw_log()
                              );

  return 0;
}
