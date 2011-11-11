/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_IS_ASSIGNMENT_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_IS_ASSIGNMENT_EXPRESSION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check if a given proto expression has a ?= tag
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/matches.hpp>

namespace boost { namespace simd {  namespace details
{
  struct assign_cases
  {
    template<class Tag> struct case_ : boost::proto::not_< boost::proto::_ > {};
  };

  template<>
  struct  assign_cases::case_< boost::proto::tag::shift_right_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::shift_left_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::multiplies_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::divides_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::modulus_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::plus_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::minus_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::bitwise_and_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::bitwise_or_assign >
        : boost::proto::_ {};

  template<>
  struct  assign_cases::case_< boost::proto::tag::bitwise_xor_assign >
        : boost::proto::_ {};
} } }

namespace boost { namespace simd {  namespace meta
{
  struct  assignment_operators
        : boost::proto::switch_< details::assign_cases>
  {};

  template<class Expr>
  struct  is_assignment_expression
        : boost::proto::matches < Expr
                                , assignment_operators
                                >
  {};
} } }

#endif
