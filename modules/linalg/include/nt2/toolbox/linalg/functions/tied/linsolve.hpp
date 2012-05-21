//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_LINSOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_LINSOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/linsolve.hpp>
#include <nt2/toolbox/linalg/functions/solvers/linsolve.hpp>

#include <nt2/toolbox/linalg/functions/solvers/options.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/full_lu_solve.hpp>
#include <nt2/include/functions/full_qr_solve.hpp> 

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of linsolve is called whenever a tie(...) = linsolve(...) is captured
  // before assign is resolved. As a tieable function, linsolve retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linsolve_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::linsolve_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename solvers::options                                    opts_t; 
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child1;
    typedef typename meta::strip<child0>::type                          dest0_t;
    typedef typename meta::
            call< nt2::tag::
                  solvers::full_lu_solve_ ( dest0_t&, child1
                                          , char, nt2::details::in_place_
                                          )
                >::type                                              solve_lu_t;
    typedef typename meta::
            call< nt2::tag::
                  solvers::full_qr_solve_ ( dest0_t&, child1
                                          , char, nt2::details::in_place_
                                          )
                >::type                                              solve_qr_t;


    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy equation rhs in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<1>(a0);
      // Copy the matrix somwhere
      dest0_t a = boost::proto::child_c<0>(a0); 
      // Retrieve the Linsolve/Scale options
      opts_t opts = options(a0, N0()); 

      // solve in place
      if(nt2::issquare(a))
        {
          solve_lu_t f = solvers::full_lu_solve(a, boost::proto::child_c<0>(a1),'N',in_place_);
          solve(f, a1, N1());
        }
      else
        {
          solve_qr_t f = solvers::full_qr_solve(a, boost::proto::child_c<0>(a1),'N',in_place_);
          solve(f, a1, N1());
        }        
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // get 'B',  'S'("noperm") 
    //==========================================================================
    BOOST_FORCEINLINE
    opts_t options(A0 const &, boost::mpl::long_<2> const &) const
    {
      return opts_t(); 
    }

    BOOST_FORCEINLINE
    opts_t options(A0 const & a0, boost::mpl::long_<3> const &) const
    {
      return boost::proto::value(boost::proto::child_c<2>(a0)); 
    }
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    template < class S > 
    BOOST_FORCEINLINE
    void solve(S const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.x();
    }

    BOOST_FORCEINLINE
    void solve(solve_qr_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.x();
      boost::proto::child_c<1>(a1) = f.rank();
    }
    BOOST_FORCEINLINE
    void solve(solve_lu_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.x();
      boost::proto::child_c<1>(a1) = f.rcond();
    }
  };
} }

#endif
