//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_BALANCE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_BALANCE_HPP_INCLUDED

#include <nt2/linalg/functions/balance.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/gebak.hpp>
#include <nt2/include/functions/gebal.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/linalg/details/utility/warning.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //BALANCE Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::balance_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::balance_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };


  //============================================================================
  //BALANCE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::balance_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::balance_
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
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                  type_t;
    typedef typename meta::as_real<type_t>::type                        rtype_t;
    typedef typename meta::as_integer<rtype_t>::type                    itype_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }
  private:
    //==========================================================================
    /// INTERNAL ONLY - B = BALANCE(A)
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval2_1(a0, a1, nt2::both_);
    }

    /// INTERNAL ONLY - B = BALANCE(A, perm_/no_perm_/both_/none_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval2_1(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    //perm_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_1 ( A0& a0, A1& a1
                   , nt2::policy<ext::perm_>
                   ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a1)),
                       "matrix to balance must be square");
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(boost::proto::child_c<0>(a1));
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      lapack_warn(gebal(boost::proto::value(boost::proto::child_c<0>(a1))
                       , boost::proto::value(scale)
                       , ilo, ihi, 'P'));
    }

    //no_perm_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
      void eval2_1 ( A0& a0, A1& a1
                   , nt2::policy<ext::no_perm_>
                   ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a1)),
                       "matrix to balance must be square");
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(boost::proto::child_c<0>(a1));
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      lapack_warn(gebal( boost::proto::value(boost::proto::child_c<0>(a1))
                       , boost::proto::value(scale)
                       , ilo, ihi, 'S'));
    }

    //both_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
      void eval2_1 ( A0& a0, A1& a1
                   , nt2::policy<ext::both_>
                   ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a1)),
                       "matrix to balance must be square");
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(boost::proto::child_c<0>(a1));
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      lapack_warn(gebal(boost::proto::value(boost::proto::child_c<0>(a1))
                       , boost::proto::value(scale)
                       , ilo, ihi, 'B'));
    }

    // none_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
      void eval2_1 ( A0& a0, A1& a1
                   , nt2::policy<ext::none_>
                   ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a1)),
                       "matrix to balance must be square");
    }

    //==========================================================================
    /// INTERNAL ONLY - [T, B] = BALANCE(A)
    // finds a similarity transformation T such
    // that B = T\A*T has, as nearly as possible, approximately equal
    // row and column norms and balanced matrix B
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2(a0, a1, 'B');
    }

    //==========================================================================
    /// INTERNAL ONLY - [T, B] = BALANCE(A, perm_/noperm_/both_/none_)
    // finds a similarity transformation T such
    // that B = T\A*T has, as nearly as possible, approximately equal
    // row and column norms and balanced matrix B
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    // none_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , char job
                 ) const
    {
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a0);
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<1>(a1)),
                       "matrix to balance must be square");
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(boost::proto::child_c<1>(a1));
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      lapack_warn(gebal(boost::proto::value(boost::proto::child_c<1>(a1))
                       , boost::proto::value(scale)
                       , ilo, ihi, job));
      boost::proto::child_c<0>(a1) = nt2::eye(n, n, meta::as_<type_t>());
      nt2_la_int ldt = boost::proto::child_c<1>(a1).leading_size();
      lapack_warn(gebak(boost::proto::value(boost::proto::child_c<0>(a1)),
                        boost::proto::value(scale), ilo, ihi,  job, 'R'));
    }

    // both_
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::both_>
                   ) const
    {
      eval2_2(a0, a1, 'B');
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::perm_>
                   ) const
    {
      eval2_2(a0, a1, 'P');
    }
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::no_perm_>
                   ) const
    {
      eval2_2(a0, a1, 'S');
    }
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::none_>
                   ) const
    {
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a0);
      nt2_la_int n = height(boost::proto::child_c<1>(a1));
      boost::proto::child_c<0>(a1) = nt2::eye(n, n, meta::as_<type_t>());
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<1>(a1)),
                       "matrix to balance must be square");
    }

    //==========================================================================
    /// INTERNAL ONLY - [S, P, B] = BALANCE(A)
    // finds a similarity transformation T such
    // that B = T\A*T has, as nearly as possible, approximately equal
    // row and column norms and balanced matrix B
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_2(a0, a1, 'B');
    }

    //==========================================================================
    /// INTERNAL ONLY - [S, P, B] = BALANCE(A, perm_/noperm_/both_/none_)
    // finds a similarity transformation T such
    // that B = T\A*T has, as nearly as possible, approximately equal
    // row and column norms and balanced matrix B
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1, char job) const
    {
       BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a0)),
                        "matrix to balance must be square");
       boost::proto::child_c<2>(a1) = boost::proto::child_c<0>(a0);
       nt2_la_int ilo, ihi;
       nt2_la_int n = height(boost::proto::child_c<2>(a1));
       nt2::container::table<rtype_t> scale(of_size(n, 1));
       lapack_warn(gebal(boost::proto::value(boost::proto::child_c<2>(a1))
                        , boost::proto::value(scale)
                        , ilo, ihi, job));
       nt2::container::table<type_t> t =  nt2::eye(n, n, meta::as_<type_t>());
       lapack_warn(gebak( boost::proto::value(t)
                        , boost::proto::value(scale)
                        , ilo, ihi,  job, 'R'));
       extract_ips(a1, t);
    }

    /// INTERNAL ONLY
    template < class T>
    BOOST_FORCEINLINE
    void  extract_ips(A1& a1, const T& t) const
    {
      size_t n =  height(t);
      boost::proto::child_c<1>(a1).resize(of_size(n, 1));
      boost::proto::child_c<0>(a1).resize(of_size(n, 1));
      for(size_t i=1; i <= n; ++i)
      {
        for(size_t j=1; j <= n; ++j)
        {
          if(is_nez(t(i, j)))
          {
            boost::proto::child_c<1>(a1)(i) = j;
            boost::proto::child_c<0>(a1)(i) = real(t(i, j));
            break;
          }
        }
      }
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::both_>
                   ) const
    {
      eval3_2(a0, a1, 'B');
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::perm_>
                   ) const
    {
      eval3_2(a0, a1, 'P');
    }
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::no_perm_>
                   ) const
    {
      eval3_2(a0, a1, 'S');
    }
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                   , nt2::policy<ext::none_>
                   ) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a0)),
                       "matrix to balance must be square");
      boost::proto::child_c<2>(a1) = boost::proto::child_c<0>(a0);
      itype_t n = height(boost::proto::child_c<0>(a0));
      boost::proto::child_c<0>(a1) = nt2::ones(n, 1, meta::as_<type_t>());
      boost::proto::child_c<1>(a1) = nt2::colvect(nt2::_(itype_t(1), n));
    }


  };
} }

#endif
