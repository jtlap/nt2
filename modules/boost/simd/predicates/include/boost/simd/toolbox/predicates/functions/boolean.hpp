//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_BOOLEAN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_BOOLEAN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup boolean boolean function
 *
 * \par Description
 * Returns a boolean value but of the type of the input.
 * Zero<A0>() or One<A0>() according a0 is zero or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/boolean.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::boolean_(A0)>::type
 *     boolean(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of boolean
 * 
 * \return a value of the same type as the parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag boolean_ of functor boolean 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct boolean_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::boolean_, boolean, 1)
} }

#endif

// modified by jt the 25/12/2010
