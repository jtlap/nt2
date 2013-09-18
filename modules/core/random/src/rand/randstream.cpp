//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <nt2/core/utility/mt19937stream.hpp>

namespace nt2
{
  randstream_::~randstream_() {}

  NT2_CORE_RANDOM_DECL rng_settings current_prng_;
}
