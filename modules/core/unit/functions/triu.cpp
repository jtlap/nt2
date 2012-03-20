/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::triu function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( triu, (double)(float) )
{
  using boost::simd::native;
  typedef T r_t;
  double ulpd;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef typename nt2::meta::as_integer<n_t>::type vtype; 

  nt2::table<T> xd = nt2::ones(nt2::of_size(3, 3), nt2::meta::as_<T>());
  vtype i = nt2::enumerate<vtype>(1);
  std::cout << xd(i) << std::endl; 
  //  nt2::table<T> yd = nt2::triu(xd); 
}
