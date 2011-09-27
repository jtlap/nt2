//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_not_equal_with_equal_nans is_not_equal_with_equal_nans function
 *
 * \par Description
 * Returns True<A0>() if a0 and a1 are not equal else False<A0>().
 * nans are considered equal
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_not_equal_with_equal_nans.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_not_equal_with_equal_nans_(A0,A0)>::type
 *     is_not_equal_with_equal_nans(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of is_not_equal_with_equal_nans
 * \param a1 is the second parameter of is_not_equal_with_equal_nans
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
     * \brief Define the tag is_not_equal_with_equal_nans_ of functor is_not_equal_with_equal_nans 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_not_equal_with_equal_nans_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_equal_with_equal_nans_, is_not_equal_with_equal_nans, 2)
} }

#endif

// modified by jt the 25/12/2010
