/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::hierarchy_of"

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

  typedef typename hierarchy_of<T>::type        hvalue;
  typedef typename hierarchy_of<T&>::type       rvalue;
  typedef typename hierarchy_of<T const&>::type crvalue;

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

  typedef hierarchy_of<bool>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<bool_<bool>          > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<bool>   > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<bool>   > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<bool_<bool>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<bool>  > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<bool>  > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<bool>             , UP(base,6) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_void)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<void>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<void_<void>          > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<void>   > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<void>   > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<void_<void>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<void>  > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<void>  > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<void>             , UP(base,6) >::value) );
}
BOOST_SIMD_TEST_CASE(hierarchy_of_ints64)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::int64_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<int64_<boost::simd::int64_t>       > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints64_<boost::simd::int64_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type64_<boost::simd::int64_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<int_<boost::simd::int64_t>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<boost::simd::int64_t>      > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::int64_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::int64_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::int64_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::int64_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<int64_<boost::simd::int64_t>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints64_<boost::simd::int64_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type64_<boost::simd::int64_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<int_<boost::simd::int64_t>          > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<boost::simd::int64_t>       > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::int64_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::int64_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::int64_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::int64_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::int64_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints64)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::uint64_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<uint64_<boost::simd::uint64_t>      > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints64_<boost::simd::uint64_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type64_<boost::simd::uint64_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<uint_<boost::simd::uint64_t>        > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unsigned_<boost::simd::uint64_t>    > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::uint64_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::uint64_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::uint64_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::uint64_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<uint64_<boost::simd::uint64_t>       > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints64_<boost::simd::uint64_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type64_<boost::simd::uint64_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<uint_<boost::simd::uint64_t>         > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unsigned_<boost::simd::uint64_t>     > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::uint64_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::uint64_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::uint64_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::uint64_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::uint64_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints32)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::int32_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<int32_<boost::simd::int32_t>       > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints32_<boost::simd::int32_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type32_<boost::simd::int32_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<int_<boost::simd::int32_t>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<boost::simd::int32_t>      > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::int32_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::int32_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::int32_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::int32_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<int32_<boost::simd::int32_t>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints32_<boost::simd::int32_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type32_<boost::simd::int32_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<int_<boost::simd::int32_t>          > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<boost::simd::int32_t>       > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::int32_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::int32_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::int32_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::int32_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::int32_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints32)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::uint32_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<uint32_<boost::simd::uint32_t>      > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints32_<boost::simd::uint32_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type32_<boost::simd::uint32_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<uint_<boost::simd::uint32_t>        > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unsigned_<boost::simd::uint32_t>    > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::uint32_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::uint32_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::uint32_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::uint32_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<uint32_<boost::simd::uint32_t>       > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints32_<boost::simd::uint32_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type32_<boost::simd::uint32_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<uint_<boost::simd::uint32_t>         > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unsigned_<boost::simd::uint32_t>     > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::uint32_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::uint32_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::uint32_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::uint32_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::uint32_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints16)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::int16_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<int16_<boost::simd::int16_t>       > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints16_<boost::simd::int16_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type16_<boost::simd::int16_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<int_<boost::simd::int16_t>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<boost::simd::int16_t>      > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::int16_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::int16_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::int16_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::int16_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<int16_<boost::simd::int16_t>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints16_<boost::simd::int16_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type16_<boost::simd::int16_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<int_<boost::simd::int16_t>          > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<boost::simd::int16_t>       > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::int16_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::int16_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::int16_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::int16_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::int16_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints16)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::uint16_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<uint16_<boost::simd::uint16_t>      > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints16_<boost::simd::uint16_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type16_<boost::simd::uint16_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<uint_<boost::simd::uint16_t>        > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unsigned_<boost::simd::uint16_t>    > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::uint16_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::uint16_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::uint16_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::uint16_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<uint16_<boost::simd::uint16_t>       > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints16_<boost::simd::uint16_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type16_<boost::simd::uint16_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<uint_<boost::simd::uint16_t>         > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unsigned_<boost::simd::uint16_t>     > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::uint16_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::uint16_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::uint16_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::uint16_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::uint16_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_ints8)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::int8_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<int8_<boost::simd::int8_t>       > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints8_<boost::simd::int8_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type8_<boost::simd::int8_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<int_<boost::simd::int8_t>         > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<boost::simd::int8_t>      > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::int8_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::int8_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::int8_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::int8_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<int8_<boost::simd::int8_t>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints8_<boost::simd::int8_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type8_<boost::simd::int8_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<int_<boost::simd::int8_t>          > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<boost::simd::int8_t>       > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::int8_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::int8_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::int8_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::int8_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::int8_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_uints8)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<boost::simd::uint8_t>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<uint8_<boost::simd::uint8_t>      > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<ints8_<boost::simd::uint8_t>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type8_<boost::simd::uint8_t>      > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<uint_<boost::simd::uint8_t>        > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unsigned_<boost::simd::uint8_t>    > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<integer_<boost::simd::uint8_t>     > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<boost::simd::uint8_t>  > , UP(base,6) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<boost::simd::uint8_t> > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<boost::simd::uint8_t> > , UP(base,8) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<uint8_<boost::simd::uint8_t>       > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<ints8_<boost::simd::uint8_t>       > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type8_<boost::simd::uint8_t>       > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<uint_<boost::simd::uint8_t>         > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unsigned_<boost::simd::uint8_t>     > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<integer_<boost::simd::uint8_t>      > , UP(base,14) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<boost::simd::uint8_t>   > , UP(base,15) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<boost::simd::uint8_t>  > , UP(base,16) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<boost::simd::uint8_t>  > , UP(base,17) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<boost::simd::uint8_t>             , UP(base,18) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_double)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<double>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<double_<double>      > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type64_<double>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<real_<double>        > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<double>      > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<double>  > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<double> > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<double> > , UP(base,6) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<double_<double>      > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type64_<double>      > , UP(base,8) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<real_<double>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<double>      > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<double>  > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<double> > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<double> > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<double>            , UP(base,14) >::value) );
}

BOOST_SIMD_TEST_CASE(hierarchy_of_float)
{
  using boost::is_same;
  using namespace boost::meta;

  typedef hierarchy_of<float>::type base;

  BOOST_SIMD_TEST( (is_same<scalar_<float_<float>       > , base >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<type32_<float>      > , UP(base,1) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<real_<float>        > , UP(base,2) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<signed_<float>      > , UP(base,3) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<arithmetic_<float>  > , UP(base,4) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<fundamental_<float> > , UP(base,5) >::value) );
  BOOST_SIMD_TEST( (is_same<scalar_<unspecified_<float> > , UP(base,6) >::value) );

  BOOST_SIMD_TEST( (is_same<generic_<float_<float>       > , UP(base,7) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<type32_<float>      > , UP(base,8) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<real_<float>        > , UP(base,9) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<signed_<float>      > , UP(base,10) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<arithmetic_<float>  > , UP(base,11) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<fundamental_<float> > , UP(base,12) >::value) );
  BOOST_SIMD_TEST( (is_same<generic_<unspecified_<float> > , UP(base,13) >::value) );
  BOOST_SIMD_TEST( (is_same<unspecified_<float>            , UP(base,14) >::value) );
}
