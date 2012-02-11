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
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/proto/unpack.hpp>

namespace boost { namespace simd { namespace ext
{
  template<class M, class T>
  struct same_as
   : is_same<typename M::type, T>
  {
  };

  template<class Tag>
  struct unpack_schedule
  : proto::
    unpack< proto::
            call< dispatch::
                  functor<Tag>
                > ( proto::
                    when< proto::_
                        , proto::call< typename dispatch::
                                       make_functor< tag::schedule_, Tag>
                                                     ::type ( proto::_expr
                                                            , proto::_state
                                                            , proto::_data
                                                            )
                                     >
                        >
                  )
          >
  {
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)
                                   , (ast_<A0>)
                                     (unspecified_<F>)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class F_>
    struct result<This(A0_, F_)>
    {
      typedef typename dispatch::meta::call<tag::schedule_(A0_, F const&, bool)>::type type;
    };

    template<class A0_>
    BOOST_FORCEINLINE typename result<implement(A0_&, F const&)>::type
    operator()(A0_& a0, F const& f) const
    {
      return schedule(a0, f, bool());
    }
  };

  //==============================================================================
  // Add assignment if necessary
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)(Top)
                                   , ((node_<A0, boost::simd::tag::assign_, mpl::long_<2> >))
                                     (unspecified_<F>)
                                     (scalar_< fundamental_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class F_, class Top_>
    struct result<This(A0_, F_, Top_)>
    {
      typedef typename boost::proto::result_of::child_c<A0_, 0>::type child0;
      typedef typename boost::proto::result_of::child_c<A0_, 1>::type child1;
      typedef typename dispatch::meta::call<tag::schedule_assign_(child0, child1, F_, Top_)>::type type;
    };

    template<class A0_>
    BOOST_FORCEINLINE typename result<implement(A0_&, F const&, Top)>::type
    operator()(A0_& a0, F const& f, Top top) const
    {
      return schedule_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), f, top);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)(Top)
                                   , (ast_<A0>)
                                     (unspecified_<F>)
                                     (scalar_< fundamental_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class F_, class Top_>
    struct result<This(A0_, F_, Top_)>
    {
      typedef typename dispatch::meta::semantic_of<A0_>::type semantic;
      typedef typename dispatch::meta::strip<typename dispatch::meta::terminal_of<semantic>::type>::type terminal;
      typedef typename dispatch::meta::call<tag::schedule_assign_(terminal&, A0_, F_, Top_)>::type type;
    };

    template<class A0_>
    BOOST_FORCEINLINE typename result<implement(A0_&, F const&, Top)>::type
    operator()(A0_& a0, F const& f, Top top) const
    {
      typename result<implement(A0_&, F const&, Top)>::terminal term;
      return schedule_assign(term, a0, f, top);
    }
  };

  //==============================================================================
  // Elementwise
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)(Top)
                                   , (unspecified_<A0>)
                                     ((node_<A1, elementwise_<T1>, N1>))
                                     (unspecified_<F>)
                                     (scalar_< bool_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
    {
      typedef typename unpack_schedule<T1>::template result<unpack_schedule<T1>(A1_, F_, int)>::type transformed;
      typedef typename dispatch::meta::call<tag::assign_(A0_, transformed)>::type assigned;
      typedef typename dispatch::meta::result_of<F const(assigned)>::type type;
    };

    template<class A0_, class A1_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1_&, F const&, bool)>::type
    operator()(A0_& a0, A1_& a1, F const& f, bool) const
    {
      int i;
      return f(assign(a0, unpack_schedule<T1>()(a1, f, i)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)(Top)
                                   , (unspecified_<A0>)
                                     ((node_<A1, elementwise_<T1>, N1>))
                                     (unspecified_<F>)
                                     (scalar_< integer_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)> : unpack_schedule<T1>::template result<unpack_schedule<T1>(A1_, F_, Top_)> {};

    template<class A0_, class A1_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_&, A1_& a1, F const& f, Top top) const
    {
      return unpack_schedule<T1>()(a1, f, top);
    }
  };

  //==============================================================================
  // Reduction
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)(Top)
                                   , (unspecified_<A0>)
                                     ((node_<A1, reduction_<T1>, N1>))
                                     (unspecified_<F>)
                                     (scalar_< fundamental_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
    {
      typedef typename unpack_schedule<T1>::template result<unpack_schedule<T1>(A1_, F_, int)>::type transformed;
      typedef typename dispatch::meta::call<tag::assign_(A0_, transformed)>::type assigned;
      typedef typename dispatch::meta::result_of<F const(assigned)>::type type;
    };

    template<class A0_, class A1_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_& a0, A1_& a1, F const& f, Top) const
    {
      int i;
      return f(assign(a0, unpack_schedule<T1>()(a1, f, i)));
    }
  };

  //==============================================================================
  // Unspecified
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)(Top)
                                   , ( typename mpl::
                                       eval_if< proto::is_expr<A0>
                                              , boost::simd::ext::same_as< proto::tag_of<A0>, boost::proto::tag::terminal >
                                              , mpl::true_
                                              >::type
                                     )
                                   , (unspecified_<A0>)
                                     ((node_<A1, unspecified_<T1>, N1>))
                                     (unspecified_<F>)
                                     (scalar_< fundamental_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
    {
      typedef typename unpack_schedule<T1>::template result<unpack_schedule<T1>(A1_, F_, bool)>::type transformed;
      typedef typename dispatch::meta::call<tag::assign_(A0_, transformed)>::type assigned;
      typedef typename dispatch::meta::result_of<F const(assigned)>::type type;
    };

    template<class A0_, class A1_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_& a0, A1_& a1, F const& f, Top top) const
    {
      bool b;
      return f(assign(a0, unpack_schedule<T1>()(a1, f, b)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)(Top)
                                   , ( mpl::not_< typename mpl::
                                                  eval_if< proto::is_expr<A0>
                                                         , boost::simd::ext::same_as< proto::tag_of<A0>, boost::proto::tag::terminal >
                                                         , mpl::true_
                                                         >::type
                                                >
                                     )
                                   , (unspecified_<A0>)
                                     ((node_<A1, unspecified_<T1>, N1>))
                                     (unspecified_<F>)
                                     (scalar_< unspecified_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
    {
      typedef typename unpack_schedule<T1>::template result<unpack_schedule<T1>(A1_, F_, bool)>::type transformed;
      typedef typename dispatch::meta::semantic_of<transformed>::type semantic;
      typedef typename dispatch::meta::strip<typename dispatch::meta::terminal_of<semantic>::type>::type terminal;

      typedef typename dispatch::meta::call<tag::assign_(terminal&, transformed)>::type assigned0;
      typedef typename dispatch::meta::result_of<F const(assigned0)>::type type0;

      typedef typename dispatch::meta::call<tag::assign_(A0_, type0)>::type assigned;
      typedef typename dispatch::meta::result_of<F const(assigned)>::type type;
    };

    template<class A0_, class A1_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_& a0, A1_& a1, F const& f, Top top) const
    {
      bool b;
      typename result<implement(A0_&, A1_&, F const&, Top)>::terminal term;
      return f(assign(a0, f(assign(term, unpack_schedule<T1>()(a1, f, b)))));
    }
  };

  //==============================================================================
  // Terminal
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)(Top)
                                   , ((node_<A0, boost::simd::tag::terminal_, mpl::long_<0> >))
                                     (unspecified_<F>)
                                     (scalar_< bool_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class F_, class Top_>
    struct result<This(A0_, F_, Top_)>
     : dispatch::meta::as_ref<A0_>
    {
    };

    template<class A0_>
    BOOST_FORCEINLINE typename result<implement(A0_&, F const&, Top)>::type
    operator()(A0_& a0, F const& f, Top) const
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(F)(Top)
                                   , (unspecified_<A0>)
                                     ((node_<A1, boost::simd::tag::terminal_, mpl::long_<0> >))
                                     (unspecified_<F>)
                                     (scalar_< bool_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
    {
      typedef typename dispatch::meta::call<tag::assign_(A0_, A1_)>::type assigned;
      typedef typename dispatch::meta::result_of<F const(assigned)>::type type;
    };

    template<class A0_, class A1_>
    BOOST_FORCEINLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_& a0, A1_& a1, F const& f, Top) const
    {
      return f(assign(a0, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(F)(Top)
                                   , (unspecified_<A0>)
                                     ((node_<A1, boost::simd::tag::terminal_, mpl::long_<0> >))
                                     (unspecified_<F>)
                                     (scalar_< integer_<Top> >)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_, class F_, class Top_>
    struct result<This(A0_, A1_, F_, Top_)>
      : dispatch::meta::as_ref<A1_>
    {
    };

    template<class A0_, class A1_>
    BOOST_FORCEINLINE typename result<implement(A0_&, A1_&, F const&, Top)>::type
    operator()(A0_&, A1_& a1, F const&, Top) const
    {
      return a1;
    }
  };

} } }

#endif
