/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::category_of simd"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/simd/sdk/unit/tests/basic.hpp>
#include <boost/simd/sdk/unit/module.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Test category of SIMD types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(simd_category)
{
  using boost::simd::native;
  using boost::simd::meta::hierarchy_of;
  using boost::is_same;
  using namespace boost::simd;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;

  #if defined(BOOST_SIMD_SSE_FAMILY)
  BOOST_SIMD_TEST((is_same<  hierarchy_of< native<double,ext_t> >::type
                    , meta::simd_< meta::double_<native<double,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::uint64_t,ext_t> >::type
                    , meta::simd_< meta::uint64_<native<boost::simd::uint64_t,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::int64_t,ext_t> >::type
                    , meta::simd_< meta::int64_<native<boost::simd::int64_t,ext_t> > ,ext_t>
                    >::value
          ));
  #endif

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<float,ext_t> >::type
                    , meta::simd_< meta::float_< native<float,ext_t> >,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::uint32_t,ext_t> >::type
                    , meta::simd_< meta::uint32_<native<boost::simd::uint32_t,ext_t> >,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::int32_t,ext_t> >::type
                    , meta::simd_< meta::int32_<native<boost::simd::int32_t,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::uint16_t,ext_t> >::type
                    , meta::simd_< meta::uint16_<native<boost::simd::uint16_t,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::int16_t,ext_t> >::type
                    , meta::simd_< meta::int16_<native<boost::simd::int16_t,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::uint8_t,ext_t> >::type
                    , meta::simd_< meta::uint8_<native<boost::simd::uint8_t,ext_t> > ,ext_t>
                    >::value
          ));

  BOOST_SIMD_TEST((is_same<  hierarchy_of<native<boost::simd::int8_t,ext_t> >::type
                    , meta::simd_< meta::int8_<native<boost::simd::int8_t,ext_t> > ,ext_t>
                    >::value
          ));
}

BOOST_SIMD_TEST_CASE_TPL(simd_expr_category, (double))
{
  using boost::simd::pack;
  using boost::simd::meta::hierarchy_of;
  using boost::is_same;
  using namespace boost;

  pack<T> x,y;

  BOOST_SIMD_DECLTYPE(x+y, type_t_);
  typedef typename boost::simd::meta::strip<type_t_>::type type_t;
  typedef typename boost::proto::domain_of<type_t>::type domain_t;

  BOOST_SIMD_TEST(( is_same< typename hierarchy_of<type_t>::type
                    , boost::simd::meta::expr_< type_t , boost::simd::meta::domain_<domain_t>
                                      , boost::proto::tag::plus , void
                                      >
                    >::value
          ));
}
