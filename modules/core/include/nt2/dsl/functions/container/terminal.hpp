//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_TERMINAL_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/have_compatible_alignments.hpp>
#include <boost/simd/toolbox/operator/functions/unaligned_load.hpp>
#include <boost/simd/toolbox/operator/functions/unaligned_store.hpp>
#include <nt2/core/settings/details/fusion.hpp>
#include <nt2/sdk/meta/safe_at.hpp>

// TODO: storage order is not used.

namespace nt2 { namespace ext
{
  //============================================================================
  // terminal for 0-dimensional access (no-op)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::terminal_, tag::cpu_
                               , (A0)(State)(Data)
                               , (mpl::bool_< fusion::result_of::size<State>::type::value == 0 >)
                               , (ast_<A0>)
                                 (fusion_sequence_<State>)
                                 (unspecified_<Data>)
                               )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0&>::type                                  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // table terminal with a position in scalar read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (fusion_sequence_<State>)
                              (target_<scalar_<unspecified_<Data> > >)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0&>::type
              >::type                               result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const&) const
    {
       return boost::proto::value(a0)[state];
    }
  };

  //============================================================================
  // table terminal with a position in scalar write mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(State)(Data)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (fusion_sequence_<State>)
                              (scalar_<unspecified_<Data> >)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0&>::type
             >::type                                result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const& data) const
    {
       return boost::proto::value(a0)[state] = data;
    }
  };

  //============================================================================
  // table terminal with a position in SIMD read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(Seq)(A)(Data)(X)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              ((position_<Seq, A>))
                              ((target_< simd_<unspecified_<Data>, X> >))
                            )
  {
    typedef typename Data::type                                  result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, Seq const& state, Data const&) const
    {
      return eval(a0, state, have_compatible_alignments<A0, A>());
    }

    inline result_type eval ( A0 const& a0, Seq const& state, boost::mpl::true_ const& ) const
    {
      return load<result_type>(boost::proto::value(a0).get(
                                 boost::fusion::at_c<
                                   boost::fusion::result_of::size<Seq>::type::value-1
                                 >(state)
                               ),
                               nt2::meta::default_at_c<
                                 boost::fusion::result_of::size<Seq>::type::value-2, 0
                               >(state));
    }

    inline result_type eval ( A0 const& a0, Seq const& state, boost::mpl::false_ const& ) const
    {
      return boost::simd::unaligned_load<result_type>(boost::proto::value(a0).get(
                                 boost::fusion::at_c<
                                   boost::fusion::result_of::size<Seq>::type::value-1
                                 >(state)
                               ),
                               nt2::meta::default_at_c<
                                 boost::fusion::result_of::size<Seq>::type::value-2, 0
                               >(state));
    }
  };

  //============================================================================
  // table terminal with a position in SIMD write mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(S0)(Seq)(A)(Data)(X)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              ((position_<Seq, A>))
                              ((simd_<unspecified_<Data>, X>))
                            )
  {
    typedef Data                                            result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, Seq const& state, Data const& data) const
    {
      return eval(a0, state, data, have_compatible_alignments<A0, A>());
    }

    BOOST_FORCEINLINE result_type
    eval(A0& a0, Seq const& state, Data const& data, boost::mpl::true_ const&) const
    {
      return store<result_type>(data, boost::proto::value(a0).get(
                                  boost::fusion::at_c<
                                    boost::fusion::result_of::size<Seq>::type::value-1
                                  >(state)
                                ),
                                nt2::meta::default_at_c<
                                  boost::fusion::result_of::size<Seq>::type::value-2, 0
                                >(state));
    }

    BOOST_FORCEINLINE result_type
    eval(A0& a0, Seq const& state, Data const& data, boost::mpl::false_ const&) const
    {
      return boost::simd::unaligned_store<result_type>(data, boost::proto::value(a0).get(
                                  boost::fusion::at_c<
                                    boost::fusion::result_of::size<Seq>::type::value-1
                                  >(state)
                                ),
                                nt2::meta::default_at_c<
                                  boost::fusion::result_of::size<Seq>::type::value-2, 0
                                >(state));
    }
  };

  //============================================================================
  // scalar terminal, return value in scalar mode (LHS not allowed)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (fusion_sequence_<State>)
                              (target_< scalar_< unspecified_<Data> > >)
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0&>::type                                  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const&, Data const&) const
    {
       return boost::proto::value(a0);
    }
  };

  //============================================================================
  // scalar terminal, splat value in SIMD read mode (LHS not allowed)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (fusion_sequence_<State>)
                              ((target_< simd_< unspecified_<Data>,X > >))
                            )
  {
    typedef typename Data::type   result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, State const&, Data const&) const
    {
      return nt2::splat<result_type>(boost::proto::value(a0));
    }
  };
} }

#endif
