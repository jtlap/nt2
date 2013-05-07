//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE_HPP_INCLUDED

#include <nt2/core/functions/freqspace.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // freqspace(a0)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)
                            , ((scalar_< integer_<A0> >))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , box<_2D>
                                          , A0
                                          , meta::as_<double>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator ()(const A0& a0) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( boxify( _2D(1,1+a0/2) )
                            , a0
                            , meta::as_<double>()
                            );
    }
  };

  //============================================================================
  // freqspace(a0,whole_)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)
                            , ((scalar_< integer_<A0> >))
                              ((unspecified_<A1>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , box<_2D>
                                          , A0
                                          , meta::as_<double>
                                          , meta::as_<A1>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator ()(const A0& a0, const A1&) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( boxify( _2D(1,a0) )
                            , a0
                            , meta::as_<double>()
                            , meta::as_<A1>()
                            );
    }
  };

  //============================================================================
  // freqspace(a0,as<T>)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)
                            , ((scalar_< integer_<A0>  >))
                              ((target_< floating_<A1> >))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , box<_2D>
                                          , A0
                                          , meta::as_<A1>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator ()(const A0& a0,const A1& a1) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( boxify( _2D(1,1+a0/2) ), a0, a1 );
    }
  };

  //============================================================================
  // freqspace(a0,whole_, as<T>)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((scalar_< integer_<A0> >))
                              ((unspecified_<A1>))
                              ((target_< floating_<A2> >))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , box<_2D>
                                          , A0
                                          , meta::as_<A2>
                                          , meta::as_<A1>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator ()(const A0& a0, const A1&, const A2& a2) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( boxify( _2D(1,a0) ), a0, a2, meta::as_<A2>());
    }
  };
} }

#endif
