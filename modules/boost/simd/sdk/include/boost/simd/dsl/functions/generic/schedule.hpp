//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED

#include <boost/simd/dsl/functions/schedule.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/proto/unpack.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

#include <boost/proto/make_expr.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>

namespace boost { namespace simd { namespace ext
{
  template<class Tag>
  struct unpack_schedule_impl
  : proto::
    unpack< proto::
            call< dispatch::
                  functor<Tag, tag::formal_>
                > ( proto::
                    when< proto::_
                        , proto::call< typename dispatch::
                                       make_functor< tag::schedule_, Tag>
                                                     ::type ( proto::_expr
                                                            , proto::_state
                                                            )
                                     >
                        >
                  )
          >
  {
  };

  struct unpack_schedule
  {
    template<class Sig>
    struct result;

    template<class This, class Expr, class State>
    struct result<This(Expr, State)>
      : unpack_schedule_impl<typename proto::tag_of<Expr>::type>::template
        result< unpack_schedule_impl< typename proto::tag_of<Expr
                                    >::type> ( typename dispatch::meta::as_ref<Expr>::type
                                             , State
                                             )
              >
    {
    };

    template<class Expr, class State>
    typename result<unpack_schedule(Expr&, State const&)>::type
    operator()(Expr& expr, State const& st) const
    {
      return unpack_schedule_impl<typename proto::tag_of<Expr>::type>()(expr, st);
    }

    template<class Expr, class State>
    typename result<unpack_schedule(Expr const&, State const&)>::type
    operator()(Expr const& expr, State const& st) const
    {
      return unpack_schedule_impl<typename proto::tag_of<Expr>::type>()(expr, st);
    }
  };

  //==============================================================================
  // Jump to schedule_assign if assign node
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)
                                   , ((node_<A0, boost::simd::tag::assign_, mpl::long_<2> >))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename boost::proto::result_of::child_c<A0&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<A0&, 1>::type child1;
    typedef typename dispatch::meta::call<tag::schedule_assign_(child0, child1, F&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F& f) const
    {
      return schedule_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), f);
    }
  };

  //==============================================================================
  // Elementwise
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, elementwise_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule::template result<unpack_schedule(A0&, F&)>::type  child0;
    typedef typename unpack_schedule::template result<unpack_schedule(A1&, F&)>::type  child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type          result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F& f) const
    {
      return boost::simd::assign(unpack_schedule()(a0, f), unpack_schedule()(a1, f));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, elementwise_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule::template result<unpack_schedule(A0&, F&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F& f) const
    {
      return unpack_schedule()(a0, f);
    }
  };

  //==============================================================================
  // Reduction
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, unspecified_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule::template result<unpack_schedule(A0&, F&)>::type  child0;
    typedef typename unpack_schedule::template result<unpack_schedule(A1&, F&)>::type  child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type          assigned;
    typedef typename dispatch::meta::result_of<F(assigned)>::type                      result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F& f) const
    {
      return f(boost::simd::assign(unpack_schedule()(a0, f), unpack_schedule()(a1, f)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, unspecified_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename dispatch::meta::
            strip< typename dispatch::meta::
                  terminal_of< typename dispatch::meta::semantic_of<A0&>::type
                             >::type
                 >::type                                                               terminal;
    typedef terminal                                                                   child0;
    typedef typename unpack_schedule::template result<unpack_schedule(A0&, F&)>::type  child1;
    typedef typename proto::result_of::
            make_expr<proto::tag::assign, child0, child1>::type                        assigned;
    typedef typename dispatch::meta::result_of<F(assigned)>::type                      result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F& f) const
    {
      /* FIXME: this leads to the terminal being copied many times over;
       *        find a way to avoid all copies. */
      typedef typename mpl::if_< is_reference<child1>
                               , reference_wrapper<typename remove_reference<child1>::type>
                               , child1 const&
                               >::type ref;
      return f(proto::make_expr<proto::tag::assign>(terminal(), ref(unpack_schedule()(a0, f))));
    }
  };

} } }

#endif
