//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ZEROS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ZEROS_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/zeros.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/utility/generative/generative.hpp>
#include <nt2/core/utility/generative/preprocessor.hpp>
#include <nt2/core/utility/generative/constant_adaptor.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates zeros from expression (support size(a) calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::Zero, tag::cpu_
                            , (A0), (ast_< unspecified_<A0> >)
                            )
  {
    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::Zero>
                      , double
                      , settings(of_size_max)
                      > base;

    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      of_size_max sizee;
      nt2::details::constant_generator<nt2::tag::Zero> callee;

      for(std::size_t i=1;i<of_size_max::size();++i) sizee[i-1] = a0(i);

      base that(sizee,callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };

  //============================================================================
  // Generates zeros from expression + types (support size(a) calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::Zero, tag::cpu_
                            , (A0)(T)
                            , (ast_< unspecified_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef nt2::details::
            generative< nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::Zero>
                      , typename T::type
                      , settings(of_size_max)
                      > base;

    typedef typename  boost::proto::
                      result_of::as_expr< base
                                        , container::domain
                                        >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const
    {
      of_size_max sizee;
      nt2::details::constant_generator<nt2::tag::Zero> callee;

      for(std::size_t i=1;i<of_size_max::size();++i) sizee[i-1] = a0(i);

      base that(sizee,callee);
      return boost::proto::as_expr<container::domain>(that);
    }
  };
} }

#endif
