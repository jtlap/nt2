//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO_2_HPP_INCLUDED
/*!
 * \file
**/
#include <nt2/sdk/constant/constant.hpp>
/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant_pio_2 pio_2 constant
 *
 * \par Description
 * Constant pio_2 : \f$\frac\pi{2}\f$.
 * 
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/pio_2.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_pio_2_(A0)>::type
 *     pio_2();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Pio_2
 * 
 * \return type T value
 *  
 **/
namespace nt2
{
  NT2_MAKE_STD_CONSTANT( Pio_2     , 0x3ff921fb54442d18ll, 0x3fc90fdb, 1)
}

#endif
