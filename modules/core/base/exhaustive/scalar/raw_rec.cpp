//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/raw_rec.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

#include <nt2/sdk/exhaustive/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

struct raw_rec
{
  float operator()(float x) const
  {
    return 1.f/x;
  }
};

int main()
{
  nt2::exhaustive_test<float> ( nt2::Valmin<float>()
                              , nt2::Valmax<float>()
                              , nt2::functor<nt2::tag::raw_rec_>()
                              , raw_rec()
                              );

  return 0;
}
