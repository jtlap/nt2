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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEGATION_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEGATION_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_negation negation
 *
 * \par Description
 * a1 < 0 ? a0 : -a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/negation.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::negation_(A0,A0)>::type
 *     negation(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of negation
 * \param a1 the second parameter of negation
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
     * \brief Define the tag negation_ of functor negation
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct negation_ : ext::elementwise_<negation_> { typedef ext::elementwise_<negation_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negation_, negation, 2)
} }

#endif

// modified by jt the 25/12/2010
