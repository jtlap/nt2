/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::hierarchy_of for as_<T>"

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for ref, value and const ref
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(hierarchy_of_ref_cref, NT2_TYPES)
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;

  typedef typename hierarchy_of<as_<T> >::type        hvalue;
  typedef typename hierarchy_of<as_<T>& >::type       rvalue;
  typedef typename hierarchy_of<as_<T>const&  >::type crvalue;

  NT2_TEST_EXPR_TYPE( rvalue(),  _, hvalue );
  NT2_TEST_EXPR_TYPE( crvalue(), _, hvalue );
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for basic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(hierarchy_of_bool)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<bool> >::type base;

  NT2_TEST( (is_same<target_<scalar_<bool_< as_<bool> >        > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<bool> > > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<bool> > > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<generic_<bool_< as_<bool> >       > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<bool> > > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<bool> > > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<bool> > >           , UP(base,6) >::value) );
}

NT2_TEST_CASE(hierarchy_of_void)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<void> >::type base;

  NT2_TEST( (is_same<target_<scalar_<void_<as_<void> >          > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<void> >   > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<void> >   > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<generic_<void_<as_<void> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<void> >  > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<void> >  > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<void> > >             , UP(base,6) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints64)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::int64_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int64_< as_<nt2::int64_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints64_< as_<nt2::int64_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_< as_<nt2::int64_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_< as_<nt2::int64_t> >  > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_< as_<nt2::int64_t> >         > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_< as_<nt2::int64_t> >      > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<nt2::int64_t> >     > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<nt2::int64_t> >  > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<nt2::int64_t> > > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<nt2::int64_t> > > > , UP(base,9) >::value) );

  NT2_TEST( (is_same<target_<generic_<int64_< as_<nt2::int64_t> >        > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints64_< as_<nt2::int64_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_< as_<nt2::int64_t> >       > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_< as_<nt2::int64_t> >   > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_< as_<nt2::int64_t> >          > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_< as_<nt2::int64_t> >       > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<nt2::int64_t> >      > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<nt2::int64_t> >   > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<nt2::int64_t> >  > > , UP(base,18) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<nt2::int64_t> >  > > , UP(base,19) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<nt2::int64_t> > >             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints64)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::uint64_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint64_< as_<nt2::uint64_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints64_< as_<nt2::uint64_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_< as_<nt2::uint64_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_< as_<nt2::uint64_t> >  > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_< as_<nt2::uint64_t> >        > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_< as_<nt2::uint64_t> >    > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<nt2::uint64_t> >     > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<nt2::uint64_t> >  > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<nt2::uint64_t> > > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<nt2::uint64_t> > > > , UP(base,9) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint64_< as_<nt2::uint64_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints64_< as_<nt2::uint64_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_< as_<nt2::uint64_t> >       > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_< as_<nt2::uint64_t> >   > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_< as_<nt2::uint64_t> >         > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_< as_<nt2::uint64_t> >     > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<nt2::uint64_t> >      > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<nt2::uint64_t> >   > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<nt2::uint64_t> >  > > , UP(base,18) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<nt2::uint64_t> >  > > , UP(base,19) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<nt2::uint64_t> > >             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints32)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::int32_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int32_< as_<nt2::int32_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints32_< as_<nt2::int32_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type32_< as_<nt2::int32_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_< as_<nt2::int32_t> >  > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_< as_<nt2::int32_t> >         > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_< as_<nt2::int32_t> >      > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<nt2::int32_t> >     > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<nt2::int32_t> >  > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<nt2::int32_t> > > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<nt2::int32_t> > > > , UP(base,9) >::value) );

  NT2_TEST( (is_same<target_<generic_<int32_< as_<nt2::int32_t> >        > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints32_< as_<nt2::int32_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<type32_< as_<nt2::int32_t> >       > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_< as_<nt2::int32_t> >   > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_< as_<nt2::int32_t> >          > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_< as_<nt2::int32_t> >       > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<nt2::int32_t> >      > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<nt2::int32_t> >   > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<nt2::int32_t> >  > > , UP(base,18) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<nt2::int32_t> >  > > , UP(base,19) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<nt2::int32_t> > >             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints32)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::uint32_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint32_< as_<nt2::uint32_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints32_< as_<nt2::uint32_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type32_< as_<nt2::uint32_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_< as_<nt2::uint32_t> >  > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_< as_<nt2::uint32_t> >        > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_< as_<nt2::uint32_t> >    > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_< as_<nt2::uint32_t> >     > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_< as_<nt2::uint32_t> >  > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_< as_<nt2::uint32_t> > > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_< as_<nt2::uint32_t> > > > , UP(base,9) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint32_< as_<nt2::uint32_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints32_< as_<nt2::uint32_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<type32_< as_<nt2::uint32_t> >       > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_< as_<nt2::uint32_t> >   > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_< as_<nt2::uint32_t> >         > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_< as_<nt2::uint32_t> >     > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_< as_<nt2::uint32_t> >      > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_< as_<nt2::uint32_t> >   > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_< as_<nt2::uint32_t> >  > > , UP(base,18) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_< as_<nt2::uint32_t> >  > > , UP(base,19) >::value) );
  NT2_TEST( (is_same<target_<unspecified_< as_<nt2::uint32_t> > >             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints16)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::int16_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int16_<as_<nt2::int16_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints16_<as_<nt2::int16_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type16_<as_<nt2::int16_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_<as_<nt2::int16_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<nt2::int16_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<nt2::int16_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<nt2::int16_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<nt2::int16_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<nt2::int16_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int16_<as_<nt2::int16_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints16_<as_<nt2::int16_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type16_<as_<nt2::int16_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_<as_<nt2::int16_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<nt2::int16_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<nt2::int16_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<nt2::int16_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<nt2::int16_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<nt2::int16_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<nt2::int16_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints16)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::uint16_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint16_<as_<nt2::uint16_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints16_<as_<nt2::uint16_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type16_<as_<nt2::uint16_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_<as_<nt2::uint16_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_<as_<nt2::uint16_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<nt2::uint16_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<nt2::uint16_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<nt2::uint16_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<nt2::uint16_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint16_<as_<nt2::uint16_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints16_<as_<nt2::uint16_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type16_<as_<nt2::uint16_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_<as_<nt2::uint16_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_<as_<nt2::uint16_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<nt2::uint16_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<nt2::uint16_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<nt2::uint16_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<nt2::uint16_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<nt2::uint16_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints8)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::int8_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<int8_<as_<nt2::int8_t> >       > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints8_<as_<nt2::int8_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type8_<as_<nt2::int8_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<int_<as_<nt2::int8_t> >         > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<nt2::int8_t> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<nt2::int8_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<nt2::int8_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<nt2::int8_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<nt2::int8_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<int8_<as_<nt2::int8_t> >        > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints8_<as_<nt2::int8_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type8_<as_<nt2::int8_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<int_<as_<nt2::int8_t> >          > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<nt2::int8_t> >       > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<nt2::int8_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<nt2::int8_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<nt2::int8_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<nt2::int8_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<nt2::int8_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints8)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<nt2::uint8_t> >::type base;

  NT2_TEST( (is_same<target_<scalar_<uint8_<as_<nt2::uint8_t> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<ints8_<as_<nt2::uint8_t> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<type8_<as_<nt2::uint8_t> >      > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<uint_<as_<nt2::uint8_t> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unsigned_<as_<nt2::uint8_t> >    > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<integer_<as_<nt2::uint8_t> >     > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<nt2::uint8_t> >  > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<nt2::uint8_t> > > > , UP(base,7) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<nt2::uint8_t> > > > , UP(base,8) >::value) );

  NT2_TEST( (is_same<target_<generic_<uint8_<as_<nt2::uint8_t> >       > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<ints8_<as_<nt2::uint8_t> >       > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<type8_<as_<nt2::uint8_t> >       > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<uint_<as_<nt2::uint8_t> >         > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<unsigned_<as_<nt2::uint8_t> >     > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<integer_<as_<nt2::uint8_t> >      > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<nt2::uint8_t> >   > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<nt2::uint8_t> >  > > , UP(base,16) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<nt2::uint8_t> >  > > , UP(base,17) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<nt2::uint8_t> > >             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_double)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<double> >::type base;

  NT2_TEST( (is_same<target_<scalar_<double_<as_<double> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<type64_<as_<double> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_<as_<double> >  > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_<as_<double> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<double> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<double> >  > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<double> > > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<double> > > > , UP(base,7) >::value) );

  NT2_TEST( (is_same<target_<generic_<double_<as_<double> >      > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<generic_<type64_<as_<double> >      > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_<as_<double> >  > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_<as_<double> >        > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<double> >      > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<double> >  > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<double> > > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<double> > > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<double> > >            , UP(base,16) >::value) );
}

NT2_TEST_CASE(hierarchy_of_float)
{
  using boost::is_same;
  using nt2::meta::as_;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of< as_<float> >::type base;

  NT2_TEST( (is_same<target_<scalar_<single_<as_<float> >      > > , base >::value) );
  NT2_TEST( (is_same<target_<scalar_<type32_<as_<float> >      > > , UP(base,1) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_sized_<as_<float> >  > > , UP(base,2) >::value) );
  NT2_TEST( (is_same<target_<scalar_<floating_<as_<float> >        > > , UP(base,3) >::value) );
  NT2_TEST( (is_same<target_<scalar_<signed_<as_<float> >      > > , UP(base,4) >::value) );
  NT2_TEST( (is_same<target_<scalar_<arithmetic_<as_<float> >  > > , UP(base,5) >::value) );
  NT2_TEST( (is_same<target_<scalar_<fundamental_<as_<float> > > > , UP(base,6) >::value) );
  NT2_TEST( (is_same<target_<scalar_<unspecified_<as_<float> > > > , UP(base,7) >::value) );

  NT2_TEST( (is_same<target_<generic_<single_<as_<float> >      > > , UP(base,8) >::value) );
  NT2_TEST( (is_same<target_<generic_<type32_<as_<float> >      > > , UP(base,9) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_sized_<as_<float> >  > > , UP(base,10) >::value) );
  NT2_TEST( (is_same<target_<generic_<floating_<as_<float> >        > > , UP(base,11) >::value) );
  NT2_TEST( (is_same<target_<generic_<signed_<as_<float> >      > > , UP(base,12) >::value) );
  NT2_TEST( (is_same<target_<generic_<arithmetic_<as_<float> >  > > , UP(base,13) >::value) );
  NT2_TEST( (is_same<target_<generic_<fundamental_<as_<float> > > > , UP(base,14) >::value) );
  NT2_TEST( (is_same<target_<generic_<unspecified_<as_<float> > > > , UP(base,15) >::value) );
  NT2_TEST( (is_same<target_<unspecified_<as_<float> > >            , UP(base,16) >::value) );
}
