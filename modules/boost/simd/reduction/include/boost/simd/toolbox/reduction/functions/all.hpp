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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_ALL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_ALL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_all all
 *
 * \par Description
 * returns true if all elements of the input vector are non zero.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/all.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::all_(A0)>::type
 *     all(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of all
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

namespace boost { namespace simd
{
  namespace tag
  {
    struct logical_and_;
    struct True;

    /*!
     * \brief Define the tag all_ of functor all 
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct all_ : ext::reduction_<all_, tag::logical_and_, tag::True> 
    { 
      typedef ext::reduction_<all_, tag::logical_and_, tag::True> parent;  
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::all_, all, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::all_, all, 2)
} }


#endif
