/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::linspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/sdk/complex/complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( linspace_cplx, (double)(float) )
{
  typedef std::complex<T> cT;
  nt2::table<cT> z = nt2::linspace(cT(-1, -1), cT(1, 1), 257);
  nt2::table<cT> ref(nt2::of_size(1,257));

  for(size_t i = 1; i <= 257; ++i)
    ref(i) =  cT(-1, -1)+cT(T(i-1)/128, T(i-1)/128);

  NT2_TEST_EQUAL(z, ref);
}
