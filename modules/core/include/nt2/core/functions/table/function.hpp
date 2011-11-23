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
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <nt2/core/functions/table/details/function/size.hpp>
#include <nt2/core/functions/table/details/function/value_type.hpp>

namespace nt2 { namespace container { namespace ext
{
  // assumes all nodes are terminals, incorrect
  // Must handle : expr<scalar>, expr<colon>, expr<?>
  template<class State>
  struct function_state_impl
  {
    template<class Sig> struct result;

    template<class This, class A0>
    struct result<This(A0)> : boost::proto::result_of::value<A0> {};

    function_state_impl(State const& s) : state_(s) {}
    State const& state_;

    template<class A0>
    BOOST_DISPATCH_FORCE_INLINE typename result<function_state_impl(A0&)>::type
    operator()(A0& a0) const
    {
      return boost::proto::value(a0);
    }
  };

  template<class Expr, class State>
  struct function_state
  {
    typedef typename boost::fusion::result_of::
    transform<Expr const, function_state_impl<State> >::type result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr const& expr, State const& state) const
    {
      return boost::fusion::transform(expr, function_state_impl<State>(state));
    }
  };
} }

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
                      child_c<Expr const&, 0>::type  child0;
    typedef typename  boost::fusion::result_of::
                      pop_front<Expr const>::type   childN;

    typedef typename container::ext::
            function_state<Expr, State>::result_type                         new_state;
            
    typedef typename meta::
            call<tag::run_(child0, new_state, Data const&)>::type            result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr const& expr, State const& state, Data const& data) const
    {
      return nt2::run( boost::proto::child_c<0>(expr)
                     , container::ext::function_state<childN, State>()
                       (boost::fusion::pop_front(expr), state)
                     , data
                     );
    }
  };
} }

#endif
