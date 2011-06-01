/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_MAX_LEFT_SHIFT_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_MAX_LEFT_SHIFT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <nt2/include/simd.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/toolbox/constant/include.hpp>
#include <nt2/sdk/constant/common.hpp>

namespace nt2
{
  namespace tag
  {
    struct max_left_shift_ {};
  }
  
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::max_left_shift_, Maxleftshift)
}

#include <nt2/toolbox/constant/constants/scalar/max_left_shift.hpp>
#include <nt2/toolbox/constant/constants/simd/all/max_left_shift.hpp>

#endif

