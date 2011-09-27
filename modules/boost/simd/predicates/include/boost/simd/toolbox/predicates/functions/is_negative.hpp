//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NEGATIVE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NEGATIVE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_predicates
 * \defgroup is_negative is_negative function
 *
 * \par Description
 * Returns True<A0>() if a0 is negative else False<A0>().
 * \par
 * This function differs from is_ltz from floating point argument,
 * because Mzero<A0>() is negative but not less than zero.
 * \par
 * Mzero<A0>() is the floating point 'minus zero',
 * i.e. all bits are zero but the sign bit.
 * Such a value is treated as zero by ieee standards.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_negative.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_negative_(A0)>::type
 *     is_negative(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of is_negative
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
     * \brief Define the tag is_negative_ of functor is_negative 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct is_negative_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_negative_, is_negative, 1)
} }

#endif

// modified by jt the 25/12/2010
