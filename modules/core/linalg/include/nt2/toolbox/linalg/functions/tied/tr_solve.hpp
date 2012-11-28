//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_TR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_TR_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/tr_solve.hpp>
#include <nt2/toolbox/linalg/functions/solvers/tr_solve.hpp>
#include <nt2/toolbox/linalg/functions/solvers/options.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of tr_solve is called whenever a tie(...) = tr_solve(...) is captured
  // before assign is resolved. As a tieable function, tr_solve retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tr_solve_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::tr_solve_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename solvers::options                                    opts_t;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child1;

    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<child0>::type
                       >::type                                          dest0_t;
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<child1>::type
                       >::type                                          dest1_t;

    typedef typename meta::
            call< nt2::tag::
                 solvers::tr_solve_ ( dest0_t&, dest1_t&, char, char, char
                                       , nt2::details::in_place_
                                       )
                >::type                                                 solve_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy equation rhs in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<1>(a0);
      char uplo, trans, udiag;
      // Retrieve the options
      options(a0, N0(), uplo, trans, udiag);

      // Copy the matrix somewhere
      dest0_t a = boost::proto::child_c<0>(a0);
      // Copy the rhs somewhere
      dest1_t b = boost::proto::child_c<1>(a0);

      // solve in place
      solve_t
        f = solvers::tr_solve(a, b,  uplo, trans, udiag, in_place_);

      solve(f, a1, N1());
    }

    private:
    BOOST_FORCEINLINE void options(A0 const&, boost::mpl::long_<2> const&,
                                   char &uplo,
                                   char &trans,
                                   char &udiag) const
    {
      uplo = 'L'; trans= 'N'; udiag= 'N';
    }
    BOOST_FORCEINLINE void options(A0 const&in, boost::mpl::long_<3> const&,
                                   char &uplo,
                                   char &trans,
                                   char &udiag) const
    {
      uplo = boost::proto::value(boost::proto::child_c<2>(in));
      trans= 'N'; udiag= 'N';
    }
    BOOST_FORCEINLINE void options(A0 const&in, boost::mpl::long_<4> const&,
                                   char &uplo,
                                   char &trans,
                                   char &udiag) const
    {
      uplo = boost::proto::value(boost::proto::child_c<2>(in));
      trans = boost::proto::value(boost::proto::child_c<3>(in));
      udiag= 'N';
    }
    BOOST_FORCEINLINE void options(A0 const&in, boost::mpl::long_<5> const&,
                                   char &uplo,
                                   char &trans,
                                   char &udiag) const
    {
      uplo = boost::proto::value(boost::proto::child_c<2>(in));
      trans = boost::proto::value(boost::proto::child_c<3>(in));
      udiag = boost::proto::value(boost::proto::child_c<4>(in));
    }

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
      boost::proto::child_c<1>(a1) = f.status();
    }

  };
} }

#endif
