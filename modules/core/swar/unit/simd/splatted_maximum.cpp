//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/swar/include/functions/splatted_maximum.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( splatted_maximum, BOOST_SIMD_SIMD_TYPES )
{
  using nt2::splatted_maximum;
  using nt2::tag::splatted_maximum_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<splatted_maximum_(vT)>::type
                  , vT
                  );

  static const std::size_t n = vT::static_size;
  T data[n];

  for(std::size_t k=0;k<n;++k)
  {
    for(std::size_t i=0;i<n;++i) data[i] = T(i+1);
    data[k] = T(99);

    vT vn = boost::simd::load<vT>(&data[0]);
    NT2_TEST_EQUAL(splatted_maximum(vn), splat<vT>( 99 ) );
  }
}
