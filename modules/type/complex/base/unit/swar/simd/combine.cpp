//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/combine.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/complex/complex.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<typename T>
struct big_enough : boost::mpl::bool_< (BOOST_SIMD_BYTES/sizeof(T) > 2) >
{};

NT2_TEST_CASE_TPL_MPL ( combine_native
                      , NT2_TEST_SEQ_MPL_FILTER ( NT2_SIMD_REAL_TYPES
                                                , big_enough<_>
                                                )
                      )
{
  using boost::simd::native;
  using boost::simd::tag::combine_;
  using boost::simd::meta::vector_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                    ext_t;
  typedef std::complex<T>                                 cT;
  typedef native<cT,ext_t>                                wT;
  typedef typename vector_of<cT, wT::static_size/2>::type vT;

  typedef typename boost::dispatch::meta::call<combine_(vT, vT)>::type rT;

  NT2_TEST_TYPE_IS( rT, wT );

  vT a,b;

  for(std::size_t i=0; i < vT::static_size;++i)
  {
    a[i] = cT(1+i,2*i);
    b[i] = cT(1+i+vT::static_size,2*(i+vT::static_size));
  }

  wT ref;

  for(std::size_t i=0; i < wT::static_size;++i)
    ref[i] = cT(1+i,2*+i);

  NT2_TEST_EQUAL(ref, boost::simd::combine(a,b));
}
