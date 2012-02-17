/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::category_of simd"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/toolbox/operator.hpp>
#include <boost/proto/tags.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

struct hierarchy_
{
  template<class X>
  struct apply : boost::dispatch::meta::hierarchy_of<X>
  {
  };
};

////////////////////////////////////////////////////////////////////////////////
// Test category of SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(simd_category)
{
  using namespace boost::dispatch::meta;
  using boost::simd::native;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;

  #if defined(BOOST_SIMD_SSE_FAMILY)
  {
    native<double, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< double_< native<double, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::uint64_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< uint64_< native<boost::simd::uint64_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::int64_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< int64_< native<boost::simd::int64_t, ext_t> >, ext_t > )
                      );
  }
  #endif

  {
    native<float, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< single_< native<float, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::uint32_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< uint32_< native<boost::simd::uint32_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::int32_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< int32_< native<boost::simd::int32_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::uint16_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< uint16_< native<boost::simd::uint16_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::int16_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< int16_< native<boost::simd::int16_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::uint8_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< uint8_< native<boost::simd::uint8_t, ext_t> >, ext_t > )
                      );
  }
  {
    native<boost::simd::int8_t, ext_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( simd_< int8_< native<boost::simd::int8_t, ext_t> >, ext_t > )
                      );
  }
}

NT2_TEST_CASE(pack_category)
{
  using namespace boost::dispatch::meta;
  using namespace boost::simd;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION   ext_t;
  typedef boost::simd::domain            domain_;
  typedef boost::simd::tag::terminal_    tag_;
  typedef boost::mpl::long_<0>           arity_;

  #if defined(BOOST_SIMD_SSE_FAMILY)
  {
    pack<double> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< double_< pack<double> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::uint64_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< uint64_< pack<boost::simd::uint64_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::int64_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< int64_< pack<boost::simd::int64_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  #endif

  {
    pack<float> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< single_< pack<float> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::uint32_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< uint32_< pack<boost::simd::uint32_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::int32_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< int32_< pack<boost::simd::int32_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::uint16_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< uint16_< pack<boost::simd::uint16_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::int16_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< int16_< pack<boost::simd::int16_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::uint8_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< uint8_< pack<boost::simd::uint8_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
  {
    pack<boost::simd::int8_t> p;
    NT2_TEST_EXPR_TYPE( p, hierarchy_
                      , ( expr_< simd_< int8_< pack<boost::simd::int8_t> >, ext_t >
                               , tag_, arity_
                               >
                        )
                      );
  }
}

NT2_TEST_CASE_TPL(pack_expr_category, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using namespace boost::dispatch::meta;
  using boost::mpl::_;

  pack<T> x,y;

  NT2_TEST_EXPR_TYPE( x
                    , hierarchy_
                    , ( expr_< typename hierarchy_of< typename semantic_of< pack<T> >::type
                                                    , pack<T>
                                                    >::type
                             , boost::simd::tag::terminal_
                             , typename boost::proto::arity_of< pack<T> >::type
                             >
                      )
                    );
  
  typedef BOOST_DISPATCH_TYPEOF(x+y) type_t_;
  typedef typename strip<type_t_>::type type_t;
  typedef typename boost::proto::arity_of<type_t>::type arity_t;
  typedef typename semantic_of<type_t>::type semantic_t;

  NT2_TEST_EXPR_TYPE( x + y
                    , hierarchy_
                    , ( expr_< typename hierarchy_of<semantic_t, type_t>::type
                             , boost::simd::tag::plus_
                             , arity_t
                             >
                      )
                    );
}
