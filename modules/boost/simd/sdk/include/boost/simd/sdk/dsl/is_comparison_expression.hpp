/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_IS_COMPARISON_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_IS_COMPARISON_EXPRESSION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check if a given proto expression has a tag of a comaprison operator
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/matches.hpp>

namespace boost { namespace simd {  namespace details
{
  struct compare_cases
  {
    template<class Tag> struct case_ : boost::proto::not_< boost::proto::_ > {};
  };

  template<>
  struct  compare_cases::case_< boost::proto::tag::equal_to >
        : boost::proto::_ {};

  template<>
  struct  compare_cases::case_< boost::proto::tag::not_equal_to >
        : boost::proto::_ {};

  template<>
  struct  compare_cases::case_< boost::proto::tag::less >
        : boost::proto::_ {};

  template<>
  struct  compare_cases::case_< boost::proto::tag::greater >
        : boost::proto::_ {};

  template<>
  struct  compare_cases::case_< boost::proto::tag::less_equal >
        : boost::proto::_ {};

  template<>
  struct  compare_cases::case_< boost::proto::tag::greater_equal >
        : boost::proto::_ {};
} } }

namespace boost { namespace simd {  namespace meta
{
  struct  comparison_operators
        : boost::proto::switch_< details::compare_cases>
  {};

  template<class Expr>
  struct  is_comparison_expression
        : boost::proto::matches < Expr
                                , comparison_operators
                                >
  {};
} } }

#endif
