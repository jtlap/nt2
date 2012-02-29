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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXTAFTER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXTAFTER_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_nextafter nextafter
 *
 * \par Description
 * in the type A0 of a0, the next element in the a1 direction.
 * \par
 * rg if a1 is greater than a0 this is next(a0)
 * rg if a1 is equal to a0 this is a0
 * rg if a1 is less than a0 this is prev(a0)
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/nextafter.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::nextafter_(A0,A0)>::type
 *     nextafter(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of nextafter
 * \param a1 the second parameter of nextafter
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
     * \brief Define the tag nextafter_ of functor nextafter 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct nextafter_ : ext::elementwise_<nextafter_> { typedef ext::elementwise_<nextafter_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::nextafter_, nextafter, 2)
} }

#endif

// modified by jt the 25/12/2010
