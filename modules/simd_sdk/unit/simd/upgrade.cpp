/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::upgrade SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(upgrade, NT2_SIMD_TYPES)
{
  using nt2::simd::native;
  using nt2::meta::upgrade;
  using boost::is_same;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             native_t;
  typedef typename upgrade<T>::type base_t;

  typedef typename
  boost::mpl::if_ < nt2::meta::is_vectorizable<base_t,ext_t>
                  , base_t
                  , typename native_t::value_type
                  >::type upgraded_t;

  NT2_TEST( (is_same< typename upgrade<native_t>::type::value_type
                    , upgraded_t
                    >::value ));
}

