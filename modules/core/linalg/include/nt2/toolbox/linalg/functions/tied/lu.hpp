//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_LU_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_LU_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/lu.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/lu.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = lu(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::lu_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  child0;
    typedef typename meta::
            call< nt2::tag::
                  factorization::lu_(child0,nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);

      // Factorize in place
      fact_t f = factorization::lu(boost::proto::child_c<0>(a1),in_place_);

      decomp(f, a1, N1());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t & f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.values();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t & f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.l();
      boost::proto::child_c<1>(a1) = f.u();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t & f, A1 & a1, boost::mpl::long_<3> const&) const
    {
      boost::proto::child_c<0>(a1) = f.l();
      boost::proto::child_c<1>(a1) = f.u();
      boost::proto::child_c<2>(a1) = f.p(); 
    }
  };
} }

#endif
