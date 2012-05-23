/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::freqspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/functions/freqspace.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <boost/proto/debug.hpp>

NT2_TEST_CASE_TPL( freqspace, (double)(float) )
{
  using nt2::freqspace;
  nt2::table<T> f1, f2;

  tie(f1) = freqspace(10);
  tie(f1) = freqspace(10, nt2::meta::as_<T>() );

  tie(f1,f2) = freqspace(10);
  tie(f1,f2) = freqspace(10, nt2::meta::as_<T>() );
  tie(f1) = freqspace(10, nt2::whole_);
  tie(f1, f2) = freqspace(10, nt2::whole_);
  ////tie(f1, f2) = freqspace(nt2::of_size(10, 5));
  ////tie(f1, f2) = freqspace(nt2::of_size(10, 5), nt2::);
}
