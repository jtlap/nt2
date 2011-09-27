//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_BITWISE_ANY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_BITWISE_ANY_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_reduction
 * \defgroup bitwise_any bitwise_any function
 *
 * \par Description
 * returns true if at least one vector bits is set else false
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_any.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg any_negative
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::bitwise_any_(A0)>::type
 *     bitwise_any(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of bitwise_any
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation has always a scalar result which translate a property.
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag bitwise_any_ of functor bitwise_any 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct bitwise_any_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_any_, bitwise_any, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_any_, any_negative, 1)
} }

#endif
