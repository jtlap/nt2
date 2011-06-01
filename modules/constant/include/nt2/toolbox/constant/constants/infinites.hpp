/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_INFINITES_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_INFINITES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Generating an infinite constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/include/simd.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/toolbox/constant/include.hpp>
#include <nt2/sdk/constant/common.hpp>

namespace nt2 { namespace tag
{
  struct inf_   {}; struct m_inf_ {}; struct nan_  {};
} }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::inf_    , Inf   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::m_inf_  , Minf  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::nan_    , Nan   )
}

#include <nt2/toolbox/constant/constants/scalar/infinites.hpp>
#include <nt2/toolbox/constant/constants/simd/all/infinites.hpp>

#endif
