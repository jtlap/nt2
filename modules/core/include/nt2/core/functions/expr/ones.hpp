//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ONES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ONES_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/ones.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/utility/generator/generator.hpp>
#include <nt2/core/utility/generator/preprocessor.hpp>
#include <nt2/core/utility/generator/constant_adaptor.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates Ones from expression (support size(a) calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::One, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::One>
                      , double
                      , settings(of_size_max)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      of_size_max sizee;
      container::domain domain_;
      nt2::details::constant_generator<nt2::tag::One> callee;

      for(std::size_t i=1;i<of_size_max::size();++i) sizee[i-1] = a0(i);
      return domain_( expr_type::make( base(sizee,callee) ) );
    }
  };

  //============================================================================
  // Generates Ones from expression + types (support size(a) calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::One, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef nt2::details::
            generator < nt2::tag::table_
                      , nt2::details::constant_generator<nt2::tag::One>
                      , typename T::type
                      , settings(of_size_max)
                      > base;

    typedef typename boost::proto::terminal<base>::type  expr_type;
    typedef typename boost::
            result_of<container::domain(expr_type)>::type const result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const
    {
      of_size_max sizee;
      container::domain domain_;
      nt2::details::constant_generator<nt2::tag::One> callee;

      for(std::size_t i=1;i<of_size_max::size();++i) sizee[i-1] = a0(i);
      return domain_( expr_type::make( base(sizee,callee) ) );
    }
  };
} }

#endif
