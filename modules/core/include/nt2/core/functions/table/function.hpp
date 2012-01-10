//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/function.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/is_colon.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <nt2/include/functions/relative_index.hpp>

#include <nt2/core/functions/table/details/function/size.hpp>
#include <nt2/core/functions/table/details/function/value_type.hpp>

namespace nt2
{
  namespace details
  {
    template<class Res, class Indexes, class S, class Position>
    void reindex(Res& that, Indexes const&, S const&, Position const&, S const&)
    {}

    template<class Res, class Indexes, class S, class Position,class N>
    void reindex( Res& that, Indexes const& i, S const& sz, Position const& p, N const& n)
    {
      that[N::value] = relative_index(boost::fusion::at_c<N::value>(i), p, n);
      reindex( that, i, sz, p, boost::mpl::int_<N::value+1>());
    }

    template<class Indexes, class Size, class Position>
    boost::array<std::ptrdiff_t, Size::value>
    reindex( Indexes const& i, Size const& sz, Position const& p )
    {
      boost::array<std::ptrdiff_t, Size::value> that;
      reindex( that, i, sz, p, boost::mpl::int_<0>() );
      return that;
    }
  }

  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                              , (Expr)(State)(Data)(Arity)
                              , ((expr_< unspecified_<Expr>
                                       , nt2::container::domain
                                       , nt2::tag::function_
                                       , Arity
                                       >
                                ))
                                (fusion_sequence_<State>)
                                (unspecified_<Data>)
                              )
    {
      typedef typename  boost::proto::result_of::
                        child_c<Expr const&, 0>::type               child0;

      typedef boost::array<std::size_t,Arity::value-1>              new_index;

      typedef typename meta::
              call<tag::run_(child0, new_index, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr const& expr, State const& state, Data const& data) const
      {
        return nt2::run( boost::proto::child_c<0>(expr)
                       , details::reindex ( boost::fusion::pop_front(expr)
                                          , boost::mpl::int_<Arity::value-1>()
                                          , state
                                          )
                       , data
                       );
      }
    };
  }
}

#endif
