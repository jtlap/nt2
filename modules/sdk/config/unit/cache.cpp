/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::config::cache"

#include <iostream>
#include <nt2/sdk/config/cache.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

using namespace nt2::config;

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_size)
{
  std::cout << "Cache L1Code size : " << nt2::config::cache_size(L1Code) << " Kbytes" << std::endl;
  std::cout << "Cache L1Data size : " << nt2::config::cache_size(L1Data) << " Kbytes" << std::endl;
  std::cout << "Cache L1     size : " << nt2::config::cache_size(L1) << " Kbytes" << std::endl;
  std::cout << "Cache L2     size : " << nt2::config::cache_size(L2) << " Kbytes" << std::endl;
  std::cout << "Cache L3     size : " << nt2::config::cache_size(L3) << " Kbytes" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Test cache_size and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cache_line_size)
{
  std::cout << "Cache L1Code size : " << nt2::config::cache_line_size(L1Code) << " bytes" << std::endl;
  std::cout << "Cache L1Data size : " << nt2::config::cache_line_size(L1Data) << " bytes" << std::endl;
  std::cout << "Cache L1     size : " << nt2::config::cache_line_size(L1) << " bytes" << std::endl;
  std::cout << "Cache L2     size : " << nt2::config::cache_line_size(L2) << " bytes" << std::endl;
  std::cout << "Cache L3     size : " << nt2::config::cache_line_size(L3) << " bytes" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Test has_cache and display the result
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_cache)
{
  std::cout << "Cache L1Code available : " << std::boolalpha << nt2::config::has_cache(L1Code) << std::endl;
  std::cout << "Cache L1Data available : " << std::boolalpha << nt2::config::has_cache(L1Data) << std::endl;
  std::cout << "Cache L1     available : " << std::boolalpha << nt2::config::has_cache(L1) << std::endl;
  std::cout << "Cache L2     available : " << std::boolalpha << nt2::config::has_cache(L2) << std::endl;
  std::cout << "Cache L3     available : " << std::boolalpha << nt2::config::has_cache(L3) << std::endl;

  NT2_TEST_COMPLETE("Cache test complete");
}

