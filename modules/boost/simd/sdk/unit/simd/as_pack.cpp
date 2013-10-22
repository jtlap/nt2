//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/meta/as_pack.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(as_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::meta::as_pack;
  using boost::simd::pack;

  NT2_TEST_TYPE_IS( (typename as_pack<T,1 >::type), T            );
  NT2_TEST_TYPE_IS( (typename as_pack<T,2 >::type), (pack<T,2>)  );
  NT2_TEST_TYPE_IS( (typename as_pack<T,4 >::type), (pack<T,4>)  );
  NT2_TEST_TYPE_IS( (typename as_pack<T,8 >::type), (pack<T,8>)  );
  NT2_TEST_TYPE_IS( (typename as_pack<T,16>::type), (pack<T,16>) );
  NT2_TEST_TYPE_IS( (typename as_pack<T,32>::type), (pack<T,32>) );
}
