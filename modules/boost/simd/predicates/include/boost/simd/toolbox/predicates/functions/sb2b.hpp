//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SB2B_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SB2B_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup sb2b sb2b function
 *
 * \par Description
 * converts signed boolean to bool.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sb2b.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sb2b_(A0)>::type
 *     sb2b(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of sb2b
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
     * \brief Define the tag sb2b_ of functor sb2b 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct sb2b_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sb2b_, sb2b, 1)
} }

#endif

// modified by jt the 25/12/2010
