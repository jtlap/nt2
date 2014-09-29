//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/group.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/swar/include/functions/group.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/type_traits/is_floating_point.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( demote, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::enumerate;
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename boost::simd::meta::vector_of< typename boost::dispatch::meta::downgrade<T>::type, vT::static_size >::type dvT;
  typedef typename boost::dispatch::meta::call<group_(vT)>::type r_t;
  NT2_TEST_TYPE_IS(r_t, dvT);

  NT2_TEST_EQUAL( group(boost::simd::enumerate<vT>(T(-vT::static_size/2)))
                , boost::simd::enumerate<dvT>(T(-vT::static_size/2))
                );
}

NT2_TEST_CASE_TPL_MPL( group_groupable__2_0, NT2_TEST_SEQ_MPL_FILTER(BOOST_SIMD_SIMD_GROUPABLE_TYPES, not_< boost::is_floating_point<_> >) )
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::native;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  using boost::simd::Allbits;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(group(One<vT>(),  One<vT>())[0],  One<sr_t>());
  NT2_TEST_EQUAL(group(Zero<vT>(), Zero<vT>())[0], Zero<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>()/Two<vT>(), Valmax<vT>()/Two<vT>())[0], Allbits<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>()/Two<vT>(), Valmin<vT>()/Two<vT>())[0], Zero<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>(), Valmax<vT>())[0], Allbits<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>(), Valmin<vT>())[0], Zero<sr_t>());
} // end of test for groupable_

NT2_TEST_CASE_TPL_MPL( group_groupable__2_1, NT2_TEST_SEQ_MPL_FILTER(BOOST_SIMD_SIMD_GROUPABLE_TYPES, boost::is_floating_point<_>) )
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::native;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(group(One<vT>(),  One<vT>())[1],  One<sr_t>());
  NT2_TEST_EQUAL(group(Zero<vT>(), Zero<vT>())[1], Zero<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>()/Two<vT>(), Valmax<vT>()/Two<vT>())[1], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>()/Two<vT>(), Valmin<vT>()/Two<vT>())[1], Minf<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>(), Valmax<vT>())[1], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>(), Valmin<vT>())[1], Minf<sr_t>());
} // end of test for groupable_

NT2_TEST_CASE_TPL ( group_groupable__3_1,  BOOST_SIMD_SIMD_GROUPABLE_TYPES)
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests

  size_t n = cardinal_of<vT>::value;
  for(size_t i=0; i < cardinal_of<vT>::value; i++)
  {
    NT2_TEST_EQUAL(group(boost::simd::enumerate<vT>(T(0)),  boost::simd::enumerate<vT>(T(n)))[i],  T(i));
  }
} // end of test for groupable_

NT2_TEST_CASE_TPL ( group_groupable__4_1,  (int32_t))
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests

  size_t n = cardinal_of<vT>::value;
  int32_t s = 32767 - int32_t(n);
  for(size_t i=0; i < cardinal_of<vT>::value; i++)
  {
    NT2_TEST_EQUAL(group( boost::simd::enumerate<vT>(T(s))
                        , boost::simd::enumerate<vT>(T(s+n))
                        )[i]
                  ,  T(s+i)
                  );
  }
} // end of test for groupable_

