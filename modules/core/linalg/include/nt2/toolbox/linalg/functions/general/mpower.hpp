/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_MPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_MPOWER_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/mpower.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/modf.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/power.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/sqrtm.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mpower_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::mpower_, N0>))
                                ((node_<A1, nt2::tag::tie_ , N1>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1& a1 ) const
    {
      const In0& a  = boost::proto::child_c<0>(a0);
      const In1& b  = boost::proto::child_c<1>(a0);
      const Out0& r  = boost::proto::child_c<0>(a1);
      bool s0 =  nt2::isscalar(a);
      bool s1 =  nt2::isscalar(b);
      if (s0 && s1)
        {
          value_type aa = a,  bb = b;
          doit0(aa, bb, r);

        }
      else if(s0)
        {
          value_type aa = a;
            doit1(aa, b, r);
        }
      else if(s1)
        {
          value_type bb = b;
          doit2(a, bb, r);
        }
    }
  private:
    BOOST_FORCEINLINE static void doit0(const value_type& a, value_type& b, Out0& r)
    {
      r =  nt2::pow(a, b);
    }
    template < class T >
    BOOST_FORCEINLINE static void doit1(const value_type& a, T& b, Out0& r)
    {
      r.resize(extent(b));
      r =  nt2::expm(nt2::log(a)*b);
    }
    template < class T >
    BOOST_FORCEINLINE static void doit2(const T& a, value_type& b, Out0& r)
    {
      r.resize(extent(a));
      typedef typename A0::index_type       index_type;
      typedef table<value_type, index_type> result_type;
      if(is_ltz(b))
        {
          r = nt2::inv(nt2::mpower(a, -b));
          return;
        }
      else {
        value_type m = nt2::trunc(b);
        value_type f = b-m;
        result_type q, t;
        // tie(q, t) = schur(a,'N'/*"complex"*/); // t is complex schur form.        result_type e, v;
        if (false && isdiagonal(t))
          {
            t = nt2::from_diag(nt2::pow(diag_of(t), m));
            r = nt2::mtimes(q, nt2::mtimes(t, nt2::trans(nt2::conj(q))));
            return;
          }
        else
          { //use iterative method
            r = nt2::eye(nt2::size(a), meta::as_<value_type>());
            result_type rf = r;
            if (m)
              {
                result_type a00 = a;
                while (m >= nt2::One<value_type>())
                  {
                    if (nt2::is_odd(m))
                      {
                        r =  nt2::mtimes(a00, r);
                      }
                    a00 =  nt2::mtimes(a00, a00);
                    m =  nt2::trunc(m/2); //Half<value_type>(); or >> 1
                  }
              }
            if(!f)
              {
                return;
              }
            else
              {
                result_type a00 = nt2::sqrtm(a);
                value_type thresh = nt2::Half<value_type>();
                while (f > Zero<value_type>())
                  {
                    if (f >= thresh)
                      {
                        rf = nt2::mtimes(rf, a00);
                        f -= thresh;
                      }
                    thresh *= nt2::Half<value_type>();
                    a00 =  nt2::sqrtm(a00);
                  }
              }
            r= nt2::mtimes(r, rf);
          }
      }
    }
  };

} }

#endif
