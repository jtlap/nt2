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
#include <nt2/include/functions/numel.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace nt2 { namespace container { namespace ext
{
  // helper to get static or -1
  template<class T, class Enable = void>
  struct mpl_value
   : boost::mpl::int_<-1>
  {
  };

  template<class T>
  struct mpl_value<T, typename boost::enable_if< boost::is_class<typename meta::strip<T>::type> >::type >
   : meta::strip<T>::type
  {
  };

  // size deduction per argument
  template<class Domain>
  struct function_size
  {
    template<class Sz, class Children, int N, int M, class Enable = void>
    struct impl
    {
      typedef typename boost::
              remove_reference< typename size_transform<Domain>::template
                                result<size_transform<Domain>
                                ( typename  boost::fusion::result_of::
                                            at_c<Children,N>::type
                                )
                                >::type
                              >::type                           seq_t;

      typedef typename meta::call<tag::numel_( seq_t )>::type   result_type;

      BOOST_DISPATCH_FORCE_INLINE
      result_type operator()(Sz, Children children) const
      {
        return
        nt2::numel( size_transform<Domain>()(boost::fusion::at_c<N>(children)) );
      }
    };

    template<class Sz, class Children, int N, int M>
    struct impl<Sz, Children, N, M, typename boost::enable_if<
      meta::is_colon< typename boost::fusion::result_of::
                      at_c<Children, N>::type
                    >
    >::type>
    {
      typedef boost::fusion::
              result_of::at_c < typename boost::remove_reference<Sz>::type
                              , N
                              >   false_type;

      typedef typename boost::fusion::result_of::pop_front<Sz>::type  seq_t;
      typedef meta::call<tag::numel_( seq_t )>                        true_type;

      typedef boost::mpl::bool_<(N == M-1)> is_final;

      typedef typename boost::mpl::
              eval_if<is_final, true_type, false_type>::type result_type;

      BOOST_DISPATCH_FORCE_INLINE
      result_type operator()(Sz sz, Children) const
      {
        return compute(sz, is_final() );
      }

      BOOST_DISPATCH_FORCE_INLINE
      result_type compute(Sz sz, boost::mpl::true_ const&) const
      {
        return nt2::numel(boost::fusion::pop_front(sz));
      }

      BOOST_DISPATCH_FORCE_INLINE
      result_type compute(Sz sz, boost::mpl::false_ const&) const
      {
        return boost::fusion::at_c<N>(sz);
      }
    };
  };

  // build size
  template<int N, class F, class Sizes, class Children>
  struct make_size;

  #define M1(z,n,t) mpl_value< typename F::template impl<Sizes, Children, n, t>::result_type >::value
  #define M2(z,n,t) that[n] = typename F::template impl<Sizes, Children, n, t>()(sz, children);

  #define M3(z,n,t)                                                            \
  template<class Dummy>                                                        \
  struct impl<n, Dummy>                                                        \
  {                                                                            \
    BOOST_DISPATCH_FORCE_INLINE                                                \
    static result_type call(Sizes sz, Children children)                       \
    {                                                                          \
      result_type that;                                                        \
      BOOST_PP_REPEAT(n, M2, t)                                                \
      return that;                                                             \
    }                                                                          \
  };

  #define M0(z,n,t)                                                            \
  template<class F, class Sizes, class Children>                               \
  struct make_size<n, F, Sizes, Children>                                      \
  {                                                                            \
    typedef of_size_<                                                          \
               BOOST_PP_ENUM(n, M1, n)                                         \
            >            result_type;                                          \
                                                                               \
                                                                               \
    template<int N, class Dummy = void>                                        \
    struct impl {};                                                            \
                                                                               \
    BOOST_PP_REPEAT(BOOST_PP_INC(n), M3, n)                                    \
                                                                               \
    BOOST_DISPATCH_FORCE_INLINE                                                \
    result_type operator()(Sizes sz, Children children) const                  \
    {                                                                          \
      return impl<result_type::static_size>::call(sz, children);               \
    }                                                                          \
  };

  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
  #undef M0
  #undef M1
  #undef M2
  #undef M3

  template<class Expr, class Domain, int N>
  struct size_of<tag::function_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                            child0;

    typedef typename boost::fusion::result_of::
    pop_front<Expr const>::type                        childN;

    typedef typename size_transform<Domain>::template
    result<size_transform<Domain>(child0)>::type       sz;

    typedef make_size<N-1, function_size<Domain>, sz, childN>  impl;
    typedef typename impl::result_type result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(Expr& e) const
    {
      return impl()(
        size_transform<Domain>()(boost::proto::child_c<0>(e))
      , boost::fusion::pop_front(e)
      );
    }
  };

  template<class Expr, class Domain, int N>
  struct value_type<tag::function_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                         child0;

    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<child0>::type
             >::type                                type;
  };

  // assumes all nodes are terminals, incorrect
  // Must handle : expr<scalar>, expr<colon>, expr<?>
  template<class State>
  struct function_state_impl
  {
    template<class Sig>
    struct result;

    template<class This, class A0>
    struct result<This(A0)>
      : boost::proto::result_of::
        value<A0>
    {
    };

    function_state_impl(State const& s) : state_(s) {}
    State const& state_;

    template<class A0>
    BOOST_DISPATCH_FORCE_INLINE
    typename result<function_state_impl(A0&)>::type
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
                                     , nt2::tag::function_
                                     , Arity
                                     >
                              ))
                              (fusion_sequence_<State>)
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::proto::result_of::child_c<Expr const&, 0>::type  child0;
    typedef typename boost::fusion::result_of::pop_front<Expr const>::type   childN;

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
