//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_EXPAND_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_EXPAND_TO_HPP_INCLUDED

#include <nt2/core/functions/expand_to.hpp>
#include <nt2/core/functions/common/expand_to.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/repnum.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + of_size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::expand_to_
                                          , container::domain
                                          , A0 const&
                                          , box<sizes_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return  boost::proto::
              make_expr < nt2::tag::expand_to_
                        , container::domain
                        > ( boost::cref(a0), boxify(a1) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repnum_
                                          , container::domain
                                          , box<sizes_t>
                                          , box<nt2::details::repnum<A0> >
                                          , meta::as_<A0>
                                          >::type   result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      return  boost::proto::
              make_expr<nt2::tag::repnum_, container::domain>
              ( boxify(a1)
              , boxify(nt2::details::repnum<A0>(a0))
              , meta::as_<A0>()
              );
    }
  };

  //============================================================================
  // Generates linearize_ from expression + expression containing size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::expand_to_
                                          , container::domain
                                          , A0 const&
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
    {
      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a1));
      nt2::memory::copy(a1.raw(), a1.raw()+sz, &sizee[0]);

      return  boost::proto::
              make_expr < nt2::tag::expand_to_
                        , container::domain
                        > ( boost::cref(a0), boxify(sizee) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )
                              (ast_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repnum_
                                          , container::domain
                                          , box<of_size_max>
                                          , box<nt2::details::repnum<A0> >
                                          , meta::as_<A0>
                                          >::type   result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      BOOST_ASSERT_MSG
      ( nt2::isrow(a1)
      , "Error using repmat: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a1));
      nt2::memory::cast_copy(a1.raw(), a1.raw()+sz, &sizee[0]);

      return  boost::proto::
              make_expr<nt2::tag::repnum_, container::domain>
              ( boxify(sizee)
              , boxify(nt2::details::repnum<A0>(a0))
              , meta::as_<A0>()
              );
    }
  };
  
} }

#endif
