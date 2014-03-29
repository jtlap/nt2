//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/memory/include/functions/splat.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( splat, NT2_TYPES )
{
  using nt2::splat;
  using nt2::tag::splat_;

  // return type conformity test
  NT2_TEST_TYPE_IS( (typename nt2::meta::call < splat_( T
                                                      , boost::dispatch::meta::as_<T>
                                                      )
                                              >::type
                    )
                  , T
                  );

  NT2_TEST_EQUAL(splat<T>(1), T(1));
}
