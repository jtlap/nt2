//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/combine.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<typename T>
struct big_enough : boost::mpl::bool_< (BOOST_SIMD_BYTES/sizeof(T) > 2) >
{};

NT2_TEST_CASE_TPL_MPL ( combine_native
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , big_enough<_>
                                                )
                      )
{
  using boost::simd::native;
  using boost::simd::tag::combine_;
  using boost::simd::meta::vector_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                    ext_t;
  typedef native<T,ext_t>                                 wT;
  typedef typename vector_of<T, wT::static_size/2>::type  vT;

  typedef typename boost::dispatch::meta::call<combine_(vT, vT)>::type rT;

  NT2_TEST_TYPE_IS( rT, wT );

  vT a,b;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    a[i] = T(1+i);
    b[i] = T(1+i+vT::static_size);
  }

  wT ref;

  for(std::size_t i=0; i < wT::static_size;++i)
    ref[i] = T(1+i);

  NT2_TEST_EQUAL(ref, boost::simd::combine(a,b));
}

NT2_TEST_CASE_TPL_MPL ( combine_logical
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , big_enough<_>
                                                )
                      )
{
  using boost::simd::native;
  using boost::simd::logical;
  using boost::simd::tag::combine_;
  using boost::simd::meta::vector_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                    ext_t;
  typedef native<logical<T>,ext_t>                                 wT;
  typedef typename vector_of<logical<T>, wT::static_size/2>::type  vT;

  typedef typename boost::dispatch::meta::call<combine_(vT, vT)>::type rT;

  NT2_TEST_TYPE_IS( rT, wT );

  vT a,b;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    a[i] = logical<T>((1+i) % 2 );
    b[i] = logical<T>((1+i+wT::static_size) % 2);
  }

  wT ref;

  for(std::size_t i=0; i < wT::static_size;++i)
    ref[i] = logical<T>((1+i) % 2 );

  NT2_TEST_EQUAL(ref, boost::simd::combine(a,b));
}

NT2_TEST_CASE_TPL_MPL ( combine_fusion
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , big_enough<_>
                                                )
                      )
{
  using boost::simd::native;
  using boost::simd::tag::combine_;
  using boost::simd::meta::vector_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                             ext_t;
  typedef native<std::pair<T,T>,ext_t>                             wT;
  typedef typename vector_of<std::pair<T,T>, wT::static_size/2>::type  vT;

  typedef typename boost::dispatch::meta::call<combine_(vT, vT)>::type rT;

  NT2_TEST_TYPE_IS( rT, wT );

  vT a,b;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    a[i] = std::make_pair(T(i+1), T(2*i));
    b[i] = std::make_pair(T(i+1+vT::static_size), T(2*(i+vT::static_size)));
  }

  wT ref;

  for(std::size_t i=0; i < wT::static_size;++i)
    ref[i] = std::make_pair(T(i+1), T(2*i));

  NT2_TEST_EQUAL(ref, boost::simd::combine(a,b));
}

NT2_TEST_CASE_TPL_MPL ( combine_pack
                      , NT2_TEST_SEQ_MPL_FILTER ( BOOST_SIMD_SIMD_TYPES
                                                , big_enough<_>
                                                )
                      )
{
  using boost::simd::pack;
  using boost::simd::tag::combine_;

  typedef pack<T>                       wT;
  typedef pack<T,wT::static_size/2>     vT;

  vT a,b;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    a[i] = T(1+i);
    b[i] = T(1+i+vT::static_size);
  }

  wT ref;

  for(std::size_t i=0; i < wT::static_size;++i)
    ref[i] = T(1+i);

  NT2_TEST_EQUAL( ref.size(), a.size()+b.size() );
  NT2_TEST_EQUAL( ref, boost::simd::combine(a,b));
}

