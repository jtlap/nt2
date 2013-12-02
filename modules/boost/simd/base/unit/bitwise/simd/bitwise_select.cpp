//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitwise_select.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(bitwise_select, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::splat;
  using boost::simd::bitwise_cast;
  using boost::simd::bitwise_select;
  using boost::simd::tag::bitwise_select_;
  using boost::simd::native;
  using boost::dispatch::meta::as_integer;

  typedef BOOST_SIMD_DEFAULT_EXTENSION          ext_t;
  typedef native<T,ext_t>                       vT;
  typedef typename as_integer<T,unsigned>::type iT;
  typedef typename as_integer<vT,unsigned>::type ivT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                                   ::call<bitwise_select_(vT,vT,vT)>::type
                    )
                  , vT
                  );

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                                   ::call<bitwise_select_(ivT,vT,vT)>::type
                    )
                  , vT
                  );

  boost::simd::uint64_t base = 0xF5555552F552F5F2ULL;
  ivT imask = splat<ivT>(base & boost::simd::uint64_t(~iT(0)));
  vT  mask  = bitwise_cast<vT>(imask);

  NT2_TEST_EQUAL( bitwise_select( imask
                                , boost::simd::Allbits<vT>()
                                , boost::simd::Zero<vT>()
                                )
                , mask
                );

  NT2_TEST_EQUAL( bitwise_select( mask
                                , boost::simd::Allbits<vT>()
                                , boost::simd::Zero<vT>()
                                )
                , mask
                );
}
