//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_CORRECT_FMA_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_correct_fma correct_fma
 *
 * \par Description
 * Always compute the correct fused multiply add,
 * For floating point entries this means
 * the computation of a0*a1+a2 with only one rounding operation.
 * On machines not possessing this hard wired capability
 * this can be a bit costly
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/correct_fma.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::correct_fma_(A0,A0,A0)>::type
 *     correct_fma(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of correct_fma
 * \param a1 the second parameter of correct_fma
 * \param a2 the third parameter of correct_fma
 * 
 * \return a value of the common type of the parameters
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag correct_fma_ of functor correct_fma 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct correct_fma_ : ext::elementwise_<correct_fma_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::correct_fma_, correct_fma, 3)
} }

#endif

// modified by jt the 25/12/2010
