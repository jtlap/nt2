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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/include/functions/logical_notand.hpp>
#include <boost/simd/toolbox/constant/constants/true.hpp>
/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_none none
 *
 * \par Description
 * returns true if all elements of the input vector are zero.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/none.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::none_(A0)>::type
 *     none(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of none
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
     * \brief Define the tag none_ of functor none 
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct none_ : ext::reduction_<none_, tag::logical_notand_, tag::True> 
    { 
      typedef ext::reduction_<none_, tag::logical_notand_, tag::True> parent; 
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 2)
} }


#endif

// modified by jt the 25/12/2010
