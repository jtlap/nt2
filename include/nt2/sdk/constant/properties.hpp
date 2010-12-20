/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_PROPERTIES_HPP_INCLUDED
#define NT2_SDK_CONSTANT_PROPERTIES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// List constants tied to type properties and bit representation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/constant/constant.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constant tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct val_max_           {}; struct val_min_           {};
  struct ldexp_mask_        {}; struct signmask_          {};
  struct nb_digits_         {}; struct max_left_shift_    {};
  struct nb_mantissa_bits_  {}; struct nb_exponent_bits_  {};
  struct max_exponent_      {}; struct min_exponent_      {};
} }

////////////////////////////////////////////////////////////////////////////////
// Constant function
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::val_max_          , Valmax         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::val_min_          , Valmin         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::signmask_         , Signmask       )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::max_left_shift_   , Maxleftshift   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::ldexp_mask_       , Ldexpmask      )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::nb_mantissa_bits_ , Nbmantissabits )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::nb_exponent_bits_ , Nbexponentbits )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::max_exponent_     , Maxexponent    )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::min_exponent_     , Minexponent    )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::nb_digits_        , Nbdigits       )
}

////////////////////////////////////////////////////////////////////////////////
// Constant function implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/details/valmax.hpp>
#include <nt2/sdk/constant/details/valmin.hpp>
#include <nt2/sdk/constant/details/signmask.hpp>
#include <nt2/sdk/constant/details/ieee_spec.hpp>
#include <nt2/sdk/constant/details/maxleftshift.hpp>

#endif
