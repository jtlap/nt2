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
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_INTERP1_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_INTERP1_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau interp1
 *
 * \par Description
 * one dimensional interp1 interpolation
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/interp1.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::interp1_(A0)>::type
 *     interp1(const A0 & a0, const A1 & a1, const A2 & a2);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag interp1_ of functor interp1
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct interp1_ : ext::unspecified_<interp1_> { typedef ext::unspecified_<interp1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 5)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::interp1_, Domain, N, Expr>
        : meta::size_as<Expr,2>
  {};

 template <class Domain, class Expr,  int N>
 struct value_type < tag::interp1_, Domain,N,Expr>
  : meta::value_as<Expr,1>
 {};
} }

#endif
