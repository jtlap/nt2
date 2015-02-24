//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_LSQNONNEG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_LSQNONNEG_HPP_INCLUDED

#include <nt2/linalg/functions/lsqnonneg.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/falses.hpp>
#include <nt2/include/functions/globalany.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/mldivide.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/posmax.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/trues.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/table.hpp>


namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = lsqnonneg(...) at assign time and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( lsqnonneg_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::lsqnonneg_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef typename container::table<value_t>                          table_t;
    typedef typename meta::as_logical<value_t>::type                     bool_t;
    typedef typename container::table<bool_t>                          btable_t;
    typedef nt2::memory::container<tag::table_, value_t, nt2::_2D>   o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, c, boost::proto::child_c<0>(a0));
      NT2_AS_TERMINAL_IN(o_semantic, d, boost::proto::child_c<1>(a0));
      value_t tol = gettol(a0, c, N0());
      compute(c, d, tol, a1, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class C > BOOST_FORCEINLINE
    value_t gettol(A0 const &, C const & c, boost::mpl::long_<2> const &) const
    {
      return Ten<value_t>()*Eps<value_t>()*mnorm1(c)*length(c);
    }

    template < class C > BOOST_FORCEINLINE
    value_t gettol(A0 const & a0, C const &, boost::mpl::long_<3> const &) const
    {
      return boost::proto::value(boost::proto::child_c<3>(a0));
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1&,  R const &, std::size_t, std::size_t
                   , W const &, boost::mpl::long_<1> const &) const
    {
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t, std::size_t
                   , W const &, boost::mpl::long_<2> const &) const
    {
      value_t resnorm = mtimes(trans(resid), resid);
      boost::proto::child_c<1>(a1) = resnorm;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
      void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                     , W const & w, boost::mpl::long_<3> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w,  boost::mpl::long_<2>());
      boost::proto::child_c<2>(a1) = resid;
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<4> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w,  boost::mpl::long_<3>());
      boost::proto::child_c<3>(a1) =  exitflag;
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<5> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w, boost::mpl::long_<4>());
      boost::proto::child_c<4>(a1) =  outeriter;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<6> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w, boost::mpl::long_<5>());
      boost::proto::child_c<5>(a1) =  w;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class C, class D> BOOST_FORCEINLINE
    void compute(C const & c, D const & d, value_t tol, A1& a1, N1 const & ) const
    {
      std::size_t n = size(c,2);
      //  initialize vector of n zeros and infs (to be used later)
      table_t nzeros = zeros(n,1,meta::as_<value_t>());
      table_t wz = nzeros;
      // initialize set of non-active columns to null
      btable_t p = falses(n,1,meta::as_<bool_t>());
      //  initialize set of active columns to all and the initial point to zeros
      btable_t z = trues(n,1,meta::as_<bool_t>());
      table_t x = nzeros;

      table_t resid = d - mtimes(c, x);
      table_t w = mtimes(trans(c), resid);

      //  set up iteration criterion
      std::size_t outeriter = 0;
      std::size_t iter = 0;
      const std::size_t itmax = 3*n;
      //  outer loop to put variables into set to hold positive coefficients
      while (globalany(z) && globalany(w(z) > tol))
      {
        ++outeriter;
        //  reset intermediate solution zz
        table_t zz = nzeros;
        //  create wz, a lagrange multiplier vector of variables in the zero set.
        //  wz must have the same size as w to preserve the correct indices, so
        //  set multipliers to -inf for variables outside of the zero set.
        wz(p) = Minf<value_t>();
        wz(z) = w(z);
        //  find variable with largest lagrange multiplier
        std::size_t t = globalfind(globalmax(wz) == wz);
        //   move variable t from zero set to positive set
        p(t) = True<bool_t>();
        z(t) = False<bool_t>();
        //  compute intermediate solution using only variables in positive set
        zz(p) = mldivide(c(_,p), d);
        // inner loop to remove elements from the positive set which no longer belong
        while (globalany(is_lez(zz(p))))
        {
          ++iter;
          if (iter > itmax)
          {
            assign_swap(boost::proto::child_c<0>(a1), zz);
            setresults(a1, resid, 0, outeriter, w, N1());
            return;
          }
          //  find indices where intermediate solution zz is approximately negative
          btable_t q = logical_and(is_lez(zz), p);
          //    choose new x subject to keeping new x nonnegative
          value_t alpha = nt2::min(x(q)/(x(q) - zz(q)));
          x  += alpha*(zz - x);
          //  reset z and p given intermediate values of x
          z = logical_or(logical_and((nt2::abs(x) < tol), p), z);
          p = logical_not(z);
          zz = nzeros;          // reset zz
          zz(p) = mldivide(c(_,p), d);     // re-solve for zz
        }
        x =  zz;
        resid = d - mtimes(c, x);
        w = mtimes(trans(c), resid);
      }
      assign_swap(boost::proto::child_c<0>(a1), x);
      setresults(a1, resid, 1, outeriter, w, N1());
    }

  };
} }

#endif
