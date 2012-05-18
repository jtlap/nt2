//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_FULL_QR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_FULL_QR_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/full_qr_solve.hpp>
#include <nt2/toolbox/linalg/functions/solvers/full_qr_solve.hpp>
#include <nt2/toolbox/linalg/functions/solvers/options.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of full_qr_solve is called whenever a tie(...) = full_qr_solve(...) is captured
  // before assign is resolved. As a tieable function, full_qr_solve retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::full_qr_solve_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::full_qr_solve_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename solvers::options                                    opts_t; 
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          dest0_t;
    typedef typename meta::
            call< nt2::tag::
                  solvers::full_qr_solve_(dest0_t&, dest0_t&, char, nt2::details::in_place_)
                >::type                                                 solve_t;
    
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy equation rhs in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<1>(a0);
      // Copy the matrix somewhere
      dest0_t a = boost::proto::child_c<0>(a0); 

      // solve in place
      solve_t f = solvers::full_qr_solve(a, boost::proto::child_c<0>(a1),'N',in_place_);
      solve(f, a1, N1());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void solve(solve_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.x();
    }

    BOOST_FORCEINLINE
    void solve(solve_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.x();
      boost::proto::child_c<1>(a1) = f.rank();
    }
  };
} }

#endif
