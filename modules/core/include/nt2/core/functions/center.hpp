//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CENTER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CENTER_HPP_INCLUDED

/*!
 * \ingroup core
 * \defgroup core center
 *
 * \par Description
 * Returns the sum of absolute values of the elements matrix along the selected direction,
 * i.e. the 1-norm center(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 * \alias norm1,  asum
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/center.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::center_(A0)>::type
 *     center(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of center
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
**/


namespace nt2
{
  namespace tag
  {
    struct center_ : tag::formal_ 
    { 
      typedef tag::formal_ parent; 
    };
  }

  //============================================================================
  /*!
   * sum of absolute squares of a table
   *
   * \param xpr  table 
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 3)
}


#endif
