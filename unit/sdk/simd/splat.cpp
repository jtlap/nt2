/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::splat SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test behavior for splat
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( splat, NT2_SIMD_TYPES )
{
  using boost::is_same;
  using nt2::tag::splat_;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  using nt2::meta::scalar_of;
  using nt2::meta::as_;

  typedef NT2_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<T,ext_t>                       n_t;
  typedef typename scalar_of<n_t>::type         s_t;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<splat_(s_t, as_<n_t>)>::type
                            , n_t
                            >::value
            )
          );

  nt2::uint64_t values[] =
  {
      0x00, 0x01, 0x7F, 0xFF,
      0xFF00U, 0xFF01U, 0x7FFFU, 0xFFFFU,
      0xFFFFFF00UL, 0xFFFFFF01UL, 0x7FFFFFFFUL, 0xFFFFFFFFUL,
      0xFFFFFFFFFFFFFF00ULL, 0xFFFFFFFFFFFFFF01ULL, 0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL
  };
  for(std::size_t j=0; j<sizeof values/sizeof values[0]; ++j)
  {
    n_t v = nt2::splat<n_t>(values[j]);
    for(std::size_t i=0;i<cardinal_of<n_t>::value;++i)
         NT2_TEST_EQUAL(v[i], s_t(values[j]));
  }
}

