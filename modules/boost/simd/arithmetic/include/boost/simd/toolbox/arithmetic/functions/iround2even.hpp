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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IROUND2EVEN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_iround2even iround2even
 *
 * \par Description
 * return a value of integer type of the same size and signedness than the entry.
 * The value returned is the nearest integer to the entry
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/iround2even.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::iround2even_(A0)>::type
 *     iround2even(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of iround2even
 * 
 * \return an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag iround2even_ of functor iround2even 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct iround2even_ : ext::elementwise_<iround2even_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::iround2even_, iround2even, 1)
} }

#endif

// modified by jt the 25/12/2010
