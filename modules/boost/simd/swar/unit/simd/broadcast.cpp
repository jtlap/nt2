//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<typename Ref, typename T>
void check(T const& a0, boost::mpl::int_<1> const&)
{
  using boost::simd::splat;
  using boost::simd::tag::broadcast_;
  using boost::simd::broadcast;
  using boost::dispatch::meta::call;
  using boost::mpl::int_;

  NT2_TEST_TYPE_IS( typename call<broadcast_(T const&,int_<0>)>::type
                  , Ref
                  );

  NT2_TEST_EQUAL( broadcast<0>(a0), splat<T>(a0[0]));
}

template<typename Ref, int N, typename T>
void check(T const& a0, boost::mpl::int_<N> const&)
{
  using boost::simd::splat;
  using boost::simd::tag::broadcast_;
  using boost::simd::broadcast;
  using boost::dispatch::meta::call;
  using boost::mpl::int_;

  NT2_TEST_TYPE_IS( typename call<broadcast_(T const&,int_<N-1>)>::type
                  , Ref
                  );

  NT2_TEST_EQUAL( broadcast<N-1>(a0), splat<T>(a0[N-1]));
  check<Ref>(a0, boost::mpl::int_<N-1>());
}

NT2_TEST_CASE_TPL ( broadcast,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  vT original;

  for(std::size_t i=0; i< vT::static_size;++i)
    original[i] = T(1+i);

  check<vT>(original, boost::mpl::int_<vT::static_size>());
}

NT2_TEST_CASE_TPL ( broadcast_pack, BOOST_SIMD_SIMD_TYPES)
{
  typedef boost::simd::pack<T> vT;

  vT original;

  for(std::size_t i=0; i< vT::static_size;++i)
    original[i] = T(1+i);

  check<vT>(original          , boost::mpl::int_<vT::static_size>() );
  check<vT>(original+original , boost::mpl::int_<vT::static_size>() );
}
