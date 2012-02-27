/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::hierarchy_of for as_<native<T> >"

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

#include <iostream>

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)
////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for ref, value and const ref
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(hierarchy_of_ref_cref, BOOST_SIMD_TYPES)
{
  using boost::is_same;
  using namespace boost::simd::meta;
  using namespace boost::dispatch::meta;

  typedef typename hierarchy_of<as_<T> >::type        hvalue;
  typedef typename hierarchy_of<as_<T>& >::type       rvalue;
  typedef typename hierarchy_of<as_<T>const&  >::type crvalue;

  NT2_TEST( (is_same<hvalue, rvalue>::value) );
  NT2_TEST( (is_same<hvalue, crvalue>::value) );
}
/*
NT2_TEST_CASE(hierarchy_of_ints64)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::int64_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int64_< as_<boost::simd::int64_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints64_< as_<boost::simd::int64_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_< as_<boost::simd::int64_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_< as_<boost::simd::int64_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_< as_<boost::simd::int64_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::int64_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::int64_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::int64_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::int64_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int64_< as_<boost::simd::int64_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints64_< as_<boost::simd::int64_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_< as_<boost::simd::int64_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_< as_<boost::simd::int64_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_< as_<boost::simd::int64_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::int64_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::int64_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::int64_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::int64_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<boost::simd::int64_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints64)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::uint64_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint64_< as_<boost::simd::uint64_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints64_< as_<boost::simd::uint64_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_< as_<boost::simd::uint64_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_< as_<boost::simd::uint64_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_< as_<boost::simd::uint64_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::uint64_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::uint64_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::uint64_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::uint64_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint64_< as_<boost::simd::uint64_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints64_< as_<boost::simd::uint64_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_< as_<boost::simd::uint64_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_< as_<boost::simd::uint64_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_< as_<boost::simd::uint64_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::uint64_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::uint64_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::uint64_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::uint64_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<boost::simd::uint64_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints32)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::int32_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int32_< as_<boost::simd::int32_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints32_< as_<boost::simd::int32_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type32_< as_<boost::simd::int32_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_< as_<boost::simd::int32_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_< as_<boost::simd::int32_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::int32_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::int32_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::int32_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::int32_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int32_< as_<boost::simd::int32_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints32_< as_<boost::simd::int32_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type32_< as_<boost::simd::int32_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_< as_<boost::simd::int32_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_< as_<boost::simd::int32_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::int32_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::int32_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::int32_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::int32_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<boost::simd::int32_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints32)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::uint32_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint32_< as_<boost::simd::uint32_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints32_< as_<boost::simd::uint32_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type32_< as_<boost::simd::uint32_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_< as_<boost::simd::uint32_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_< as_<boost::simd::uint32_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<boost::simd::uint32_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<boost::simd::uint32_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<boost::simd::uint32_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<boost::simd::uint32_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint32_< as_<boost::simd::uint32_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints32_< as_<boost::simd::uint32_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type32_< as_<boost::simd::uint32_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_< as_<boost::simd::uint32_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_< as_<boost::simd::uint32_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<boost::simd::uint32_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<boost::simd::uint32_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<boost::simd::uint32_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<boost::simd::uint32_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<boost::simd::uint32_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints16)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::int16_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int16_<as_<boost::simd::int16_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints16_<as_<boost::simd::int16_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type16_<as_<boost::simd::int16_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_<as_<boost::simd::int16_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<boost::simd::int16_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::int16_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::int16_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::int16_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::int16_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int16_<as_<boost::simd::int16_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints16_<as_<boost::simd::int16_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type16_<as_<boost::simd::int16_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_<as_<boost::simd::int16_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<boost::simd::int16_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::int16_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::int16_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::int16_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::int16_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<boost::simd::int16_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints16)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::uint16_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint16_<as_<boost::simd::uint16_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints16_<as_<boost::simd::uint16_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type16_<as_<boost::simd::uint16_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_<as_<boost::simd::uint16_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_<as_<boost::simd::uint16_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::uint16_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::uint16_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::uint16_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::uint16_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint16_<as_<boost::simd::uint16_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints16_<as_<boost::simd::uint16_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type16_<as_<boost::simd::uint16_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_<as_<boost::simd::uint16_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_<as_<boost::simd::uint16_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::uint16_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::uint16_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::uint16_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::uint16_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<boost::simd::uint16_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints8)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::int8_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int8_<as_<boost::simd::int8_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints8_<as_<boost::simd::int8_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type8_<as_<boost::simd::int8_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_<as_<boost::simd::int8_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<boost::simd::int8_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::int8_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::int8_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::int8_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::int8_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int8_<as_<boost::simd::int8_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints8_<as_<boost::simd::int8_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type8_<as_<boost::simd::int8_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_<as_<boost::simd::int8_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<boost::simd::int8_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::int8_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::int8_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::int8_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::int8_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<boost::simd::int8_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints8)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<boost::simd::uint8_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint8_<as_<boost::simd::uint8_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints8_<as_<boost::simd::uint8_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type8_<as_<boost::simd::uint8_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_<as_<boost::simd::uint8_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_<as_<boost::simd::uint8_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<boost::simd::uint8_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<boost::simd::uint8_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<boost::simd::uint8_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<boost::simd::uint8_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint8_<as_<boost::simd::uint8_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints8_<as_<boost::simd::uint8_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type8_<as_<boost::simd::uint8_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_<as_<boost::simd::uint8_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_<as_<boost::simd::uint8_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<boost::simd::uint8_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<boost::simd::uint8_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<boost::simd::uint8_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<boost::simd::uint8_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<boost::simd::uint8_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_double)
{
  using boost::is_same;
  using namespace boost::simd::meta;

  typedef hierarchy_of< as_<double> >::type base;

  NT2_TEST( (is_same<target_<scalar_<double_<as_<double> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_<as_<double> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_<as_<double> >        > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<double> >      > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<double> >  > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<double> > > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<double> > > > , UP(base,6) >::value) );

  NT2_TEST( (is_same<target_<generic_<double_<as_<double> >      > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_<as_<double> >      > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_<as_<double> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<double> >      > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<double> >  > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<double> > > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<double> > > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<double> > >            , UP(base,14) >::value) );
}
*/

NT2_TEST_CASE(hierarchy_of_float)
{
  using boost::is_same;
  //using boost::simd::meta;
  //using namespace boost::simd;
  //using namespace boost::dispatch::meta;
  using boost::dispatch::meta::target_;
  using boost::dispatch::meta::simd_;
  using boost::dispatch::meta::as_;
  using boost::dispatch::meta::generic_;
  using boost::dispatch::meta::hierarchy_of;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<float,ext_t> dst_t;

  typedef hierarchy_of< as_<dst_t> >::type base;

  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::single_<as_<dst_t> >,ext_t> >, base >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::type32_<as_<dst_t> >,ext_t      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::floating_sized_< as_<dst_t> >,ext_t > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::floating_<as_<dst_t> >,ext_t        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::signed_<as_<dst_t> >,ext_t      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::arithmetic_<as_<dst_t> >,ext_t  > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::fundamental_<as_<dst_t> >,ext_t > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<simd_<boost::dispatch::meta::unspecified_<as_<dst_t> >,ext_t > > , UP(base,7) >::value) );

  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::single_<as_<dst_t> >       > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::type32_<as_<dst_t> >      > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::floating_sized_<as_<dst_t> >  > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::floating_<as_<dst_t> >        > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::signed_<as_<dst_t> >      > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::arithmetic_<as_<dst_t> >  > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::fundamental_<as_<dst_t> > > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<boost::dispatch::meta::unspecified_<as_<dst_t> > > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<boost::dispatch::meta::unspecified_<as_<dst_t> > >            , UP(base,16) >::value) );
}
