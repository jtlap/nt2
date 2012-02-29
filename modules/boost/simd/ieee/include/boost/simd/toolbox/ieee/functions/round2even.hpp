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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_ROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_ROUND2EVEN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_round2even round2even
 *
 * \par Description
 * round to the nearest integer
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/round2even.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::round2even_(A0)>::type
 *     round2even(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of round2even
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
     * \brief Define the tag round2even_ of functor round2even 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct round2even_ : ext::elementwise_<round2even_> { typedef ext::elementwise_<round2even_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round2even_, round2even, 1)
} }

#endif

// modified by jt the 25/12/2010
