//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_repeat_lower_half repeat_lower_half
 *
 * \par Description
 * Compute 
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/repeat_lower_half.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class A0,class A1> inline
 *   typename boost::dispatch::meta::call<tag::repeat_lower_half_(A0 const&,A1 const&)
 *                                       >::type
 *   repeat_lower_half(A0 const& a0,A1 const& a1);
 *    
 *   template<class A0,class A1> inline
 *   A0 repeat_lower_half(A0 const& a0,A1 const& a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of repeat_lower_half
 * \param a1 the second parameter of repeat_lower_half
 * 
 * \return 
 *  
 * \par Notes
 * \par
 * This is a swar operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *  
**/

namespace boost { namespace simd {
  namespace tag
  {         
    /*!
     * \brief Define the tag repeat_lower_half_ of functor repeat_lower_half 
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct repeat_lower_half_ 
    : ext::unspecified_<repeat_lower_half_> 
    { 
      typedef ext::unspecified_<repeat_lower_half_> parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::repeat_lower_half_, repeat_lower_half, 1)
  
} }

#endif
