//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/reduction/include/functions/sum.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL (sum_cplx, NT2_SIMD_REAL_TYPES)
{
  using nt2::sum;
  using nt2::tag::sum_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>               cT;
  typedef native<T,ext_t>               vT;
  typedef native<cT,ext_t>              vcT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<sum_(vcT)>::type
                  , cT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];

  for(std::size_t i=0;i<n;++i) data[i] = i+1;

  vT vr = boost::simd::load<vT>(&data[0]);
  vT vi = 2.*vr;

  vcT vn(vr,vi);

  NT2_TEST_EQUAL(sum(vn), cT(n*(n+1)/2, n*(n+1)) );
}

NT2_TEST_CASE_TPL (sum_dry, NT2_SIMD_REAL_TYPES)
{
  using nt2::sum;
  using nt2::tag::sum_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef nt2::dry<T>                   cT;
  typedef native<T,ext_t>               vT;
  typedef native<cT,ext_t>              vcT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<sum_(vcT)>::type
                  , cT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];

  for(std::size_t i=0;i<n;++i) data[i] = i+1;

  vT vr = boost::simd::load<vT>(&data[0]);

  vcT vn(vr);

  NT2_TEST_EQUAL(sum(vn), cT(n*(n+1)/2) );
}
