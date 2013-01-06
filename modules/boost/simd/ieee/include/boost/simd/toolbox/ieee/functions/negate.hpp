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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_NEGATE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_negate negate
 *
 * \par Description
 * a1 < 0 ? a0 : -a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/negate.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::negate_(A0,A0)>::type
 *     negate(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of negate
 * \param a1 the second parameter of negate
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag negate_ of functor negate
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct negate_ : ext::elementwise_<negate_> { typedef ext::elementwise_<negate_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negate_, negate, 2)
} }

#endif

// modified by jt the 25/12/2010
