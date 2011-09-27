//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GEZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GEZ_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_gez is_gez function
 *
 * \par Description
 * Returns True<A0>() or False<A0>() according a0 is greater or equal to zero or not.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_gez.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_gez_(A0)>::type
 *     is_gez(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of is_gez
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
     * \brief Define the tag is_gez_ of functor is_gez 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_gez_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_gez_, is_gez, 1)
} }

#endif

// modified by jt the 25/12/2010
