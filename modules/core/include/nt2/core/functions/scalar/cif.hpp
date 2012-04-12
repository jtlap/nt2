//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_CIF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_CIF_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/cif.hpp>
#include <nt2/core/functions/details/cif.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/core/functions/of_size.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates cif from a pair of integers
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cif_
      , container::domain
      , box<_2D>
      , box< nt2::details::cif >
      ,  meta::as_<double>
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A0 const& m) const
    {
      return boost::proto::make_expr< nt2::tag::cif_
                                    , container::domain
                                    > ( boxify(of_size(n,m))
                                      , boxify(nt2::details::cif())
                                        , meta::as_<double>()
                                        );
    }
  };
  //============================================================================
  // Generates cif from one integer return doubles
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                              , (A0)
                              , (scalar_< integer_<A0> >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cif_
      , container::domain
      , box<_2D>
      , box< nt2::details::cif >
      ,  meta::as_<double>
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
     return boost::proto::make_expr< nt2::tag::cif_
                                    , container::domain
                                    > ( boxify(of_size(n,n))
                                      , boxify(nt2::details::cif())
                                        , meta::as_<double>()
                                        );
    }
  };
  //============================================================================
  // Generates cif from a pair of integers
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                            , (A0)(T)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cif_
      , container::domain
      , box<_2D>
      , box< nt2::details::cif >
      , T
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A0 const& m, T const& ) const
    {
      return boost::proto::make_expr< nt2::tag::cif_
                                    , container::domain
                                    > ( boxify(of_size(n,m))
                                      , boxify(nt2::details::cif())
                                        , T()
                                        );
    }
  };
  //============================================================================
  // Generates cif from one integer
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cif_
      , container::domain
      , box<_2D>
      , box< nt2::details::cif >
      , T
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const& ) const
    {
     return boost::proto::make_expr< nt2::tag::cif_
                                    , container::domain
                                    > ( boxify(of_size(n,n))
                                      , boxify(nt2::details::cif())
                                        ,T()
                                        );
    }
  };

  //============================================================================
  // Generates cif from fusion sequence (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                            , (Seq)
                            , (fusion_sequence_<Seq>)
                            )
  {
    typedef typename meta::strip<Seq>::type seq_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cif_
                                          , container::domain
                                          , box<seq_t>
                                          , box<nt2::details::cif>
                                          , meta::as_<double>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq) const
    {
      return  boost::proto::
              make_expr < nt2::tag::cif_
                        , container::domain
                        > ( boxify(seq)
                          , boxify(nt2::details::cif())
                          , meta::as_<double>()
                          );
    }
  };

  //============================================================================
  // Generates cif from fusion sequence + types (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cif_, tag::cpu_
                            , (Seq)(T)
                            , (fusion_sequence_<Seq>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename meta::strip<Seq>::type seq_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cif_
                                          , container::domain
                                          , box<seq_t>
                                          , box<nt2::details::cif>
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(Seq const& seq, T const& ) const
    {
      return  boost::proto::
              make_expr<  nt2::tag::cif_
                        , container::domain
                        > ( boxify(seq)
                          , boxify(nt2::details::cif())
                            , T()
                          );
    }
  };  
} }

#endif
