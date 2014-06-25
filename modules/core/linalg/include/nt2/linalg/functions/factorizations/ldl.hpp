//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LDL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LDL_HPP_INCLUDED

#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/hstrf.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/linalg/details/utility/lapack_assert.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //[Q,R] = LDL(A)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ldl_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::ldl_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type     child0;
    typedef typename child0::value_type                                      type_t;
    typedef typename meta::as_real<type_t>::type                            rtype_t;
    typedef typename meta::as_integer<rtype_t>::type                        itype_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>        o_semantic;
    typedef nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D>    i_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

  private:
    /// INTERNAL ONLY - [dm, ipiv] = ldl(a, lapack_/upper_/lower_)
    /// this is the direct return of LAPACK
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // 2 input
              , boost::mpl::long_<2> const& // 2 output
              ) const
    {
      eval2_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }



    ///////////////////////////////////////////////////////////////////////////////
    // evali_j bunch
    ///////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 2o lapack_
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , const nt2::policy<ext::lapack_>&
                   ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, dm,   boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (i_semantic, ipiv, boost::proto::child_c<1>(a1));
      ipiv.resize(of_size(height(dm), 1));
      lapack_assert(nt2::hstrf( boost::proto::value(dm)
                              , boost::proto::value(ipiv)
                              , 'L'));

      boost::proto::child_c<0>(a1) = dm;
      boost::proto::child_c<1>(a1) = ipiv;
    }
  };
} }

#endif
