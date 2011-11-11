//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_45_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_45_HPP_INCLUDED
/*!
 * \file
**/
#include <nt2/sdk/constant/constant.hpp>
/*!
 * \ingroup trigo_constant
 * \defgroup trigo_constant__45 _45 
 *
 * \par Description
 * Constant _45 : 45.
 * 
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/_45.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::_45_(A0)>::type
 *     _45();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of _45
 * 
 * \return type T value
 *  
 *  
**/
namespace nt2
{
  NT2_MAKE_STD_CONSTANT(_45    , 0x4046800000000000ll, 0x42340000, 45)
}

#endif
