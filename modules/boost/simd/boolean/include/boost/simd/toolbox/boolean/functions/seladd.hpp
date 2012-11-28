//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SELADD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SELADD_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_seladd seladd
 *
 * \par Description
 * The function returns the second entry or the sum of the second and third entries,
 * according to the first entry being True or False
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/seladd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1>
 *     meta::call<tag::seladd_(A0,A1,A1)>::type
 *     seladd(const A0 & a0,const A1 & a1,const A1 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of seladd
 * \param a1 the second parameter of seladd, must be an integer value
 * \param a2 the third parameter of seladd
 *
 * \return a value of the common type of the 2 last parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag seladd_ of functor seladd
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct seladd_ : ext::elementwise_<seladd_> { typedef ext::elementwise_<seladd_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seladd_, seladd, 3)
} }

#endif

// modified by jt the 25/12/2010
