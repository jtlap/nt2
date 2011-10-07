//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_INVPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_INVPI_HPP_INCLUDED
/*!
 * \file
**/
#include <nt2/sdk/constant/constant.hpp>
/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_invpi Invpi constant
 *
 * \par Description
 * Constant Invpi : \f$\frac1\pi\f$.
 * 
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/invpi.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_invpi_(A0)>::type
 *     Invpi();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Invpi
 * 
 * \return type T value
 *  
 *  
**/
namespace nt2
{
  NT2_MAKE_STD_CONSTANT( Invpi     , 0x3fd45f306dc9c883ll, 0x3ea2f983, 0)
}

#endif
