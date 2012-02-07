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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEXT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_next next
 *
 * \par Description
 * in the type A0 of a0, the least A0 strictly greater than a0
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/next.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::next_(A0)>::type
 *     next(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of next
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
     * \brief Define the tag next_ of functor next 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct next_ : ext::elementwise_<next_> { typedef ext::elementwise_<next_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::next_, next, 1)
} }

#endif

// modified by jt the 25/12/2010
