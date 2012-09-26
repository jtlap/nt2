//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_BALANCE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_BALANCE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/balance.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/balance.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <cstring>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of balance is called whenever a tie(...) = balance(...) is captured
  // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::balance_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::balance_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::
            call< nt2::tag::
                  factorization::balance_(child0,char, nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      // Retrieve the Balance/Scale options
      char job =  choice(a0, N0()); 

      // Factorize in place
      fact_t f = factorization::balance(boost::proto::child_c<0>(a1),job,in_place_);
      decomp(f, a1, N1());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // get 'B',  'S'("noperm") 
    //==========================================================================
    BOOST_FORCEINLINE
    char choice(A0 const &, boost::mpl::long_<1> const &) const
    {
      return 'B'; 
    }

    BOOST_FORCEINLINE
    char choice(A0 const & a0, boost::mpl::long_<2> const &) const
    {
      //       bool opt = strcmp(boost::proto::value(boost::proto::child_c<1>(a0)), "noperm") == 0; 
      //       BOOST_ASSERT_MSG( opt, "Error using balance: Second argument must be \"noperm\".");
      //       return opt ? 'S':'B';
      return boost::proto::value(boost::proto::child_c<1>(a0)); 
    }
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.balanced();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.t();
      boost::proto::child_c<1>(a1) = f.balanced();
    }
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<3> const&) const
    {
      boost::proto::child_c<0>(a1) = f.scale();
      boost::proto::child_c<1>(a1) = f.ipiv(); 
      boost::proto::child_c<2>(a1) = f.balanced();
    }
  };
} }

#endif
