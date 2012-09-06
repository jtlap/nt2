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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MEANOF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MEANOF_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_meanof meanof
 *
 * \par Description
 * The function always returns a value of the same type than the entry.
 * Take care that for integers the value returned can differ by one unit
 * from \c ceil((a+b)/2.0) or \c floor((a+b)/2.0), but is always one of
 * the two
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/meanof.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::meanof_(A0,A0)>::type
 *     meanof(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of meanof
 * \param a1 the second parameter of meanof
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
     * \brief Define the tag meanof_ of functor meanof 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct meanof_ : ext::elementwise_<meanof_> { typedef ext::elementwise_<meanof_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::meanof_, meanof, 2)
} }

#endif

// modified by jt the 25/12/2010
