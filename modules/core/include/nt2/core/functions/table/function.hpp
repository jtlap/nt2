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
      typedef typename boost::fusion::result_of::
      fold< typename boost::
            remove_reference< typename size_transform<Domain>::template
                              result<size_transform<Domain>( typename boost::fusion::result_of::
                                                             at_c< Children
                                                                 , N
                                                                 >::type
                                                           )
                                    >::type
                            >::type
          , boost::mpl::size_t<1>
          , nt2::functor<tag::multiplies_>
          >::type
      result_type;

      BOOST_DISPATCH_FORCE_INLINE
      result_type operator()(Sz, Children children) const
      {
        return boost::fusion::fold(
            size_transform<Domain>()(boost::fusion::at_c<N>(children))
          , boost::mpl::size_t<1>()
          , nt2::functor<tag::multiplies_>()
          );
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

      typedef meta::
              call<tag::slice_( Sz
                              , memory::no_padding
                              , boost::mpl::int_<N+1>
                              )>  true_type;

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
        return slice<N+1>(sz,memory::no_padding());
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
    child_c<Expr, 0>::type                             child0;

    typedef typename boost::fusion::result_of::
    pop_front<Expr>::type                              childN;

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
} } }

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
