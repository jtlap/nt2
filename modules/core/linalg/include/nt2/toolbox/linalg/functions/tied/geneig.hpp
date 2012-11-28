//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_GENEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_GENEIG_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/geneig.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/geneig.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of geneig is called whenever a tie(a,p) = geneig(...) is captured
  // before assign is resolved. As a tieable function, geneig retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::geneig_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type  child1;
    typedef typename meta::
            call< nt2::tag::
                  factorization::geneig_(child0,child1,char,char,char, nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Retrieve the up/lo options
      char jobvsl = 'N';
      char jobvsr = (N1::value == 1) ? 'N' : 'V';
      char uplo = 'U';
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);

      // Factorize in place
      fact_t f = factorization::geneig(boost::proto::child_c<0>(a1),jobvsl,jobvsr,uplo,in_place_);
      decomp(f, a1, N1());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.eigen();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.v();
      boost::proto::child_c<1>(a1) = f.w();
    }
  };
} }

#endif
