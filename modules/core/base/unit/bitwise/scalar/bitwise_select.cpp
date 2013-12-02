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
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(bitwise_select, NT2_TYPES)
{
  using nt2::splat;
  using nt2::bitwise_cast;
  using nt2::bitwise_select;
  using nt2::tag::bitwise_select_;
  using boost::dispatch::meta::as_integer;

  typedef typename as_integer<T,unsigned>::type iT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                                   ::call<bitwise_select_(T,T,T)>::type
                    )
                  , T
                  );

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                                   ::call<bitwise_select_(iT,T,T)>::type
                    )
                  , T
                  );

  nt2::uint64_t base = 0xF5555552F552F5F2ULL;
  iT imask = splat<iT>(base & nt2::uint64_t(~iT(0)));
  T  mask  = bitwise_cast<T>(imask);

  NT2_TEST_EQUAL( bitwise_select( imask
                                , nt2::Allbits<T>()
                                , nt2::Zero<T>()
                                )
                , mask
                );

  NT2_TEST_EQUAL( bitwise_select( mask
                                , nt2::Allbits<T>()
                                , nt2::Zero<T>()
                                )
                , mask
                );
}
