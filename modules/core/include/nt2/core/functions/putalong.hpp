//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_PUTALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_PUTALONG_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core putalong
 *
 * \par Description
 * Returns the sum of absolute values of the elements matrix along the selected direction,
 * i.e. the 1-norm putalong(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 * \alias norm1,  asum
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/putalong.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::putalong_(A0)>::type
 *     putalong(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of putalong
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
    struct putalong_ : tag::formal_
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
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::putalong_       , putalong, 2)

}


#endif
