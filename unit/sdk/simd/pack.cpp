/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::simd::pack"

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

boost::proto::terminal< nt2::constants::constant_< nt2::constants::digit_<12> > >::type zero_ = {{}};
boost::proto::terminal< nt2::constants::constant_< nt2::constants::pi_ > >::type pi_ = {{}};

////////////////////////////////////////////////////////////////////////////////
// Test pack default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(pack_default_ctor, (float) )//NT2_SIMD_TYPES )
{
  using nt2::simd::pack;
  pack<int> x(0),z(10);
  x = z+pi_;

  std::cout << x << "\n";
}

NT2_TEST_CASE_TPL(pack_default_ctor2, (float) )//NT2_SIMD_TYPES )
{
  using nt2::simd::pack;

  pack<int,3> y;
  y = y+pi_;

  std::cout << y << "\n";
}
