/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( bsearch, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
typedef typename nt2::meta::as_integer<T>::type i_type; 
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4); 
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 7);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi); 
  
  nt2::table<i_type> yi = nt2::bsearch(x, xi); 
  
  NT2_DISPLAY(yi); 
}

