//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the line function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct line_ : ext::elementwise_<line_>
    {
      typedef ext::elementwise_<line_> parent;
    };
  }

  /*!
    Returns the line of index i along the selected direction,
    By default n is the first non-singleton dimension of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_       , line, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::line_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      result_type that(1);
      std::size_t along = boost::proto::child_c<1>(e);
      that[along] = boost::proto::child_c<0>(e).extent()[along];

      return that;
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::line_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
