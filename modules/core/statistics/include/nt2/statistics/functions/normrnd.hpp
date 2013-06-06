//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm normrnd
 *
 * \par Description
 * normal pseudo random numbers generator
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/normrnd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::normrnd_(A0)>::type
 *     normrnd(const A1 &m, const A2 & sig, ... dimension(s));
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag normrnd_ of functor normrnd
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct normrnd_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; };
  }

 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 2)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 3)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 4)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 5)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 6)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 7)
}

#endif
