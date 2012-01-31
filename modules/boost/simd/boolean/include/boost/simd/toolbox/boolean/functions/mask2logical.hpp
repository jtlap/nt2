//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_MASK2LOGICAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_mask2logical mask2logical
 *
 * \par Description
 * The function converts an arithmetic mask where each element is
 * Zero or Allbits to a logical value.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/mask2logical.hpp>
 * \endcode
 * 
* \par Alias
 * \arg m2l
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::mask2logical(A0)>::type
 *     mask2logical(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of mask2logical
 * 
 * \return a value of type \c as_logical<A0>::type
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/


namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag mask2logical_ of functor mask2logical
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
     struct mask2logical_ : ext::elementwise_<mask2logical_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mask2logical_, mask2logical, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mask2logical_, m2l, 1)
} }
 
#endif
