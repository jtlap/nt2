//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/swar/include/functions/splatted_minimum.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( splatted_minimum, BOOST_SIMD_SIMD_TYPES)
{
  using nt2::splatted_minimum;
  using nt2::tag::splatted_minimum_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<splatted_minimum_(vT)>::type
                  , vT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];

  for(std::size_t k=0;k<n;++k)
  {
    for(std::size_t i=0;i<n;++i) data[i] = T(3*(i+1));
    data[k] = T(1);

    vT vn = boost::simd::load<vT>(&data[0]);
    NT2_TEST_EQUAL(splatted_minimum(vn), splat<vT>( 1 ) );
  }
}
