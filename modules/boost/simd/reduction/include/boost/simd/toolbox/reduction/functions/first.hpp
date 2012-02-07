//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_FIRST_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_first first
 *
 * \par Description
 * returns the first element of the input vector.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/first.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::first_(A0)>::type
 *     first(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of first
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag first_ of functor first 
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct first_ : ext::reduction_<first_> { typedef ext::reduction_<first_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::first_, first, 1)
} }

#endif

// modified by jt the 25/12/2010
