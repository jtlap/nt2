//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NORM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NORM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core norm2
 *
 * \par Description
 * Returns the norm2 of the elements matrix along the selected direction,
 * i.e. the euclidian norm sqrt(asum2(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 * \alias norm_eucl
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norm2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::norm2_(A0)>::type
 *     norm2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of norm2
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
    struct norm2_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * sum of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm2, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm2, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm_eucl, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::norm2_       , norm_eucl, 2)
}

#endif
