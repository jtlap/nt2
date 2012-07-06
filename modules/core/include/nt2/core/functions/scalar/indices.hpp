//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INDICES_HPP_INCLUDED

#include <nt2/core/functions/indices.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/indices.hpp>
#include <nt2/core/functions/details/indices.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>

namespace nt2 {  namespace ext
{
  //============================================================================
  // Generates indices from a pair of integers
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::indices_
      , container::domain
      , box<_2D>
      , box< nt2::details::indices >
      ,  meta::as_<double>
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A0 const& m, const A1 &, const A2& dim) const
    {
      return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(of_size(n,m))
                                        , boxify(nt2::details::indices(dim))
                                        , meta::as_<double>()
                                        );
    }
  };
  
  //============================================================================
  // Generates indices from one integer return doubles
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (scalar_< integer_<A0> >)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::indices_
      , container::domain
      , box<_2D>
      , box< nt2::details::indices >
      ,  meta::as_<double>
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, const A1 &, const A2& dim) const
    {
      return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(of_size(n,n))
                                        , boxify(nt2::details::indices(dim))
                                        , meta::as_<double>()
                                        );
    }
  };
  
  //============================================================================
  // Generates indices from a pair of integers
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)(A2)(T)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::indices_
      , container::domain
      , box<_2D>
      , box< nt2::details::indices >
      , T
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A0 const& m, const A1 &, const A2& dim, T const& ) const
    {
      return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(of_size(n,m))
                                        , boxify(nt2::details::indices(dim))
                                        , T()
                                        );
    }
  };
                              
  //============================================================================
  // Generates indices from one integer
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                              , (A0)(A1)(A2)(T)
                              , (scalar_< integer_<A0> >)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::indices_
      , container::domain
      , box<_2D>
      , box< nt2::details::indices >
      , T
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, const A1 &, const A2& dim, T const& ) const
    {
     return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(of_size(n,n))
                                        , boxify(nt2::details::indices(dim))
                                        ,T()
                                        );
    }
  };

  //============================================================================
  // Generates indices from fusion sequence (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                              , (Seq)(A2)
                              , (fusion_sequence_<Seq>)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename meta::strip<Seq>::type seq_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::indices_
                                          , container::domain
                                          , box<seq_t>
                                          , box<nt2::details::indices>
                                          , meta::as_<double>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq, const A2& dim) const
    {
      return  boost::proto::
              make_expr < nt2::tag::indices_
                        , container::domain
                        > ( boxify(seq)
                            , boxify(nt2::details::indices(dim))
                            , meta::as_<double>()
                          );
    }
  };

  //============================================================================
  // Generates indices from fusion sequence + types (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                              , (Seq)(A1)(T)
                            , (fusion_sequence_<Seq>)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename meta::strip<Seq>::type seq_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::indices_
                                          , container::domain
                                          , box<seq_t>
                                          , box<nt2::details::indices>
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq, const A1& dim, T const& ) const
    {
      return  boost::proto::
              make_expr<  nt2::tag::indices_
                        , container::domain
                        > ( boxify(seq)
                          , boxify(nt2::details::indices(dim))
                            , T()
                          );
    }
  };
                              
} }

#endif
