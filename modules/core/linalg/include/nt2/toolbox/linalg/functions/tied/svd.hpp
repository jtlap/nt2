//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SVD_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SVD_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/svd.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/svd.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of svd is called whenever a tie(u, w, v) = svd(a, ...) is captured
  // before assign is resolved. As a tieable function, svd retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::svd_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                               result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type  child0;
    typedef typename meta::
            call< nt2::tag::
      factorization::svd_(child0,char,char,nt2::details::in_place_)
      >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      char jobu, jobvt, econ;
      // Retrieve the economy options
      econ = options(a0, N0());
      // translate to lapack job
      if (N1::value == 1)
      {
        jobu = jobvt = 'N';
      }
      else if ( econ == 'N')
      {
        jobu = jobvt = 'A';
      }
      else if (econ == 'L')
      {
        jobu = 'S'; jobvt = 'A';
      }
      else
      {
        jobu = 'S'; jobvt = 'S';
      }
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);

      // Factorize in place
      fact_t f = factorization::svd(boost::proto::child_c<0>(a1),jobu,jobvt,in_place_);
      decomp(f, a1, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    // Extract a 'U' or a 'L' from lower_/upper_ or mpl::void_
    //==========================================================================
    BOOST_FORCEINLINE char options(A0 const&, boost::mpl::long_<1> const&) const
    {
      return 'A';
    }

    BOOST_FORCEINLINE char options(A0 const& in, boost::mpl::long_<2> const&) const
    {
      char econ = boost::proto::value(boost::proto::child_c<1>(in));
      if (econ != 'R' && econ !=  'L') econ = 'A';
      return econ;
    }

    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
      void decomp(fact_t & f, A1 & a1, boost::mpl::long_<1> const&) const
    {
      boost::proto::child_c<0>(a1) = f.singular();
    }

    BOOST_FORCEINLINE
      void decomp(fact_t & f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.u();
      boost::proto::child_c<1>(a1) = f.w();
    }

    BOOST_FORCEINLINE
      void decomp(fact_t & f, A1 & a1, boost::mpl::long_<3> const&) const
    {
      boost::proto::child_c<0>(a1) = f.u();
      boost::proto::child_c<1>(a1) = f.w();
      boost::proto::child_c<2>(a1) = f.v();
    }
  };
} }

#endif
