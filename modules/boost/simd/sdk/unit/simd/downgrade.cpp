//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::downgrade SIMD"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/sdk/meta/is_downgradable.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD types
////////////////////////////////////////////////////////////////////////////////

template<class T>
struct test_type : boost::simd::meta::is_downgradable_on_ext< boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> > {};

NT2_TEST_CASE_TPL_MPL ( downgrade_native
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , test_type<_>
                                                )
                      )
{
  using boost::simd::native;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             native_t;
  typedef typename downgrade<T>::type   base_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, (native<base_t,ext_t>) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD logical types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL_MPL ( downgrade_logical
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , test_type<_>
                                                )
                      )
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      native_t;
  typedef typename downgrade<T>::type   base_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, (native<logical<base_t>,ext_t>) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD pack types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_pack, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef pack<T>                           pack_t;
  typedef typename downgrade<T>::type       base_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, pack<base_t> );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD logical pack types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_logical_pack, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::pack;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef pack< logical<T> >                pack_t;
  typedef typename downgrade<T>::type       base_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, pack< logical<base_t> > );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for complex fusion cases
////////////////////////////////////////////////////////////////////////////////
template<int N>
struct downgrade_at
{
  template<class X>
  struct apply
  {
    typedef typename boost::dispatch::meta::downgrade<X>::type upgraded;
    typedef typename boost::fusion::result_of::value_at_c<upgraded, N>::type type;
  };
};

NT2_TEST_CASE(downgrade_fusion)
{
  using boost::simd::meta::vector_of;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef std::pair<nt2::int64_t, double> T;

  static const std::size_t N = BOOST_SIMD_BYTES/4;

  typedef vector_of<T, N>::type vT;
  typedef vector_of<nt2::int64_t, N>::type vT0;
  typedef vector_of<double, N>::type vT1;

  vT va0;
  //NT2_TEST_EXPR_TYPE( va0,  upgrade<_>, int ); // for debug purposes
  NT2_TEST_EXPR_TYPE( va0, downgrade_at<0>, downgrade<vT0>::type );
  NT2_TEST_EXPR_TYPE( va0, downgrade_at<1>, downgrade<vT1>::type );
}
