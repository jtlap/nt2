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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIGNNZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_signnz signnz
 *
 * \par Description
 * Returns the sign of a0. I.e. -1 or 1, according
 * a0 is negative or positive.
 * This function never returns zero (zero is considered positive).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/signnz.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::signnz_(A0)>::type
 *     signnz(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of signnz
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag signnz_ of functor signnz
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct signnz_ : ext::elementwise_<signnz_> { typedef ext::elementwise_<signnz_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::signnz_, signnz, 1)
} }

#endif

// modified by jt the 25/12/2010
