//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rng.hpp>
#include <nt2/include/functions/randi.hpp>
#include <nt2/core/utility/lagged_fibonacci2281stream.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( rng_save_restore )
{
  nt2::rng_settings prev = nt2::rng();

  int i = nt2::randi(1000);

  nt2::rng(prev);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);

  nt2::rng(prev);
}

NT2_TEST_CASE( rng_seed )
{
  nt2::rng_settings prev = nt2::rng();
  nt2::rng(1337);
  int i = nt2::randi(1000);

  nt2::rng(1337);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);

  nt2::rng(prev);
}

NT2_TEST_CASE( rng_shuffle )
{
  nt2::rng_settings prev = nt2::rng();
  nt2::rng_settings shuffled = nt2::rng(nt2::shuffle_);
  int i = nt2::randi(1000);

  nt2::rng(shuffled);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);

  nt2::rng(prev);
}

NT2_TEST_CASE( rng_default )
{
  nt2::rng_settings prev = nt2::rng();
  int i = nt2::randi(1000);

  nt2::rng(nt2::default_);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);

  nt2::rng(prev);
}

NT2_TEST_CASE( rng_seed_generator )
{
  nt2::rng_settings prev = nt2::rng();

  nt2::rng_settings set = nt2::rng(1337, nt2::lagged_fibonacci2281stream() );
  int i = nt2::randi(1000);

  nt2::rng(set);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);

  nt2::rng(prev);
}

NT2_TEST_CASE( rng_shuffled_generator )
{
  nt2::rng_settings set = nt2::rng(nt2::shuffle_, nt2::lagged_fibonacci2281stream() );
  int i = nt2::randi(1000);

  nt2::rng(set);
  int j = nt2::randi(1000);

  NT2_TEST_EQUAL(i,j);
}
