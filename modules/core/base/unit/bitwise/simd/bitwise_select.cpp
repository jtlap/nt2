//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/bitwise_select.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(bitwise_select, NT2_SIMD_TYPES)
{
  using nt2::splat;
  using nt2::bitwise_cast;
  using nt2::bitwise_select;
  using nt2::tag::bitwise_select_;
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

  nt2::uint64_t base = 0xF5555552F552F5F2ULL;
  ivT imask = splat<ivT>(base & nt2::uint64_t(~iT(0)));
  vT  mask  = bitwise_cast<vT>(imask);

  NT2_TEST_EQUAL( bitwise_select( imask
                                , nt2::Allbits<vT>()
                                , nt2::Zero<vT>()
                                )
                , mask
                );

  NT2_TEST_EQUAL( bitwise_select( mask
                                , nt2::Allbits<vT>()
                                , nt2::Zero<vT>()
                                )
                , mask
                );
}
