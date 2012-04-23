//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WMEAM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WMEAM_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <boost/simd/toolbox/constant/constants/zero.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/details/reduction.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core wmeam
 *
 * \par Description
 * Returns the wmeam of the elements of the SIMD vector
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/wmeam.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::wmeam_(A0)>::type
 *     wmeam(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of wmeam
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
    struct wmeam_ : tag::formal_ 
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
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::wmeam_       , wmeam, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::wmeam_       , wmeam, 3)
}


#endif
