/******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_FACTOR_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_FACTOR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_factor factor
 *
 * \par Description
 * returns the table of prime numbers less or equal to the input
 * \par
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/factor.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::factor_(A0)>::type
 *     factor(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of factor
 * 
 * \param T template parameter of factor
 * 
 * \return a value of the template parameter type T.
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag factor_ of functor factor 
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct factor_ : ext::elementwise_<factor_> { typedef ext::elementwise_<factor_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::factor_,factor, 1)
} 

#endif

