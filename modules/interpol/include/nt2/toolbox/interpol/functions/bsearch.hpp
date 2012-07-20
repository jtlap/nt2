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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_BSEARCH_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_BSEARCH_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup statistics
 * \defgroup interpol bsearch
 *
 * \par Description
 * one dimensional binary search
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bsearch.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::bsearch_(A0)>::type
 *     bsearch(const A0 & a0, const A1 & a1, const A2 & a2);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag bsearch_ of functor bsearch
     *        in namespace nt2::tag for toolbox interpol
    **/
    struct bsearch_ : ext::unspecified_<bsearch_> { typedef ext::unspecified_<bsearch_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::bsearch_, bsearch, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::bsearch_, Domain, N, Expr>
        : meta::size_as<Expr,1>
  {};

  template <class Domain, class Expr,  int N>
  struct value_type < tag::bsearch_, Domain,N,Expr>
  {
   typedef typename   boost::proto::result_of
                    ::child_c<Expr&, 1>::value_type::value_type elt_t;
   typedef typename nt2::meta::as_integer<elt_t>::type          type;
  };
} }

#endif
