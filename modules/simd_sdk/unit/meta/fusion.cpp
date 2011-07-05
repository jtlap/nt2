/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::hierarchy_of for fusion types"

#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <boost/simd/sdk/meta/fusion.hpp>
#include <boost/simd/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for ref, value and const ref
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL(hierarchy_of_ref_cref, BOOST_SIMD_TYPES)
{
  using boost::array;
  using boost::is_same;
  using namespace boost::meta;

  typedef array<T,7> base;
  typedef typename hierarchy_of<base>::type        hvalue;
  typedef typename hierarchy_of<base&>::type       rvalue;
  typedef typename hierarchy_of<base const&>::type crvalue;

  BOOST_SIMD_TEST( (is_same<hvalue, rvalue>::value) );
  BOOST_SIMD_TEST( (is_same<hvalue, crvalue>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for array
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(hierarchy_of_array)
{
  using boost::array;
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< array<double,7> >::type base;

  BOOST_SIMD_TEST( (is_same<array_<scalar_<double_< array<double,7> > >, 7  >      , base >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<type64_< array<double,7> > >, 7  >      , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<real_< array<double,7> > >, 7  >        , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<signed_< array<double,7> > >, 7  >      , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<arithmetic_< array<double,7> > >, 7  >  , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<fundamental_< array<double,7> > >, 7  > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<scalar_<unspecified_< array<double,7> > >, 7  > , UP(base,6) >::value) );

  BOOST_SIMD_TEST( (is_same<array_<generic_<double_< array<double,7> > >, 7  >      , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<type64_< array<double,7> > >, 7  >      , UP(base,8) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<real_< array<double,7> > >, 7  >        , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<signed_< array<double,7> > >, 7  >      , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<arithmetic_< array<double,7> > >, 7  >  , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<fundamental_< array<double,7> > >, 7  > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<generic_<unspecified_< array<double,7> > >, 7  > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<array_<unspecified_< array<double,7> >, 7  >            , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<fusion_sequence_< array<double,7> >                     , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_< array<double,7> >                         , UP(base,16) >::value) );
}

