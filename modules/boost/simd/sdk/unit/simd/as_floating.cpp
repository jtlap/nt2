//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( as_floating_simd_native
                  , BOOST_SIMD_SIMD_REAL_CONVERTIBLE_TYPES
                  )
{
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  using boost::dispatch::meta::as_floating;
  using boost::is_same;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef typename vector_of< typename as_floating<T>::type
                            , native<T,ext_t>::static_size
                            >::type dst_t;

  NT2_TEST_TYPE_IS( (typename as_floating< native<T,ext_t> >::type)
                  , dst_t
                  );
}

NT2_TEST_CASE_TPL ( as_floating_simd_pack
                  , BOOST_SIMD_SIMD_REAL_CONVERTIBLE_TYPES
                  )
{
  using boost::simd::pack;
  using boost::dispatch::meta::as_floating;
  using boost::is_same;
  using boost::mpl::_;

  typedef pack<typename as_floating<T>::type>   dst_t;

  NT2_TEST_TYPE_IS( (typename as_floating< pack<T> >::type)
                  , dst_t
                  );
}
