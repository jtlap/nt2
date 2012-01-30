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

using namespace nt2::config;

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_size)
{
  std::cout << "Cache L1Code size : " << nt2::config::cache_size(L1Code) << " KBytes" << std::endl;
  std::cout << "Cache L1Data size : " << nt2::config::cache_size(L1Data) << " KBytes" << std::endl;
  std::cout << "Cache L2     size : " << nt2::config::cache_size(L2) << " KBytes" << std::endl;
  std::cout << "Cache L3     size : " << nt2::config::cache_size(L3) << " KBytes" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_line_size)
{
  std::cout << "Cache L1Code size : " << nt2::config::cache_line_size(L1Code) << " KBytes" << std::endl;
  std::cout << "Cache L1Data size : " << nt2::config::cache_line_size(L1Data) << " KBytes" << std::endl;
  std::cout << "Cache L2     size : " << nt2::config::cache_line_size(L2) << " KBytes" << std::endl;
  std::cout << "Cache L3     size : " << nt2::config::cache_line_size(L3) << " KBytes" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Test as_cache and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_cache)
{
  std::cout << "Cache L1Code available ([1,yes]/[0,no]) : " << nt2::config::as_cache(L1Code) << std::endl;
  std::cout << "Cache L1Data available ([1,yes]/[0,no]) : " << nt2::config::as_cache(L1Data) << std::endl;
  std::cout << "Cache L2     available ([1,yes]/[0,no]) : " << nt2::config::as_cache(L2) << std::endl;
  std::cout << "Cache L3     available ([1,yes]/[0,no]) : " << nt2::config::as_cache(L3) << std::endl;
}

