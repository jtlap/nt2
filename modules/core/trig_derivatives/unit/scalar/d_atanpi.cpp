//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_atanpi.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/third.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functions/pi.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( atanpi,  NT2_REAL_TYPES)
{
  using nt2::d_atanpi;
  NT2_TEST_ULP_EQUAL(d_atanpi(nt2::Third<T>()),
                     nt2::df(nt2::functor<nt2::tag::atanpi_>(),nt2::Third<T>(), nt2::centered_), nt2::rec(nt2::Sqrteps<T>()));

}
