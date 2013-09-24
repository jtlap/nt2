//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <iostream>

void float_control_debug()
{
  std::cout << "Float control word debug information\n";
  std::cout << "---------------------------------------------------------------\n";

  #ifdef BOOST_SIMD_ARCH_X86

  std::cout << "x87 settings:\n";
  unsigned short int cw = boost::simd::config::x86::x87_get_control_word();

  std::cout << "denormals allowed = " << !!(cw & (1 << 2)) << "\n";
  int precision = (cw >> 8) & 0x3;
  std::cout << "precision = " << ((precision == 0) ? "single" : (precision == 2) ? "double" : "extended") << "\n\n";

  #ifdef BOOST_SIMD_HAS_SSE_SUPPORT

  std::cout << "SSE settings:\n";
  unsigned int i = _mm_getcsr();
  std::cout << "Flush-To-Zero = " << !!(i & (1 << 15)) << "\n";
  std::cout << "Denormals-As-Zero = " << !!(i & (1 << 6)) << "\n";
  std::cout << "denormals allowed = " << !!(i & (1 << 8)) << "\n";

  #endif
  #endif

  std::cout << std::flush;
}
