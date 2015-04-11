//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_CPLXPAIR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_CPLXPAIR_HPP_INCLUDED

#include <nt2/linalg/functions/cplxpair.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/csort.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/linesstride.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/hundred.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( cplxpair_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> > )
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (const A0& a0)
                          , a0
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::cplxpair_, N,nt2::container::domain> ))
                            )
  {
    typedef typename A0::value_type                                      type_t;
    typedef typename container::table<type_t>                             tab_t;
    typedef typename meta::as_real<type_t>::type                        rtype_t;
    typedef typename meta::is_complex<type_t>::type                   is_cplx_t;
    typedef A0&                                                     result_type;
    BOOST_FORCEINLINE
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(out.extent());
      rtype_t tol;
      std::size_t dim;
      getparameters(in, dim, tol, N());
      compute(boost::proto::child_c<0>(in), dim, tol, out, is_cplx_t());
      return out;
    }
  private:
    BOOST_FORCEINLINE void
    getparameters( A1 &in, std::size_t &dim, rtype_t& tol
                 , const boost::mpl::long_<1> &) const
    {
      tol = Hundred<rtype_t>()*Eps<rtype_t>();
      dim = firstnonsingleton(boost::proto::child_c<0>(in));
    }

    BOOST_FORCEINLINE void
    getparameters( A1 &in, std::size_t &dim, rtype_t& tol
                 , const boost::mpl::long_<3> &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::value_type child1;
      typedef typename boost::dispatch::meta::semantic_of<child1>::type      st_t;
      typedef typename meta::is_integral<st_t>::type                     is_int_t;
      getdim(in, dim,is_int_t(), N());
      gettol(in, tol, is_int_t(), N());
    }

    BOOST_FORCEINLINE void
    getparameters( A1 &in, std::size_t &dim, rtype_t& tol
                 , const boost::mpl::long_<2> &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::value_type child1;
      typedef typename boost::dispatch::meta::semantic_of<child1>::type      st_t;
      typedef typename meta::is_integral<st_t>::type                     is_int_t;
      getdim(in, dim, is_int_t(), N());
      gettol(in, tol, is_int_t(), N());
    }

    BOOST_FORCEINLINE void
    gettol( A1 &, rtype_t& tol
          , const boost::mpl::true_ &
          , const boost::mpl::long_<2>) const
    {
      tol =  Hundred<rtype_t>()*Eps<rtype_t>();;
    }

    BOOST_FORCEINLINE void
    gettol( A1 &in, rtype_t& tol
          , const boost::mpl::true_ &
          , const boost::mpl::long_<3>) const
    {
      tol =   boost::proto::value(boost::proto::child_c<2>(in));
    }
    template < long NN > // N = 2, 3
    BOOST_FORCEINLINE void
    gettol( A1 &in, rtype_t& tol
          , const boost::mpl::false_ &
          , const boost::mpl::long_<NN>) const
    {
      tol =  boost::proto::value(boost::proto::child_c<1>(in));
    }

    BOOST_FORCEINLINE void
    getdim( A1 &in, std::size_t &dim
          , const boost::mpl::false_ &
          , const boost::mpl::long_<2>) const
    {
      dim =firstnonsingleton(boost::proto::child_c<0>(in));
    }

    BOOST_FORCEINLINE void
    getdim( A1 &in, std::size_t &dim
          , const boost::mpl::false_ &
          , const boost::mpl::long_<3>) const
    {
      dim =firstnonsingleton(boost::proto::child_c<2>(in));
    }

    template < long NN > // 2 and 3
    BOOST_FORCEINLINE void
    getdim( A1 &in, std::size_t &dim
          , const boost::mpl::true_ &
          , const boost::mpl::long_<NN>) const
    {
      dim =  boost::proto::value(boost::proto::child_c<1>(in));
    }

    template <class A>
    BOOST_FORCEINLINE void
    compute( A & x, std::size_t dim, rtype_t tol
           , A0& out, const boost::mpl::true_&) const
    {
      auto isreal =  [tol](type_t a)->bool
        {
          return nt2::abs(imag(a)) <= tol* nt2::abs(real(a));
        };
      auto cmp =  [isreal](type_t a,  type_t b)->bool
        {
          if (isreal(a) && isreal(b))
          {
            return (real(a) < real(b));
          }
          else if  (!isreal(a) && isreal(b))
          {
            return true;
          }
          else if  (isreal(a) && !isreal(b))
          {
            return false;
          }
          else if  (!isreal(a) && !isreal(b))
          {
            if (real(a) != real(b))
              return real(a) < real(b);
            else
              return imag(a) < imag(b);
          }
          else
            return true;
        };
      out =  csort(x, cmp, dim);
      reorderpairs(out, dim);
    }
    template <class A>
    BOOST_FORCEINLINE void
    compute( A & a, std::size_t dim, rtype_t
           , A0& out, const boost::mpl::false_&) const
    {
       out = csort(a, dim);
    }

    template < class RES> static BOOST_FORCEINLINE
    void reorderpairs( RES & res, std::size_t dim)
    {
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      rtype_t tol = rtype_t(100)*Eps<rtype_t>();
      auto isreal =  [tol](type_t a)->bool{ return nt2::abs(imag(a)) <= tol* nt2::abs(real(a));};
      size_t nbslice =  nt2::numel(res)/h;
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        auto pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        std::size_t i0 = 1;
        while (i0 <= h && !isreal(tmp(i0)))
        {
          std::size_t beg = i0-1;
          std::size_t nb = 0;
          type_t tmpplus  = tocomplex(real(tmp(i0)), nt2::abs(imag(tmp(i0))));
          type_t tmpminus = tocomplex(real(tmp(i0)), -nt2::abs(imag(tmp(i0))));
          while (eq(real(tmp(i0)), real(tmpplus))&&eq(nt2::abs(imag(tmp(i0))), imag(tmpplus)))
          {
            ++nb;
            ++i0;
            if (i0 > h) break;
          }
          BOOST_ASSERT_MSG (is_even(nb), "complex values are not properly paired");
          if (nb > 2)
          {
            for(std::size_t j=1; j <= nb/2 ; j++)
            {
              tmp(beg+2*j-1) = tmpminus;
              tmp(beg+2*j)   = tmpplus;
            }
          }
        }
        res(p+range) = tmp;
        ++p;
      }
    }
  };
} }

#endif
