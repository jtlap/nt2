/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED

#include <nt2/sdk/dsl/from_domain.hpp>
#include <nt2/sdk/dsl/is_assignment_expression.hpp>
#include <nt2/sdk/constant/category.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // grammar is a template class to avoid a complex, recursive type matching
  // to ensure that SIMD expression of different T/Card are not mixed.
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class Card>
  struct grammar
    : boost::proto
        ::or_ <
              //  Terminals are pack, named and unnamed constants
                boost::proto::terminal< data<T,Card> >
              , boost::proto::terminal< tag::constant_<boost::proto::_> >
              , boost::proto::
                and_< boost::proto::terminal<boost::proto::_>
                    , boost::proto::if_ < boost::
                                          is_arithmetic<boost::proto::_value>()
                                        >
                    >
              //  Nodes are cross-domain node, any non-low level nodes with
              //  matching type/cardinal
              , dsl::from_domain< boost::proto::_ >
              , boost::proto::
                and_< boost::proto::
                      nary_expr < boost::proto::_
                                , boost::proto::vararg< grammar<T,Card> >
                                >
                    , boost::proto::
                      not_< boost::proto::or_ < boost::proto::
                                                address_of< grammar<T,Card> >
                                              , boost::proto::
                                                dereference< grammar<T,Card> >
                                              , boost::proto::
                                                comma < grammar<T,Card>
                                                      , grammar<T,Card>
                                                      >
                                              , boost::proto::
                                                switch_<details::assign_cases>
                                              >
                          >
                    >
              > {};
} }

#endif
