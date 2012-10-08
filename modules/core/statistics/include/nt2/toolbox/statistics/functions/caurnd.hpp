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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau caurnd
 *
 * \par Description
 * cauchy pseudo random numbers generator : inverse cumulative method using rand
 * All rnd (cumulative distribution functions  can be called with the syntax
 * r = xxxrnd(param_1, ...,  param_n,  sizing_params)
 * the type of params elements determines the type of the output expression elements.
 * cauchy has 2 parameters: median and scale
 * parameters elements have no defaults
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/caurnd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::caurnd_(A0)>::type
 *     caurnd(const A0 & m, const A1 & l, ... dimensions);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag caurnd_ of functor caurnd
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct caurnd_ : ext::unspecified_<caurnd_> { typedef ext::unspecified_<caurnd_> parent; };
  }

 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 2)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 3)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 4)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 5)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 6)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::caurnd_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::caurnd_,Domain,N,Expr>
        : meta::boxed_size<Expr,2>
  {};
} }

#endif
