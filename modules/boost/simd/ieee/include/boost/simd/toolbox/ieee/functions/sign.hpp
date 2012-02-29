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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIGN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIGN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_sign sign
 *
 * \par Description
 * Returns the sign of a0. I.e. -1, 0 or 1, according
 * a0 is less than zero, zero or greater than zero.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sign.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sign_(A0)>::type
 *     sign(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sign
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag sign_ of functor sign 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct sign_ : ext::elementwise_<sign_> { typedef ext::elementwise_<sign_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sign_, sign, 1)
} }

#endif

// modified by jt the 25/12/2010
