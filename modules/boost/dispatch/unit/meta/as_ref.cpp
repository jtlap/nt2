//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::as_real"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/mpl/placeholders.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE(as_floating)
{
  using boost::mpl::_;
  using boost::dispatch::meta::as_ref;

  NT2_TEST_TYPE_IS( as_ref<float>::type       , float const&  );
  NT2_TEST_TYPE_IS( as_ref<float const>::type , float const&  );
  NT2_TEST_TYPE_IS( as_ref<float const&>::type, float const&  );
  NT2_TEST_TYPE_IS( as_ref<float&>::type      , float&        );
}
