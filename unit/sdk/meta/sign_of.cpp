/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::sign_of"

#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that sign_of is correct
////////////////////////////////////////////////////////////////////////////////
struct foo {};

NT2_TEST_CASE(sign_of)
{
  using nt2::meta::sign_of;
  using boost::is_same;
  using namespace nt2;

  NT2_TEST( (is_same<sign_of<double  >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<float   >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<int64_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<int32_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<int16_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<int8_t  >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<uint64_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<uint32_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<uint16_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<uint8_t >::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<bool    >::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<foo     >::type,unsigned>::value ));

}
