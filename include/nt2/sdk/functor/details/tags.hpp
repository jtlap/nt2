/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_TAGS_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_TAGS_HPP_INCLUDED

#include <boost/proto/tags.hpp>

////////////////////////////////////////////////////////////////////////////////
// proto operators tags reinjected into nt2::tag namespace
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Unary operators
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::negate             unary_minus_;
  typedef boost::proto::tag::unary_plus         unary_plus_;
  typedef boost::proto::tag::complement         complement_;
  typedef boost::proto::tag::logical_not        logical_not_;

  //////////////////////////////////////////////////////////////////////////////
  // Bianry Operators
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::plus               plus_;
  typedef boost::proto::tag::minus              minus_ ;
  typedef boost::proto::tag::multiplies         multiplies_ ;
  typedef boost::proto::tag::divides            divides_;
  typedef boost::proto::tag::modulus            modulo_;
  typedef boost::proto::tag::bitwise_xor        bitwise_xor_;
  typedef boost::proto::tag::bitwise_or         bitwise_or_;
  typedef boost::proto::tag::bitwise_and        bitwise_and_;
  typedef boost::proto::tag::logical_or         logical_or_;
  typedef boost::proto::tag::logical_and        logical_and_;
  typedef boost::proto::tag::equal_to           is_equal_;
  typedef boost::proto::tag::not_equal_to       is_not_equal_;
  typedef boost::proto::tag::less               is_less_;
  typedef boost::proto::tag::greater            is_greater_;
  typedef boost::proto::tag::less_equal         is_less_equal_;
  typedef boost::proto::tag::greater_equal      is_greater_equal_;
  typedef boost::proto::tag::shift_left         shift_left_;
  typedef boost::proto::tag::shift_right        shift_right_;

  //////////////////////////////////////////////////////////////////////////////
  // Ternary operators
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::if_else_           if_else_;

  //////////////////////////////////////////////////////////////////////////////
  // Self-operators require special support
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::pre_inc            pre_inc_;
  typedef boost::proto::tag::pre_dec            pre_dec_;
  typedef boost::proto::tag::post_inc           post_inc_;
  typedef boost::proto::tag::post_dec           post_dec_;

  //////////////////////////////////////////////////////////////////////////////
  // Assignment operators - requires special functor
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::assign             assign_;
  typedef boost::proto::tag::plus_assign        plus_assign_;
  typedef boost::proto::tag::minus_assign       minus_assign_;
  typedef boost::proto::tag::multiplies_assign  multiplies_assign_;
  typedef boost::proto::tag::divides_assign     divides_assign_;
  typedef boost::proto::tag::modulus_assign     modulo_assign_;
  typedef boost::proto::tag::bitwise_and_assign bitwise_and_assign_;
  typedef boost::proto::tag::bitwise_or_assign  bitwise_or_assign_;
  typedef boost::proto::tag::bitwise_xor_assign bitwise_xor_assign_;
  typedef boost::proto::tag::shift_left_assign  shift_left_assign_;
  typedef boost::proto::tag::shift_right_assign shift_right_assign_;

  //////////////////////////////////////////////////////////////////////////////
  // Additional required operators
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::proto::tag::terminal           terminal_;
  typedef boost::proto::tag::function           function_;
  typedef boost::proto::tag::comma              comma_;
} }

#endif
