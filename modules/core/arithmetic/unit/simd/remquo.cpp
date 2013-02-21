//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/arithmetic/include/functions/remquo.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

// All these tests should return NaN
NT2_TEST_CASE_TPL( remquo_invalid, NT2_SIMD_REAL_TYPES)
{
  using nt2::remquo;
  using nt2::tag::remquo_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>  vT;
  typedef typename boost::dispatch::meta::as_integer<vT,signed>::type viT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<remquo_(vT,vT)>::type)
                  , (std::pair<vT,viT>)
                  );

  vT inf_  = nt2::Inf<vT>();
  vT nan_  = nt2::Nan<vT>();
  vT zero_ = nt2::Zero<vT>();
  vT one_  = nt2::One<vT>();

  {
    // n is unspecified by the standard so we don't test it
    viT n;
    vT  r;

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
    viT n;
    vT  r;

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
    viT n;
    vT  r;

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
    std::pair<vT,viT> p;

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

NT2_TEST_CASE_TPL( remquo_valid, NT2_SIMD_REAL_TYPES)
{
  using nt2::remquo;
  using nt2::toint;
  using nt2::tofloat;
  using nt2::splat;
  using nt2::tag::remquo_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>  vT;
  typedef typename boost::dispatch::meta::as_integer<vT,signed>::type viT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<remquo_(vT,vT)>::type)
                  , (std::pair<vT,viT>)
                  );

  vT a0[] = { splat<vT>(1), splat<vT>(2), splat<vT>(3), splat<vT>(4.5) };
  vT a1[] = { splat<vT>(2), splat<vT>(1), splat<vT>(7), splat<vT>(3.2) };

  std::size_t nb = sizeof(a0)/sizeof(vT);

  {
    viT n;
    vT  r;

    for(std::size_t i=0;i<nb;++i)
    {
      remquo(a0[i],a1[i], r, n);
      NT2_TEST_EQUAL(n, toint(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - tofloat(n)*a1[i]);
    }
  }

  {
    viT n;
    vT  r;

    for(std::size_t i=0;i<nb;++i)
    {
      r = remquo(a0[i],a1[i], n);
      NT2_TEST_EQUAL(n, toint(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - tofloat(n)*a1[i]);
    }
  }

  {
    viT n;
    vT  r;

    for(std::size_t i=0;i<nb;++i)
    {
      boost::fusion::vector_tie(r,n) = remquo(a0[i],a1[i]);
      NT2_TEST_EQUAL(n, toint(a0[i] / a1[i]));
      NT2_TEST_EQUAL(r, a0[i] - tofloat(n)*a1[i]);
    }
  }

  {
    std::pair<vT,viT> p;

    for(std::size_t i=0;i<nb;++i)
    {
      p = remquo(a0[i],a1[i]);
      NT2_TEST_EQUAL(p.second, toint(a0[i] / a1[i]));
      NT2_TEST_EQUAL(p.first, a0[i] - tofloat(p.second)*a1[i]);
    }
  }
}
