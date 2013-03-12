//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED

#include <nt2/toolbox/statistics/functions/caurnd.hpp>
#include <nt2/include/functions/cauinv.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Perform the evaluation of a0 = caurnd(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::caurnd_, N,nt2::container::domain> ))
                            )
  {
    typedef typename meta::
            strip<typename meta::scalar_of<A0>::type>::type sA0;
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in) const
    {
      // Setup lhs memory using size informations from rhs
      out.resize(in.extent());

      // Fill randomly and apply inverse distribution
      out = nt2::rand(in.extent(), meta::as_<sA0>());
      out = nt2::cauinv ( out
                        , boost::proto::child_c<0>(in)
                        , boost::proto::child_c<1>(in)
                        );

      return out;
    }
  };

  //============================================================================
  // caurnd(x,y)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::call<tag::extent_(A0)>::type ext0t_t;
    typedef typename meta::call<tag::extent_(A1)>::type ext1t_t;
    typedef typename meta::strip<ext0t_t>::type  ext0_t;
    typedef typename meta::strip<ext1t_t>::type  ext1_t;
    typedef typename make_size< !(ext0_t::static_size <= ext1_t::static_size)
                              ? ext0_t::static_size
                              : ext1_t::static_size
                              >::type                     extent_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < tag::caurnd_,container::domain
                                , A0 const&
                                , A1 const&
                                , box<extent_t>
                                >::type                           result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& l) const
    {
      return  boost::proto
            ::make_expr<nt2::tag::caurnd_,container::domain>
            ( boost::cref(m)
            , boost::cref(l)
            , boxify( nt2::max( nt2::extent(m), nt2::extent(l) ) )
            );

    }
  };

  //============================================================================
  // caurnd(x,y,size)
  //============================================================================
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (unspecified_<A0>)
//                               (unspecified_<A1>)
//                               (unspecified_<A2>)
//                               )
//   {
//     typedef typename meta::call<tag::extent_(A0)>::type ext0_t;
//     typedef typename meta::call<tag::extent_(A1)>::type ext1_t;
//     typedef nt2::table<size_t>                        extent_t;

//     typedef typename  boost::proto::result_of
//                     ::make_expr < tag::caurnd_,container::domain
//                                 , A0 const&
//                                 , A1 const&
//                                 , box<extent_t>
//                                 >::type                           result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& l, A2 const& sz) const
//     {
//       table<size_t> sz1 = nt2::max(nt2::max(nt2::extent(m), nt2::extent(l)), sz);
//       return  boost::proto
//             ::make_expr<nt2::tag::caurnd_,container::domain>
//             ( boost::cref(m)
//             , boost::cref(l)
//             , boxify(sz1)
//             );

//     }
//   };

  //============================================================================
  // caurnd(x,y,extent)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename meta::call<tag::extent_(A0)>::type ext0t_t;
    typedef typename meta::call<tag::extent_(A1)>::type ext1t_t;
    typedef typename meta::strip<ext0t_t>::type  ext0_t;
    typedef typename meta::strip<ext1t_t>::type  ext1_t;
    typedef typename make_size< !(ext0_t::static_size <= ext1_t::static_size)
                              ? ext0_t::static_size
                              : ext1_t::static_size
                              >::type                     extent_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < tag::caurnd_,container::domain
                                , A0 const&
                                , A1 const&
                                , box<extent_t>
                                >::type                           result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& m, A1 const& l, A2 const& sz) const
    {
      return  boost::proto
            ::make_expr<nt2::tag::caurnd_,container::domain>
            ( boost::cref(m)
            , boost::cref(l)
            , boxify(nt2::max(nt2::max(nt2::extent(m), nt2::extent(l)), sz))
            );

    }
  };

  //============================================================================
  // caurnd(x,y,d0) ...
  //============================================================================


//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
//                               , (A0)(A0b)(A1)
//                               , (unspecified_<A0> )
//                                 (unspecified_<A0b> )
//                                 (unspecified_<A1>)
//                             )
//   {
//     typedef typename meta::scalar_of<A0>::type                                          sA0;
//     typedef meta::as_<sA0>                                                              TGT;
//     typedef nt2::table<sA0>                                                           tab_t;
//     typedef typename meta::call<tag::cauinv_(tab_t,A0 const&,A0b const&)>::type result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l, A1 const& a1) const
//     {
//       nt2::table<sA0> pipo(a1);
//       nt2::table<sA0> r = nt2::rand(nt2::max(nt2::size(pipo), nt2::max(nt2::size(l), nt2::size(m))), meta::as_<sA0>());
//       return nt2::cauinv(r, m, l);
//     }
//   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, 1l, 1l>                                           T1;
    typedef typename meta::call<tag::caurnd_(A0 const&,A0b const&,T1)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1) const
    {
      return nt2::caurnd(m, l, nt2::of_size(a1, a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, 1l, 1l>                                           T1;
    typedef typename meta::call<tag::caurnd_(A0 const&,A0b const&,T1)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2) const
    {
      return nt2::caurnd(m, l, nt2::of_size(a1, a2));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)(A3)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, -1l, 1l>                                          T1;
    typedef typename meta::call<tag::caurnd_(A0 const&,A0b const&,T1)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2,
                                             A3 const& a3) const
    {
      return nt2::caurnd(m, l, nt2::of_size(a1, a2, a3));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)(A3)(A4)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                              (scalar_<integer_<A4> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, -1l, -1l>                                         T1;
    typedef typename meta::call<tag::caurnd_(T1,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2,
                                             A3 const& a3, A4 const& a4) const
    {
      return nt2::caurnd(m, l, nt2::of_size(a1, a2, a3, a4));
    }
  };

} }

#endif
