//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_CHOL_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/chol.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/chol.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of chol is called whenever a tie(a,p) = chol(...) is captured
  // before assign is resolved
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (ast_<A0>)
                              (scalar_< type8_<A1> >)
                              (ast_<A2>)
                              (scalar_< integer_<A3> >)
                            )
  {
    typedef void                                            result_type;
    typedef typename meta::
            call< nt2::tag::factorization::
                  chol_(A2&,char,nt2::details::in_place_)
                >::type                                     tmp_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
    {
      // Copy data in a2 first to factorize in place later
      a2 = a0;
      tmp_t tmp = factorization::chol(a2,a1,in_place_);

      // Retrieve correct version with minimum amount of (re)allocation
      // TODO : Doing better ?
      if(a1 == 'U') a2 = tmp.upper_result();
      else          a2 = tmp.lower_result();

      // Retrieve status
      a3 = tmp.status();
    }
  };

  //============================================================================
  // Capture a tie(a) = chol(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((node_<A0,nt2::tag::tie_,boost::mpl::long_<1> >))
                              ((node_<A1,nt2::tag::chol_,N1>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      int ignore_this;

      // Pass original x, potential option, destination container and status
      nt2::chol ( boost::proto::child_c<0>(a1)
                , N1::value==1 ? 'U' : 'L'
                , boost::proto::child_c<0>(a0)
                , ignore_this
                );

      return a0;
    }
  };

  //============================================================================
  // Capture a tie(a,p) = chol(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((node_<A0,nt2::tag::tie_,boost::mpl::long_<2> >))
                              ((node_<A1,nt2::tag::chol_,N1>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      // Pass original x, potential option, destination container and status
      nt2::chol ( boost::proto::child_c<0>(a1)
                , N1::value==1 ? 'U' : 'L'
                , boost::proto::child_c<0>(a0)
                , boost::proto::value(boost::proto::child_c<1>(a0))
                );

      return a0;
    }
  };
} }

#endif
