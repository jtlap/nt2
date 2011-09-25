//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SELECT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup select select function
 *
 * \par Description
 * The function returns the second entry or the third entry,
 * according to the first entry being True or False
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/select.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg sel
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::select_(A0,A0,A0)>::type
 *     select(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of select
 * \param a1 is the second parameter of select
 * \param a2 is the third parameter of select
 * 
 * \return a value of the common type of the parameters
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag select_ of functor select 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct select_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::select_, select, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::select_, sel, 3)
} }

#endif

// modified by jt the 25/12/2010
