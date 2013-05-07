//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/remquo.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

// All these tests should return NaN
NT2_TEST_CASE_TPL( remquo_invalid, NT2_REAL_TYPES)
{
  using boost::simd::remquo;
  using boost::simd::tag::remquo_;

  typedef typename boost::dispatch::meta::as_integer<T,signed>::type iT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<remquo_(T,T)>::type)
                  , (std::pair<T,iT>)
                  );

  T inf_  = boost::simd::Inf<T>();
  T nan_  = boost::simd::Nan<T>();
  T zero_ = boost::simd::Zero<T>();
  T one_  = boost::simd::One<T>();

  {
    // n is unspecified by the standard so we don't test it
    iT n;
    T  r;

    remquo(one_,nan_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(one_,inf_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(one_,zero_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(inf_,zero_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(nan_,zero_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(nan_,one_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(nan_,nan_, r, n);
    NT2_TEST_EQUAL(r, nan_);

    remquo(nan_,inf_, r, n);
    NT2_TEST_EQUAL(r, nan_);
  }

  {
    // n is unspecified by the standard so we don't test it
    iT n;
    T  r;

    r = remquo(one_,nan_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(one_,inf_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(one_,zero_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(inf_,zero_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(nan_,zero_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(nan_,one_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(nan_,nan_, n);
    NT2_TEST_EQUAL(r, nan_);

    r = remquo(nan_,inf_, n);
    NT2_TEST_EQUAL(r, nan_);
  }

  {
    // n is unspecified by the standard so we don't test it
    iT n;
    T  r;

    boost::fusion::vector_tie(r,n) = remquo(one_,nan_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(one_,inf_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(one_,zero_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(inf_,zero_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(nan_,zero_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(nan_,one_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(nan_,nan_);
    NT2_TEST_EQUAL(r, nan_);

    boost::fusion::vector_tie(r,n) = remquo(nan_,inf_);
    NT2_TEST_EQUAL(r, nan_);
  }

  {
    // n is unspecified by the standard so we don't test it
    std::pair<T,iT> p;

    p =  remquo(one_,nan_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(one_,inf_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(one_,zero_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(inf_,zero_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(nan_,zero_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(nan_,one_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(nan_,nan_);
    NT2_TEST_EQUAL(p.first, nan_);

    p =  remquo(nan_,inf_);
    NT2_TEST_EQUAL(p.first, nan_);
  }
}

NT2_TEST_CASE_TPL( remquo_valid, NT2_REAL_TYPES)
{
  using boost::simd::remquo;
  using boost::simd::tag::remquo_;

  typedef typename boost::dispatch::meta::as_integer<T,signed>::type iT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<remquo_(T,T)>::type)
                  , (std::pair<T,iT>)
                  );

  T a0[] = { T(1), T(2), T(3), T(4.5) };
  T a1[] = { T(2), T(1), T(7), T(3.2) };

  std::size_t nb = sizeof(a0)/sizeof(T);

  {
    iT n;
    T  r;

    for(std::size_t i=0;i<nb;++i)
    {
      remquo(a0[i],a1[i], r, n);
      NT2_TEST_EQUAL(n, iT(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - n*a1[i]);
    }
  }

  {
    iT n;
    T  r;

    for(std::size_t i=0;i<nb;++i)
    {
      r = remquo(a0[i],a1[i], n);
      NT2_TEST_EQUAL(n, iT(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - n*a1[i]);
    }
  }

  {
    iT n;
    T  r;

    for(std::size_t i=0;i<nb;++i)
    {
      boost::fusion::vector_tie(r,n) = remquo(a0[i],a1[i]);
      NT2_TEST_EQUAL(n, iT(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - n*a1[i]);
    }
  }

  {
    std::pair<T,iT> p;

    for(std::size_t i=0;i<nb;++i)
    {
      p = remquo(a0[i],a1[i]);
      NT2_TEST_EQUAL(p.second, iT(a0[i] / a1[i]));
      NT2_TEST_EQUAL(p.first, a0[i] - p.second*a1[i]);
    }
  }
}
