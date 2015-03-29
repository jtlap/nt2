//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_SIGNM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_SIGNM_HPP_INCLUDED

#include <nt2/linalg/functions/signm.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2
{
  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( signm_, tag::cpu_
                              , (A0)
                              , (scalar_< unspecified_<A0> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(1)
      {
        return sign(real(a0));
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( signm_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< unspecified_<A0> >)
                                (scalar_< floating_<A1> >)
                              )
    {
      typedef A0 result_type;
      BOOST_FORCEINLINE result_type operator()(A0& a0, const A1&) const
      {
        return sign(real(a0));
      }
    };

  BOOST_DISPATCH_IMPLEMENT  ( signm_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::signm_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
    {
      typedef void                                                    result_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
      typedef typename child0::value_type                                  type_t;
      typedef typename meta::as_real<type_t>::type                        rtype_t;
      typedef typename meta::as_complex<rtype_t>::type                    ctype_t;
      typedef table<ctype_t>                                               ctab_t;
      typedef table<type_t>                                                 tab_t;
      typedef typename meta::is_complex<type_t>::type                    iscplx_t;
      typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>    o_semantic;

      BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, a, boost::proto::child_c<0>(a0));
        BOOST_ASSERT_MSG(issquare(a), "input is not square");
        ctab_t s, u, t;
        nt2::tie(u, t) = schur(a, nt2::cmplx_);
        rtype_t epsi;
        gettolerance(a0, epsi, N0());
        compute_s(s, u, t, epsi);
        choose_type(a1, s, iscplx_t());
        compute_n(a1, a, boost::proto::child_c<0>(a1), N1());
      }

      template < class S>
      BOOST_FORCEINLINE static void choose_type(A1& a1, S &s, const boost::mpl::false_&)
      {
        boost::proto::child_c<0>(a1) =  real(s);
      }
      template < class S>
      BOOST_FORCEINLINE static void choose_type(A1& a1, S &s, const boost::mpl::true_&)
      {
        boost::proto::child_c<0>(a1) = s;
      }

      template < class A, class S>
      BOOST_FORCEINLINE static void compute_n(A1& a1, const A& a, const S& s
                                                , const boost::mpl::long_<2>&)
      {
        boost::proto::child_c<1>(a1) = mtimes(s, a);
      }

      template < class A, class S>
      BOOST_FORCEINLINE static void compute_n(A1&, const A&, const S&
                                                , const boost::mpl::long_<1>)
      {
        // do nothing
      }
      template < class S, class U, class T >
      BOOST_FORCEINLINE static void compute_s(S& s, const U& u, const T& t, rtype_t epsi)
      {
        typedef typename T::value_type t_t;
        std::size_t n = height(t);
        s = from_diag( sign( diag_of(real(t)) ) );
        if (!isdiagonal(t, (n+1)*epsi))
        {
          for(std::size_t p = 1; p <= n-1; ++p)
          {
            for(std::size_t i = 1; i <= n-p; ++i)
            {
              std::size_t j = i+p;
              t_t d = t(j,j) - t(i,i);
              if (s(i,i) != -s(j,j)) // solve via s^2 = i if we can.
              {
                // get s(i,j) from s^2 = i.
                auto k = _(i+1, j-1);
                s(i,j) = -globalsum(s(i,k)(_)*s(k,j)) / (s(i,i)+s(j,j));
              }
              else
              {
                // get s(i,j) from s*t = t*s.
                t_t ss = t(i,j)*(s(j,j)-s(i,i));
                if (p > 1)
                {
                  auto k = _(i+1, j-1);
                  ss += globalsum(t(i,k)(_)*s(k,j)) - globalsum(s(i,k)(_)*t(k,j));
                }
                s(i,j) = ss/d;
              }
            }
          }
        }
        s = mtimes(mtimes(u, s), ctrans(u));
      }

      BOOST_FORCEINLINE static void gettolerance(const A0&, rtype_t & epsi
                                                  , const boost::mpl::long_<1>&)
      {
        epsi = Ten<rtype_t>()*Eps<rtype_t>();
      }

      BOOST_FORCEINLINE static void gettolerance(const A0& a0, rtype_t & epsi
                                                  , const boost::mpl::long_<2>&)
      {
        epsi = boost::proto::value(boost::proto::child_c<1>(a0));
      }


    };
  }
}

#endif
