//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_UNORD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_UNORD_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_unord is_unord function
 *
 * \par Description
 * Returns True<A0>() if a0 or a1 is nan.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_unord.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_unord_(A0,A0)>::type
 *     is_unord(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of is_unord
 * \param a1 is the second parameter of is_unord
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
     * \brief Define the tag is_unord_ of functor is_unord 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_unord_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_unord_, is_unord, 2)
} }

#endif

// modified by jt the 25/12/2010
