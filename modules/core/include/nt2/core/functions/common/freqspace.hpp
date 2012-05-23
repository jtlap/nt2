/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED

#include <nt2/include/functions/freqspace.hpp>
#include <nt2/include/functions/freqspace1.hpp>
#include <nt2/include/functions/freqspace2.hpp>
#include <boost/mpl/bool.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of freqspace is called whenever a tie(...) = freqspace(...) is captured
  // before assign is resolved. As a tieable function, freqspace retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::freqspace_, N0>))
                                ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<child0>::type
                       >::type                                            in0_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      int n, m;
      getmn(a0, m, n, N0(), N1() );
      std::cout << "m " << m << " n " << n << std::endl;
    }

    private:
    BOOST_FORCEINLINE  //[f]       = freqspace(n)
    void getmn(A0 const &a0, int &m,  int& n,
               boost::mpl::long_<3> const &,//number of inputs
               boost::mpl::long_<1> const &//number of outputs
               ) const
    {
      m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
      n = 0;
    }

    BOOST_FORCEINLINE  //[f1, f2]       = freqspace(n)
      void getmn(A0 const &a0, int &m,  int& n,
                 boost::mpl::long_<3> const &,    //number of inputs
                 boost::mpl::long_<2> const &
                 ) const//number of outputs
    {
      m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
      n = m;
    }

    BOOST_FORCEINLINE //[f]       = freqspace(n, whole_)
      void getmn( A0 const &a0, int &m,  int& n
                , boost::mpl::long_<4> const &  //number of inputs
                , boost::mpl::long_<1> const &  //number of outputs
                ) const
    {
    }

    BOOST_FORCEINLINE //[f,g]       = freqspace(n, whole_)
      void getmn( A0 const &a0, int &m,  int& n
                , boost::mpl::long_<4> const &  //number of inputs
                , boost::mpl::long_<2> const &  //number of outputs
                ) const
    {
    }

    ////template < class Dummy >
      ////BOOST_FORCEINLINE // [f1, f2]  = freqspace([m, n])
      ////void getmn(A0 const &a0, int &m,  int& n,
                 ////boost::mpl::long_<2> const &,//number of outputs
                 ////boost::mpl::long_<> const &,//number of inputs
                 ////Dummy()) const
    ////{
      ////m = int(boost::proto::value(boost::proto::child_c<0>(a0)));
      ////m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
    ////}

    ////template < class Dummy >
      ////BOOST_FORCEINLINE // [f1, f2]  = freqspace([m, n], meshgrid_)
      ////void getmn(A0 const &a0, int &m,  int& n,
                 ////boost::mpl::long_<2> const &,//number of outputs
                 ////boost::mpl::long_<2> const &,//number of inputs
                 ////Dummy()) const
    ////{
      ////m = int(boost::proto::value(boost::proto::child_c<0>(a0)));
      ////m = -1;
    ////}
  };
} }

#endif
