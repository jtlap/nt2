//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::hierarchy_of"

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for ref, value and const ref
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(hierarchy_of_ref_cref, NT2_TYPES)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef typename hierarchy_of<T>::type        hvalue;
  typedef typename hierarchy_of<T&>::type       rvalue;
  typedef typename hierarchy_of<T const&>::type crvalue;

  NT2_TEST( (is_same<hvalue, rvalue>::value) );
  NT2_TEST( (is_same<hvalue, crvalue>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for basic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(hierarchy_of_bool)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<bool>::type base;

  NT2_TEST( (is_same<scalar_<bool_<bool>          > , base >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<bool>   > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<bool>   > , UP(base,2) >::value) );
  NT2_TEST( (is_same<generic_<bool_<bool>         > , UP(base,3) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<bool>  > , UP(base,4) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<bool>  > , UP(base,5) >::value) );
  NT2_TEST( (is_same<unspecified_<bool>             , UP(base,6) >::value) );
}

NT2_TEST_CASE(hierarchy_of_void)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<void>::type base;

  NT2_TEST( (is_same<scalar_<void_<void>          > , base >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<void>   > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<void>   > , UP(base,2) >::value) );
  NT2_TEST( (is_same<generic_<void_<void>         > , UP(base,3) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<void>  > , UP(base,4) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<void>  > , UP(base,5) >::value) );
  NT2_TEST( (is_same<unspecified_<void>             , UP(base,6) >::value) );
}
NT2_TEST_CASE(hierarchy_of_ints64)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::int64_t>::type base;

  NT2_TEST( (is_same<scalar_<int64_<nt2::int64_t>       > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints64_<nt2::int64_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type64_<nt2::int64_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<nt2::int64_t>  > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<int_<nt2::int64_t>         > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<nt2::int64_t>      > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::int64_t>     > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::int64_t>  > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::int64_t> > , UP(base,8) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::int64_t> > , UP(base,9) >::value) );

  NT2_TEST( (is_same<generic_<int64_<nt2::int64_t>        > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<ints64_<nt2::int64_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<type64_<nt2::int64_t>       > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<nt2::int64_t>   > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<int_<nt2::int64_t>          > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<signed_<nt2::int64_t>       > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::int64_t>      > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::int64_t>   > , UP(base,17) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::int64_t>  > , UP(base,18) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::int64_t>  > , UP(base,19) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::int64_t>             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints64)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::uint64_t>::type base;

  NT2_TEST( (is_same<scalar_<uint64_<nt2::uint64_t>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints64_<nt2::uint64_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type64_<nt2::uint64_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<nt2::uint64_t>  > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<uint_<nt2::uint64_t>        > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<unsigned_<nt2::uint64_t>    > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::uint64_t>     > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::uint64_t>  > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::uint64_t> > , UP(base,8) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::uint64_t> > , UP(base,9) >::value) );

  NT2_TEST( (is_same<generic_<uint64_<nt2::uint64_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<ints64_<nt2::uint64_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<type64_<nt2::uint64_t>       > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<nt2::uint64_t>   > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<uint_<nt2::uint64_t>         > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<unsigned_<nt2::uint64_t>     > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::uint64_t>      > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::uint64_t>   > , UP(base,17) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::uint64_t>  > , UP(base,18) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::uint64_t>  > , UP(base,19) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::uint64_t>             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints32)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::int32_t>::type base;

  NT2_TEST( (is_same<scalar_<int32_<nt2::int32_t>       > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints32_<nt2::int32_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type32_<nt2::int32_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<nt2::int32_t>  > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<int_<nt2::int32_t>         > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<nt2::int32_t>      > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::int32_t>     > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::int32_t>  > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::int32_t> > , UP(base,8) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::int32_t> > , UP(base,9) >::value) );

  NT2_TEST( (is_same<generic_<int32_<nt2::int32_t>        > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<ints32_<nt2::int32_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<type32_<nt2::int32_t>       > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<nt2::int32_t>   > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<int_<nt2::int32_t>          > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<signed_<nt2::int32_t>       > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::int32_t>      > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::int32_t>   > , UP(base,17) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::int32_t>  > , UP(base,18) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::int32_t>  > , UP(base,19) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::int32_t>             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints32)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::uint32_t>::type base;

  NT2_TEST( (is_same<scalar_<uint32_<nt2::uint32_t>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints32_<nt2::uint32_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type32_<nt2::uint32_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<nt2::uint32_t>  > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<uint_<nt2::uint32_t>        > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<unsigned_<nt2::uint32_t>    > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::uint32_t>     > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::uint32_t>  > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::uint32_t> > , UP(base,8) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::uint32_t> > , UP(base,9) >::value) );

  NT2_TEST( (is_same<generic_<uint32_<nt2::uint32_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<ints32_<nt2::uint32_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<type32_<nt2::uint32_t>       > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<nt2::uint32_t>   > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<uint_<nt2::uint32_t>         > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<unsigned_<nt2::uint32_t>     > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::uint32_t>      > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::uint32_t>   > , UP(base,17) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::uint32_t>  > , UP(base,18) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::uint32_t>  > , UP(base,19) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::uint32_t>             , UP(base,20) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints16)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::int16_t>::type base;

  NT2_TEST( (is_same<scalar_<int16_<nt2::int16_t>       > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints16_<nt2::int16_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type16_<nt2::int16_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<int_<nt2::int16_t>         > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<nt2::int16_t>      > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::int16_t>     > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::int16_t>  > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::int16_t> > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::int16_t> > , UP(base,8) >::value) );

  NT2_TEST( (is_same<generic_<int16_<nt2::int16_t>        > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<ints16_<nt2::int16_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<type16_<nt2::int16_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<int_<nt2::int16_t>          > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<signed_<nt2::int16_t>       > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::int16_t>      > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::int16_t>   > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::int16_t>  > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::int16_t>  > , UP(base,17) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::int16_t>             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints16)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::uint16_t>::type base;

  NT2_TEST( (is_same<scalar_<uint16_<nt2::uint16_t>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints16_<nt2::uint16_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type16_<nt2::uint16_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<uint_<nt2::uint16_t>        > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<unsigned_<nt2::uint16_t>    > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::uint16_t>     > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::uint16_t>  > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::uint16_t> > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::uint16_t> > , UP(base,8) >::value) );

  NT2_TEST( (is_same<generic_<uint16_<nt2::uint16_t>       > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<ints16_<nt2::uint16_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<type16_<nt2::uint16_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<uint_<nt2::uint16_t>         > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<unsigned_<nt2::uint16_t>     > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::uint16_t>      > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::uint16_t>   > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::uint16_t>  > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::uint16_t>  > , UP(base,17) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::uint16_t>             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_ints8)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::int8_t>::type base;

  NT2_TEST( (is_same<scalar_<int8_<nt2::int8_t>       > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints8_<nt2::int8_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type8_<nt2::int8_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<int_<nt2::int8_t>         > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<nt2::int8_t>      > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::int8_t>     > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::int8_t>  > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::int8_t> > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::int8_t> > , UP(base,8) >::value) );

  NT2_TEST( (is_same<generic_<int8_<nt2::int8_t>        > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<ints8_<nt2::int8_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<type8_<nt2::int8_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<int_<nt2::int8_t>          > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<signed_<nt2::int8_t>       > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::int8_t>      > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::int8_t>   > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::int8_t>  > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::int8_t>  > , UP(base,17) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::int8_t>             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_uints8)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<nt2::uint8_t>::type base;

  NT2_TEST( (is_same<scalar_<uint8_<nt2::uint8_t>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<ints8_<nt2::uint8_t>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<type8_<nt2::uint8_t>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<uint_<nt2::uint8_t>        > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<unsigned_<nt2::uint8_t>    > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<integer_<nt2::uint8_t>     > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<nt2::uint8_t>  > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<nt2::uint8_t> > , UP(base,7) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<nt2::uint8_t> > , UP(base,8) >::value) );

  NT2_TEST( (is_same<generic_<uint8_<nt2::uint8_t>       > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<ints8_<nt2::uint8_t>       > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<type8_<nt2::uint8_t>       > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<uint_<nt2::uint8_t>         > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<unsigned_<nt2::uint8_t>     > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<integer_<nt2::uint8_t>      > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<nt2::uint8_t>   > , UP(base,15) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<nt2::uint8_t>  > , UP(base,16) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<nt2::uint8_t>  > , UP(base,17) >::value) );
  NT2_TEST( (is_same<unspecified_<nt2::uint8_t>             , UP(base,18) >::value) );
}

NT2_TEST_CASE(hierarchy_of_double)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<double>::type base;

  NT2_TEST( (is_same<scalar_<double_<double>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<type64_<double>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<double>  > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_<double>        > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<double>      > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<double>  > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<double> > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<double> > , UP(base,7) >::value) );

  NT2_TEST( (is_same<generic_<double_<double>      > , UP(base,8) >::value) );
  NT2_TEST( (is_same<generic_<type64_<double>      > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<double>  > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<floating_<double>        > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<signed_<double>      > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<double>  > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<double> > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<double> > , UP(base,15) >::value) );
  NT2_TEST( (is_same<unspecified_<double>            , UP(base,16) >::value) );
}

NT2_TEST_CASE(hierarchy_of_float)
{
  using boost::is_same;
  using nt2::meta::hierarchy_of;
  using namespace nt2::ext;

  typedef hierarchy_of<float>::type base;

  NT2_TEST( (is_same<scalar_<single_<float>      > , base >::value) );
  NT2_TEST( (is_same<scalar_<type32_<float>      > , UP(base,1) >::value) );
  NT2_TEST( (is_same<scalar_<floating_sized_<float>  > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<floating_<float>        > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<signed_<float>      > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<float>  > , UP(base,5) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<float> > , UP(base,6) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<float> > , UP(base,7) >::value) );

  NT2_TEST( (is_same<generic_<single_<float>      > , UP(base,8) >::value) );
  NT2_TEST( (is_same<generic_<type32_<float>      > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<floating_sized_<float>  > , UP(base,10) >::value) );
  NT2_TEST( (is_same<generic_<floating_<float>        > , UP(base,11) >::value) );
  NT2_TEST( (is_same<generic_<signed_<float>      > , UP(base,12) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<float>  > , UP(base,13) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<float> > , UP(base,14) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<float> > , UP(base,15) >::value) );
  NT2_TEST( (is_same<unspecified_<float>            , UP(base,16) >::value) );
}
