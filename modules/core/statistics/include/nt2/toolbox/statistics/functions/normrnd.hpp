/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMRND_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/include/functor.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

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
    struct normrnd_ : ext::unspecified_<normrnd_> { typedef ext::unspecified_<normrnd_> parent; };
  }

 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 2)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 3)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 4)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 5)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 6)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::normrnd_, normrnd, 7)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of normrnd.hpp
// /////////////////////////////////////////////////////////////////////////////
