//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_LU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_LU_HPP_INCLUDED

#include <nt2/linalg/functions/lu.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/trf.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - D = LU(A)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)
                            , ((node_ < A0, nt2::tag::lu_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , boost::mpl::long_<1>
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::table<nt2_la_int> ip;

      BOOST_AUTO_TPL( out, concrete(boost::proto::child_c<0>(a1)) );
      out = boost::proto::child_c<0>(a0);
      nt2_la_int lapack_info = nt2::trf(out,ip);

      NT2_WARNING ( lapack_info <= 0
                  , "LU factorization has been completed, but U is exactly "
                    "singular. Division by zero will occur if it is used to "
                    "solve a system of equations."
                  );

      boost::proto::child_c<0>(a1) = out;
    }
  };

  /// INTERNAL ONLY - [L,U,P*] = LU(A)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::lu_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void                                              result_type;
    typedef typename boost::proto::result_of
                                 ::child_c<A1&,0>::value_type c0_t;
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch
                                       ::meta::semantic_of<c0_t>::type
                       >::type                                tab0_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::table<nt2_la_int> ip;
      decomp(a0, a1, ip, N1());
    }

    /// INTERNAL ONLY - [L,U] = LU(A)
    BOOST_FORCEINLINE
    void decomp ( A0& a0, A1& a1, nt2::table<nt2_la_int>& ip
                , boost::mpl::long_<2> const&
                ) const
    {
      nt2_la_int info;

      if( nt2::issquare(boost::proto::child_c<0>(a0)) )
      {
        BOOST_AUTO_TPL( work, concrete(boost::proto::child_c<0>(a1)) );
        work = boost::proto::child_c<0>(a0);
        info = nt2::trf(work,ip);
        extract_lu(a1,work);
      }
      else
      {
        tab0_t work = boost::proto::child_c<0>(a0);
        info = nt2::trf(work,ip);
        extract_lu(a1,work);
      }

      check_success(info);
    }

    /// INTERNAL ONLY - [L,U,P] = LU(A)
    BOOST_FORCEINLINE
    void decomp ( A0& a0, A1& a1, nt2::table<nt2_la_int>& ip
                , boost::mpl::long_<3> const&
                ) const
    {
      decomp(a0,a1,ip,boost::mpl::long_<2>());
      extract_p(a1,ip);
    }

    /// INTERNAL ONLY - Helper for L/U extraction
    template<typename W>
    BOOST_FORCEINLINE void extract_lu(A1& a1, W& work) const
    {
      std::size_t d  = dim(work);
      boost::proto::child_c<1>(a1) = nt2::triu( work( _(1, d), _) );
      boost::proto::child_c<0>(a1) = nt2::tri1l( work(_, _(1, d) ) );
    }

    /// INTERNAL ONLY - Size of L/U
    template<typename W>
    BOOST_FORCEINLINE std::size_t dim(W const& work) const
    {
      return std::min(nt2::height(work),nt2::width(work));
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void extract_p(A1& a1, nt2::table<nt2_la_int>& ip) const
    {
      std::size_t d = nt2::numel(ip);
      boost::proto::child_c<2>(a1) = nt2::zeros(d);

      for(std::size_t i = 1; i<= d;++i)
        boost::proto::child_c<2>(a1)(i,ip(i)) = 1;
    }

    /// INTERNAL ONLY
    void check_success(nt2_la_int lapack_info) const
    {
      NT2_WARNING ( lapack_info <= 0
                  , "LU factorization has been completed, but U is exactly "
                    "singular. Division by zero will occur if it is used to "
                    "solve a system of equations."
                  );
    }
  };
} }

#endif
