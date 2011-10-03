

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_factorial factorial function
 *
 * \par Description
 * Saturated factorial in the A0 type
 * \par
 * be aware that the result is never exact if a0>12
 * and that the result is saturated in the input type!
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/factorial.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::factorial_(A0)>::type
 *     factorial(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of factorial
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

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
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_FACTORIAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {         
    /*!
    _
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct factorial_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::factorial_,factorial, 1)
} 

#endif

