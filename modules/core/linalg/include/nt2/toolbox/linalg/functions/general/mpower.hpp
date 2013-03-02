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
#include <nt2/include/functions/complexify.hpp>
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
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/mpl/bool.hpp>
namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mpower_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::mpower_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename A0::value_type                                  value_type;
    typedef std::complex<value_type>                                  cplx_type;
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
      typedef typename A0::index_type        index_type;
      typedef table<value_type, index_type> result_type;
      typedef table<cplx_type>                  ct_type;
      bool is_ltz_b = is_ltz(b);
      if(is_ltz(b)) b = -b;
      value_type m = nt2::trunc(b);
      value_type f = b-m;
      ct_type q, t;
      nt2::tie(q, t) = schur(nt2::complexify(a),'N'); // t is complex schur form.        result_type e, v;
      if (isdiagonal(t))
      {
        t = nt2::from_diag(nt2::pow(diag_of(t), m));
        if(is_ltz_b) t = nt2::inv(t);
        BOOST_AUTO_TPL(z, nt2::mtimes(q, nt2::mtimes(t, nt2::trans(nt2::conj(q)))));
        transtype(r, z, typename nt2::meta::is_complex<value_type>::type());
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
          if(is_ltz_b) r = nt2::inv(r);
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
        if(is_ltz_b) r = nt2::inv(r);
      }
    }
    template < class T1, class T2>
      BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::true_ const &)
    {
      r = z;
    }
    template < class T1, class T2 >
      BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::false_ const &)
    {
      r =  real(z);
    }

  };

} }

#endif
