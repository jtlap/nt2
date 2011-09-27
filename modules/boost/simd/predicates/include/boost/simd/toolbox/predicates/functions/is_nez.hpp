//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NEZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NEZ_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_nez is_nez function
 *
 * \par Description
 * Returns True<A0>() if a0 is not equal to zero else returns False<A0>().
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_nez.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_true
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_nez_(A0)>::type
 *     is_nez(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of is_nez
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
     * \brief Define the tag is_nez_ of functor is_nez 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_nez_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_nez_, is_nez,  1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_nez_, is_true, 1)
} }

#endif

// modified by jt the 25/12/2010
