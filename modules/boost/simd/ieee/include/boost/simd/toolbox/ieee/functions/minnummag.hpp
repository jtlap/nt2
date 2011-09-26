//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MINNUMMAG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MINNUMMAG_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_ieee
 * \defgroup minnummag minnummag function
 *
 * \par Description
 * Returns the input value which have the least absolute value, ignoring nan.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/minnummag.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::minnummag_(A0,A0)>::type
 *     minnummag(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of minnummag
 * \param a1 is the second parameter of minnummag
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
     * \brief Define the tag minnummag_ of functor minnummag 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct minnummag_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minnummag_, minnummag, 2)
} }

#endif

// modified by jt the 25/12/2010
