/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::category_of simd"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/toolbox/operator.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Test category of SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(simd_category)
{
  using boost::simd::native;
  using boost::dispatch::meta::hierarchy_of;
  using boost::dispatch::meta::simd_; 
  using boost::is_same;
  using namespace boost::simd;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;

  #if defined(BOOST_SIMD_SSE_FAMILY)
  NT2_TEST((is_same<  hierarchy_of< native<double,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::double_<native<double,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::uint64_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::uint64_<native<boost::simd::uint64_t,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::int64_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::int64_<native<boost::simd::int64_t,ext_t> > ,ext_t>
                    >::value
          ));
  #endif

  NT2_TEST((is_same<  hierarchy_of<native<float,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::single_< native<float,ext_t> >,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::uint32_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::uint32_<native<boost::simd::uint32_t,ext_t> >,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::int32_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::int32_<native<boost::simd::int32_t,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::uint16_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::uint16_<native<boost::simd::uint16_t,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::int16_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::int16_<native<boost::simd::int16_t,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::uint8_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::uint8_<native<boost::simd::uint8_t,ext_t> > ,ext_t>
                    >::value
          ));

  NT2_TEST((is_same<  hierarchy_of<native<boost::simd::int8_t,ext_t> >::type
                    , boost::dispatch::meta::simd_< boost::dispatch::meta::int8_<native<boost::simd::int8_t,ext_t> > ,ext_t>
                    >::value
          ));
}

NT2_TEST_CASE_TPL(simd_expr_category, (double))
{
  using boost::simd::pack;
  using boost::is_same;
  using namespace boost::dispatch::meta;

  pack<T> x,y;
  
  BOOST_DISPATCH_DECLTYPE(x+y, type_t_);
  typedef typename strip<type_t_>::type type_t;
  typedef typename boost::proto::domain_of<type_t>::type domain_t;
  typedef typename semantic_of<type_t>::type semantic_t;

  NT2_TEST(( is_same< typename hierarchy_of<type_t>::type
                    , expr_< typename hierarchy_of<semantic_t, type_t>::type
                           , domain_t
                           , boost::proto::tag::plus
                           >
                    >::value
          ));
}
