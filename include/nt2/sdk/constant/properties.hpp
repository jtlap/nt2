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
#include <nt2/sdk/constant/constant.hpp>
//#include <boost/type_traits/is_floating_point.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constant tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace constants
{
  struct val_max_ {};
  struct val_min_ {};
  struct smallest_pos_val_ {};
  struct signmask_ {};
  struct max_left_shift_ {};
  struct min_denormal_ {};
} }

////////////////////////////////////////////////////////////////////////////////
// Constant function
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::val_max_         , Valmax         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::val_min_         , Valmin         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::smallest_pos_val_, Smallestposval )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::signmask_        , Signmask       )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::max_left_shift_  , Maxleftshift   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::min_denormal_    , Mindenormal    )
}

////////////////////////////////////////////////////////////////////////////////
// Constant function implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/details/valmax.hpp>
//#include <nt2/sdk/constant/details/valmin.hpp>
//#include <nt2/sdk/constant/details/smallestposval.hpp>
#include <nt2/sdk/constant/details/signmask.hpp>
//#include <nt2/sdk/constant/details/maxleftshift.hpp>
//#include <nt2/sdk/constant/details/mindenormal.hpp>

#endif
