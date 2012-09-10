//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NORMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NORMP_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core normp
 *
 * \par Description
 * Returns the normp of the elements matrix along the selected direction,
 * i.e. the  power(asump(a0, p, n), 1/p)
 * by default n is the first non-singleton dimension of a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/normp.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1,  class A2>
 *     meta::call<tag::normp_(const A0& a0, const A1& p, const A2 n = 1)>::type
 *     normp(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of normp
 * \param  p the second parameter of normp
 * \param  n the thrird parameter of normp
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
    struct normp_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * sum of absolute p power of a table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normp_       , normp, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normp_       , normp, 3)
}

#endif
