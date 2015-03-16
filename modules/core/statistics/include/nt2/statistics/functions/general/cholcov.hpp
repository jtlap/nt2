//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_TIED_CHOLCOV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_TIED_CHOLCOV_HPP_INCLUDED

#include <nt2/statistics/functions/cholcov.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/ishermitian.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/of_size.hpp>
//#include <nt2/include/functions/mkhermitian.hpp>
//#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/table.hpp>
namespace nt2 { namespace ext
{
  //============================================================================
  //CHOLCOV Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cholcov_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      BOOST_ASSERT_MSG(real(a0) >= 0, "invalid covariance matrix");
      return sign(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cholcov_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return sign(a0);
    }
  };


  //============================================================================
  //CHOLCOV
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cholcov_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::cholcov_
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
    typedef container::table<type_t>                                    table_t;
    typedef container::table<rtype_t>                                  rtable_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>   r_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, sigma, boost::proto::child_c<0>(a0));
      rtype_t tol = Ten<rtype_t>()*eps(nt2::max(nt2::abs(diag_of(sigma))));
      BOOST_ASSERT_MSG((ishermitian(sigma, tol)), "input is not hermitian");
      int p;
      table_t t;
      tie(t, p) = chol(sigma);
      compute(a0, a1, sigma, t, p, N0(), N1());
    }
  private:
    template< class S> BOOST_FORCEINLINE
    void compute(A0&, A1&a1, S& s, table_t& t,  int& p, const boost::mpl::long_<1>&,  const N1&) const
    {
      factor(a1, s, t, p, nt2::semidefinite_, N1());
    }
    template< class S> BOOST_FORCEINLINE
    void compute(A0&a0, A1&a1, S& s, table_t& t,  int& p, const boost::mpl::long_<2>&,  const N1&) const
    {
      factor(a1, s, t, p, boost::proto::value(boost::proto::child_c<1>(a0)), N1());
    }

    template< class S> BOOST_FORCEINLINE
    void factor(A1&a1, S& s, table_t& t,  int& p, const policy<ext::semidefinite_> &,  const N1&) const
    {
      //   Can get factors of the form Sigma==T'*T using the eigenvalue
      //   decomposition of a symmetric matrix, so long as the matrix
      //   is positive semi-definite.
      rtable_t d;
      table_t u;
      NT2_DISPLAY(average(s, ctrans(s)));
// //      tie(d, u)= symeig(mkhermitian(sigma), nt2::vector_);
      tie(d, u)= symeig(average(s, ctrans(s)), nt2::vector_);
      NT2_DISPLAY(u);
      NT2_DISPLAY(d);
      rtype_t tol = eps(globalmax(d)) * rtype_t(length(d));
      p = globalsum(if_one_else_zero(lt(d, -tol))); // number of negative eigenvalues
      if (p==0)
      {
        auto tt = gt(nt2::abs(d), tol);
        t = ctrans(u(_,tt)*expand_to(sqrt(rowvect(d(tt))), u(_, tt).extent()));
      }
      else
      {
          t.resize(of_size(0, 1));
      }
      setresults(a1, t, p, N1());
    }
    template< class S> BOOST_FORCEINLINE
    void factor(A1&a1, S&, table_t& t,  int& p, const policy<ext::definite_> &,  const N1&) const
    {
      setresults(a1, t, p, N1());
    }
    BOOST_FORCEINLINE
      void setresults(A1&a1, table_t& t,  int&, const boost::mpl::long_<1>&) const
    {
      assign_swap(boost::proto::child_c<0>(a1), t);
    }
    BOOST_FORCEINLINE
      void setresults(A1&a1, table_t& t,  int& p, const boost::mpl::long_<2>&) const
    {
      if (p) t.resize(of_size(0, 1));
      assign_swap(boost::proto::child_c<0>(a1), t);
      boost::proto::child_c<1>(a1) = p;
    }

  };
} }

#endif
