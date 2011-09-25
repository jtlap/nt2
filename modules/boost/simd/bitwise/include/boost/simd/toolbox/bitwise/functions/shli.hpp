//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHLI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SHLI_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup shli shli function
 *
 * \par Description
 * The function returns the first entry logically shifted left
 * by the absolute value of second entry.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/shli.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::shli_(A0,A0)>::type
 *     shli(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of shli
 * \param a1 is the second parameter of shli, must be a scalar integer value
 * 
 * \return returns a value of the type of the first parameter
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag shli_ of functor shli 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct shli_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shli_, shli, 2)
} }

#endif

// modified by jt the 25/12/2010
