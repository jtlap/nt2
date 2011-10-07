//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_4_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_4_HPP_INCLUDED
/*!
 * \file
**/
#include <nt2/sdk/constant/constant.hpp>
/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_pio_4 Pio_4 constant
 *
 * \par Description
 * Constant pio_4 : \f$\frac\pi{4}\f$.
 * 
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/pio_4.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_pio_4_(A0)>::type
 *     pio_4();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Pio_4
 * 
 * \return type T value
 *  
 **/
namespace nt2
{
  NT2_MAKE_STD_CONSTANT( Pio_4     , 0x3fe921fb54442d18ll, 0x3f490fdb, 0)
}

#endif
