/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::logical_and on SIMD types"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test behavior for logical_and
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( logical_and, NT2_SIMD_TYPES )
{
  using boost::is_same;
  using nt2::tag::logical_and_;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 n_t;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<logical_and_(n_t,n_t)>::type
                            , n_t
                            >::value
            )
          );

  NT2_ALIGNED_TYPE(T) odd[cardinal_of<n_t>::value];
  NT2_ALIGNED_TYPE(T) even[cardinal_of<n_t>::value];
  for(std::size_t i=0;i<cardinal_of<n_t>::value;++i)
  {
    odd[i] = i % 2; even[i] = (i+1)%2;
  }

  n_t o = nt2::load<n_t>(&odd[0],0);
  n_t e = nt2::load<n_t>(&even[0],0);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
  {
    NT2_TEST_EQUAL( !!(o && o)[j]               , (o[j] && o[j]) );
    NT2_TEST_EQUAL( !!(nt2::logical_and(o,o))[j], (o[j] && o[j]) );
    NT2_TEST_EQUAL( !!(nt2::l_and(o,o))[j]      , (o[j] && o[j]) );
    NT2_TEST_EQUAL( !!(o && e)[j]               , (o[j] && e[j]) );
    NT2_TEST_EQUAL( !!(nt2::logical_and(o,e))[j], (o[j] && e[j]) );
    NT2_TEST_EQUAL( !!(nt2::l_and(o,e))[j]      , (o[j] && e[j]) );
  }
}
