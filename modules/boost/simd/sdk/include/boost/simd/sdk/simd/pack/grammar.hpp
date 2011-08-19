/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <boost/simd/sdk/constant/category.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/dsl/is_assignment_expression.hpp>
#include <boost/simd/sdk/dsl/is_comparison_expression.hpp>

namespace boost { namespace simd
{
  template<class T, class N> struct grammar;

  ////////////////////////////////////////////////////////////////////////////
  // grammar_cases is the switch cases for the SIMD proto grammar
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class N> struct grammar_cases
  {
    template<typename Tag, typename Dummy = void> struct  case_;
  };

  template<class T, class N> template<class Tag,class Dummy>
  struct  grammar_cases<T,N>::case_
        : boost::proto::
          and_< boost::proto::
                nary_expr < boost::proto::_
                          , boost::proto::vararg< grammar<T,N> >
                          >
              , boost::proto::
                not_< boost::proto::or_ < boost::proto::
                                          address_of< grammar<T,N> >
                                        , boost::proto::
                                          dereference< grammar<T,N> >
                                        , boost::proto::
                                          comma < grammar<T,N>
                                                , grammar<T,N>
                                                >
                                        , meta::assignment_operators
                                        , meta::comparison_operators
                                        >
                    >
              > {};

  template<class T, class N> template<class Dummy>
  struct  grammar_cases<T,N>::case_<dispatch::tag::terminal_, Dummy>
        : boost::proto::
          or_ < boost::proto::terminal< native<T,boost::proto::_> >
              , boost::proto::
                and_< boost::proto::terminal<boost::proto::_>
                    , boost::proto::if_ < boost::dispatch::details::
                                         is_array<boost::proto::_value>()>
                    >
              , boost::proto::terminal< dispatch::meta::constant_<boost::proto::_> >
              , boost::proto::
                and_< boost::proto::terminal<boost::proto::_>
                    , boost::proto::if_ < boost::
                                          is_arithmetic<boost::proto::_value>()
                                        >
                    >
              >
  {};

  ////////////////////////////////////////////////////////////////////////////
  // grammar is a template class to avoid a complex, recursive type matching
  // to ensure that SIMD expression of different T/N are not mixed.
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class N>
  struct grammar
    : boost::proto::switch_< grammar_cases<T,N> >
  {};
} }

#endif
