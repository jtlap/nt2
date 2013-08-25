//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_toint toint
 *
 * \par Description
 * convert a floating entry to integer by truncation.
 * toint cast a floating value to the signed integer value of the same bit size
 * it is done by C casting for scalars and corresponding intrinsic in simd (if available)
 * Peculiarly,  that implies that the behaviour of this function on invalid entries is
 * not defined and quite unpredictable.
 * (For instance it is quite frequent that the test:
 *           toint(Inf<double>()) ==  toint(1.0/0.0)
 * will return false whilst the test:
 *           Inf<double>() == 1.0/0.0
 * returns true !)
 * If you intend to use nans and infs entries,  consider using toint instead.
 * On integral typed values the functor acts as identity.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toint.hpp>
 * \endcode
 *
 * \par Aliases
 * \arg ifix
 * \arg itrunc
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::toint_(A0)>::type
 *     toint(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of toint
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
     * \brief Define the tag toint_ of functor toint
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct toint_ : ext::elementwise_<toint_> { typedef ext::elementwise_<toint_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, toint, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, fast_toint, 1)
  //  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, itrunc, 1)

} }

#include <boost/simd/operator/specific/common.hpp>

#endif
