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
  struct val_max_           {};
  struct val_min_           {};
  struct signmask_          {};
  struct max_left_shift_    {};
  struct nb_mantissa_bits_  {};
  struct nb_exponent_bits_  {};
  struct max_exponent_      {};
  struct min_exponent_      {};
  struct nb_digits_         {};
  struct ldexp_mask_        {};
} }

////////////////////////////////////////////////////////////////////////////////
// Constant function
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::val_max_          , Valmax         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::val_min_          , Valmin         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::signmask_         , Signmask       )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::max_left_shift_   , Maxleftshift   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::ldexp_mask_       , Ldexpmask      )
  
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::nb_mantissa_bits_ , Nbmantissabits )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::nb_exponent_bits_ , Nbexponentbits )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::max_exponent_     , Maxexponent    )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::min_exponent_     , Minexponent    )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::nb_digits_        , Nbdigits       )  
}

////////////////////////////////////////////////////////////////////////////////
// Constant function implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/details/valmax.hpp>
#include <nt2/sdk/constant/details/valmin.hpp>
//#include <nt2/sdk/constant/details/smallestposval.hpp>  //in eps_related
#include <nt2/sdk/constant/details/signmask.hpp>
#include <nt2/sdk/constant/details/ieee_spec.hpp>
#include <nt2/sdk/constant/details/ldexp_mask.hpp>
//#include <nt2/sdk/constant/details/maxleftshift.hpp>
//#include <nt2/sdk/constant/details/mindenormal.hpp> //in eps_related

/*
NT2_SPECIALIZE_CONSTANT ( max_left_shift_  , Category
                        , meta::as_integer<boost::mpl::_>
                        , ((arithmetic_,8*sizeof(T)-1         ))
                        )

NT2_SPECIALIZE_CONSTANT ( smallest_pos_val_, Category , boost::mpl::_
                        , ((double   ,0x0010000000000000LL  ))
                          ((float    ,0x00800000            ))
                          ((integer_ ,1                     ))
                        )
NT2_SPECIALIZE_CONSTANT ( min_denormal_, Category , boost::mpl::_
                        , ((double   ,0x1ll                 ))
                          ((float    ,0x1                   ))
                          ((integer_ ,1                     ))
                          ((bool     ,1                     ))
                        )
*/
                        
#endif
