/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::hierarchy_of for as_<T>"

#include <boost/simd/sdk/meta/as.hpp>
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
  using boost::is_same;
  using namespace boost::meta;

  typedef typename hierarchy_of<as_<T> >::type        hvalue;
  typedef typename hierarchy_of<as_<T>& >::type       rvalue;
  typedef typename hierarchy_of<as_<T>const&  >::type crvalue;

  BOOST_SIMD_TEST( (is_same<hvalue, rvalue>::value) );
  BOOST_SIMD_TEST( (is_same<hvalue, crvalue>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for basic types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(hierarchy_of_bool)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<bool> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<bool_< as_<bool> >        > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_< as_<bool> > > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_< as_<bool> > > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<bool_< as_<bool> >       > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_< as_<bool> > > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_< as_<bool> > > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_< as_<bool> > >           , UP(base,6) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_void)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<void> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<void_<as_<void> >          > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<void> >   > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<void> >   > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<void_<as_<void> >         > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<void> >  > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<void> >  > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<void> > >             , UP(base,6) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints64)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::int64_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<int64_< as_<boost::simd::int64_t> >       > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints64_< as_<boost::simd::int64_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type64_< as_<boost::simd::int64_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<int_< as_<boost::simd::int64_t> >         > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_< as_<boost::simd::int64_t> >      > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::int64_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::int64_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::int64_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::int64_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<int64_< as_<boost::simd::int64_t> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints64_< as_<boost::simd::int64_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type64_< as_<boost::simd::int64_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<int_< as_<boost::simd::int64_t> >          > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_< as_<boost::simd::int64_t> >       > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::int64_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::int64_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::int64_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::int64_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_< as_<boost::simd::int64_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints64)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::uint64_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint64_< as_<boost::simd::uint64_t> >      > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints64_< as_<boost::simd::uint64_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type64_< as_<boost::simd::uint64_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint_< as_<boost::simd::uint64_t> >        > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unsigned_< as_<boost::simd::uint64_t> >    > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::uint64_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::uint64_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::uint64_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::uint64_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<uint64_< as_<boost::simd::uint64_t> >       > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints64_< as_<boost::simd::uint64_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type64_< as_<boost::simd::uint64_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<uint_< as_<boost::simd::uint64_t> >         > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unsigned_< as_<boost::simd::uint64_t> >     > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::uint64_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::uint64_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::uint64_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::uint64_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_< as_<boost::simd::uint64_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints32)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::int32_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<int32_< as_<boost::simd::int32_t> >       > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints32_< as_<boost::simd::int32_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type32_< as_<boost::simd::int32_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<int_< as_<boost::simd::int32_t> >         > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_< as_<boost::simd::int32_t> >      > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::int32_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::int32_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::int32_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::int32_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<int32_< as_<boost::simd::int32_t> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints32_< as_<boost::simd::int32_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type32_< as_<boost::simd::int32_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<int_< as_<boost::simd::int32_t> >          > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_< as_<boost::simd::int32_t> >       > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::int32_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::int32_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::int32_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::int32_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_< as_<boost::simd::int32_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints32)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::uint32_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint32_< as_<boost::simd::uint32_t> >      > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints32_< as_<boost::simd::uint32_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type32_< as_<boost::simd::uint32_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint_< as_<boost::simd::uint32_t> >        > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unsigned_< as_<boost::simd::uint32_t> >    > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::uint32_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::uint32_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::uint32_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::uint32_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<uint32_< as_<boost::simd::uint32_t> >       > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints32_< as_<boost::simd::uint32_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type32_< as_<boost::simd::uint32_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<uint_< as_<boost::simd::uint32_t> >         > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unsigned_< as_<boost::simd::uint32_t> >     > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::uint32_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::uint32_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::uint32_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::uint32_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_< as_<boost::simd::uint32_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints16)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::int16_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<int16_<as_<boost::simd::int16_t> >       > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints16_<as_<boost::simd::int16_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type16_<as_<boost::simd::int16_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<int_<as_<boost::simd::int16_t> >         > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_<as_<boost::simd::int16_t> >      > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::int16_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::int16_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::int16_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::int16_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<int16_<as_<boost::simd::int16_t> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints16_<as_<boost::simd::int16_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type16_<as_<boost::simd::int16_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<int_<as_<boost::simd::int16_t> >          > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_<as_<boost::simd::int16_t> >       > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::int16_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::int16_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::int16_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::int16_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<boost::simd::int16_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints16)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::uint16_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint16_<as_<boost::simd::uint16_t> >      > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints16_<as_<boost::simd::uint16_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type16_<as_<boost::simd::uint16_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint_<as_<boost::simd::uint16_t> >        > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unsigned_<as_<boost::simd::uint16_t> >    > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::uint16_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::uint16_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::uint16_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::uint16_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<uint16_<as_<boost::simd::uint16_t> >       > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints16_<as_<boost::simd::uint16_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type16_<as_<boost::simd::uint16_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<uint_<as_<boost::simd::uint16_t> >         > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unsigned_<as_<boost::simd::uint16_t> >     > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::uint16_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::uint16_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::uint16_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::uint16_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<boost::simd::uint16_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints8)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::int8_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<int8_<as_<boost::simd::int8_t> >       > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints8_<as_<boost::simd::int8_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type8_<as_<boost::simd::int8_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<int_<as_<boost::simd::int8_t> >         > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_<as_<boost::simd::int8_t> >      > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::int8_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::int8_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::int8_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::int8_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<int8_<as_<boost::simd::int8_t> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints8_<as_<boost::simd::int8_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type8_<as_<boost::simd::int8_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<int_<as_<boost::simd::int8_t> >          > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_<as_<boost::simd::int8_t> >       > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::int8_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::int8_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::int8_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::int8_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<boost::simd::int8_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints8)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<boost::simd::uint8_t> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint8_<as_<boost::simd::uint8_t> >      > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<ints8_<as_<boost::simd::uint8_t> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type8_<as_<boost::simd::uint8_t> >      > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<uint_<as_<boost::simd::uint8_t> >        > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unsigned_<as_<boost::simd::uint8_t> >    > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::uint8_t> >     > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::uint8_t> >  > > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::uint8_t> > > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::uint8_t> > > > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<uint8_<as_<boost::simd::uint8_t> >       > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<ints8_<as_<boost::simd::uint8_t> >       > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type8_<as_<boost::simd::uint8_t> >       > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<uint_<as_<boost::simd::uint8_t> >         > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unsigned_<as_<boost::simd::uint8_t> >     > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::uint8_t> >      > > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::uint8_t> >   > > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::uint8_t> >  > > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::uint8_t> >  > > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<boost::simd::uint8_t> > >             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_double)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<double> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<double_<as_<double> >      > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type64_<as_<double> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<real_<as_<double> >        > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_<as_<double> >      > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<double> >  > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<double> > > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<double> > > > , UP(base,6) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<double_<as_<double> >      > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type64_<as_<double> >      > > , UP(base,8) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<real_<as_<double> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_<as_<double> >      > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<double> >  > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<double> > > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<double> > > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<double> > >            , UP(base,14) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_float)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of< as_<float> >::type base;

  BOOST_SIMD_TEST( (is_same<target_<scalar_<float_<as_<float> >       > > , base >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<type32_<as_<float> >      > > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<real_<as_<float> >        > > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<signed_<as_<float> >      > > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<arithmetic_<as_<float> >  > > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<fundamental_<as_<float> > > > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<scalar_<unspecified_<as_<float> > > > , UP(base,6) >::value) );

  BOOST_SIMD_TEST( (is_same<target_<generic_<float_<as_<float> >       > > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<type32_<as_<float> >      > > , UP(base,8) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<real_<as_<float> >        > > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<signed_<as_<float> >      > > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<arithmetic_<as_<float> >  > > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<fundamental_<as_<float> > > > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<generic_<unspecified_<as_<float> > > > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<target_<unspecified_<as_<float> > >            , UP(base,14) >::value) );
}
