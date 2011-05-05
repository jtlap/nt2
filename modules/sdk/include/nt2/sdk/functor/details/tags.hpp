//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_DETAILS_TAGS_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_TAGS_HPP_INCLUDED

/*!
 * \file
 * Defines the operator related functor tags.
 */
#include <boost/proto/tags.hpp>

//==============================================================================
/*!
 * \namespace nt2::tag
 * The \ref nt2::tag namespace gathers all types used as mark-up.
 */
//==============================================================================
namespace nt2{ namespace tag
{
  //============================================================================
  /*!
   * \typedef unary_minus_
   * tag for unary  operator- implementation
   * \typedef unary_plus_
   * tag for unary operator+ implementation
   * \typedef complement_
   * tag for operator~ implementation
   * \typedef logical_not_
   * tag for operator! implementation
   */
  //============================================================================
  typedef boost::proto::tag::negate             unary_minus_;
  typedef boost::proto::tag::unary_plus         unary_plus_;
  typedef boost::proto::tag::complement         complement_;
  typedef boost::proto::tag::logical_not        logical_not_;

  //============================================================================
  /*!
   * \typedef plus_
   * tag for binary operator+ implementation
   * \typedef minus_
   * tag for binary  operator- implementation
   * \typedef multiplies_
   * tag for binary operator* implementation
   * \typedef divides_
   * tag for operator/ implementation
   * \typedef modulo_
   * tag for operator% implementation
   * \typedef bitwise_xor_
   * tag for operator^ implementation
   * \typedef bitwise_or_
   * tag for operator| implementation
   * \typedef bitwise_and_
   * tag for operator& implementation
   * \typedef logical_or_
   * tag for operator|| implementation
   * \typedef logical_and_
   * tag for operator&& implementation
   * \typedef is_equal_
   * tag for operator== implementation
   * \typedef is_not_equal_
   * tag for operator!= implementation
   * \typedef is_less_
   * tag for operator< implementation
   * \typedef is_greater_
   * tag for operator> implementation
   * \typedef is_less_equal_
   * tag for operator<= implementation
   * \typedef is_greater_equal_
   * tag for operator>= implementation
   * \typedef shift_left_
   * tag for operator<< implementation
   * \typedef shift_right_
   * tag for operator>> implementation
   */
  //============================================================================
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

  //============================================================================
  /*!
   * \typedef if_else_
   * tag for the ternary selection function implementation
   */
  //============================================================================
  typedef boost::proto::tag::if_else_           if_else_;

  //============================================================================
  /*!
   * \typedef pre_inc_
   * tag for prefixed operator++ implementation
   * \typedef pre_dec_
   * tag for prefixed operator-- implementation
   * \typedef post_inc_
   * tag for postfixed operator++ implementation
   * \typedef post_dec_
   * tag for postfixed operator-- implementation
   */
  //============================================================================
  typedef boost::proto::tag::pre_inc            pre_inc_;
  typedef boost::proto::tag::pre_dec            pre_dec_;
  typedef boost::proto::tag::post_inc           post_inc_;
  typedef boost::proto::tag::post_dec           post_dec_;

  //============================================================================
  /*!
   * \typedef assign_
   * tag for operator= implementation
   * \typedef plus_assign_
   * tag for operator+= implementation
   * \typedef minus_assign_
   * tag for operator-= implementation
   * \typedef multiplies_assign_
   * tag for operator*= implementation
   * \typedef divides_assign_
   * tag for operator/= implementation
   * \typedef modulo_a=ssign_
   * tag for operator% implementation
   * \typedef bitwise_xor_assign_
   * tag for operator^= implementation
   * \typedef bitwise_or_assign_
   * tag for operator|= implementation
   * \typedef bitwise_and_assign_
   * tag for operator&= implementation
   * \typedef shift_left_assign_
   * tag for operator<<= implementation
   * \typedef shift_right_assign_
   * tag for operator>>= implementation
   */
  //============================================================================
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

  //============================================================================
  /*!
   * \typedef terminal_
   * tag for terminal_ nodes in expression
   * \typedef function_
   * tag for operator() function implementation
   * \typedef comma_
   * tag for operator, implementation
   */
  //============================================================================
  typedef boost::proto::tag::terminal           terminal_;
  typedef boost::proto::tag::function           function_;
  typedef boost::proto::tag::comma              comma_;
} }

#endif
