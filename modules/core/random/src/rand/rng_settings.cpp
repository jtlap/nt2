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
  NT2_CORE_RANDOM_DECL
  rng_settings::rng_settings() : generator_(mt19937stream())
  {
    seed(0);
  }

  NT2_CORE_RANDOM_DECL
  rng_settings::rng_settings(randstream_* g, uint32_t s)  : generator_(g)
  {
    seed(s);
  }

  NT2_CORE_RANDOM_DECL rng_settings::rng_settings(rng_settings const& s)
  {
    generator_ = s.generator_;
    seed(s.seed_);
  };

  NT2_CORE_RANDOM_DECL
  rng_settings& rng_settings::operator=(rng_settings const& s)
  {
    generator_ = s.generator_;
    seed(s.seed_);

    return *this;
  };

  NT2_CORE_RANDOM_DECL void rng_settings::seed(uint32_t s)
  {
    seed_ = s;
    generator_->seed(seed_);
  }

  NT2_CORE_RANDOM_DECL void rng_settings::generator(randstream_* g)
  {
    generator_ = g;
    generator_->seed(seed_);
  }
}

