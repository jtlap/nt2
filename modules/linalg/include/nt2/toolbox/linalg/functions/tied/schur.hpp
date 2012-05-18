//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SCHUR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SCHUR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/schur.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/schur.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of schur is called whenever a tie(a,p) = schur(...) is captured
  // before assign is resolved. As a tieable function, schur retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::schur_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::schur_, N0>))
                              ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  child0;
    typedef typename meta::strip<child0>::type                      dest_t;
    typedef typename meta::
            call< nt2::tag::
                  factorization::schur_(dest_t&,char,char,char,nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Retrieve the lapack schur relevant options options
      char sort = 'N';
      char jobvs = (N1::value == 1) ? 'N' : 'V'; 
      char sense =  'N'; 
         
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);

      // Factorize in place
      fact_t f = factorization::schur(boost::proto::child_c<0>(a1),jobvs,sort,sense,in_place_);
      decomp(f, a1, N1()); 

    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    // If nargout is 2, fill the status
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.t();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.z();
      boost::proto::child_c<1>(a1) = f.t();
    }
  };
} }

#endif
