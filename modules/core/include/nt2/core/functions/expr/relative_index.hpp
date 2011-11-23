//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/fusion/include/single_view.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Tag)(A1)(A2)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::container::domain
                                      , Tag
                                      >
                              ))
                              (fusion_sequence<A1>)
                              (mpl_integral_< scalar_< integer_<A2> > >)
                            )
  {
    typedef typename A0::formal_type result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& indexer, const A1& pos, const A2& ) const
    {
      return nt2::run ( indexer
                      , pos
                      , meta::as_<result_type>::type>()
                      );
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((expr_ < colon_< A0 >
                                      , nt2::container::domain
                                      , tag::terminal_
                                      >
                              ))
                              (fusion_sequence<A1>)
                              (mpl_integral_< scalar_< integer_<A2> > >)
                            )
  {
    //typedef typename boost::proto::result_of::value<A0>::type  result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1& pos, const A2& ) const
    {
      return boost::fusion::at_c<A2::value>(pos);
    }
  };
} }

#endif
