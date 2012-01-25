/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::config::cache"

#include <nt2/sdk/config/cache.hpp>
#include <iostream>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_size)
{
  for(int i = 1; i < 4; i++)
  {
    std::cout << "Cache L" << i << " size : " << nt2::config::cache_size(i) << " KBytes" << std::endl; 
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_line_size)
{
  for(int i = 1; i < 4; i++)
  {
    std::cout << "Cache L" << i << " line size : " << nt2::config::cache_line_size(i) << " Bytes" << std::endl; 
  }
}

