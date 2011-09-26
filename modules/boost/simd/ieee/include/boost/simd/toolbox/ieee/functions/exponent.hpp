//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EXPONENT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_ieee
 * \defgroup exponent exponent function
 *
 * \par Description
 * Returns the exponent of the floating input.
 * \par
 * The sign \f$ \pm \f$ , exponent e and mantissa m of a floating point entry a are related by
 * \f$a = \pm m\times 2^e\f$, with m between zero and one
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/exponent.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::exponent_(A0)>::type
 *     exponent(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of exponent
 * 
 * \return an integer value
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag exponent_ of functor exponent 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct exponent_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::exponent_, exponent, 1)
} }

#endif

// modified by jt the 25/12/2010
