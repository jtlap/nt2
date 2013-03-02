/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_IMPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_IMPOWER_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/impower.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_even.hpp>
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
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::impower_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::impower_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1 ) const
    {
      const In0& a  = boost::proto::child_c<0>(a0);
      const In1& nn  = boost::proto::child_c<1>(a0);
      const Out0& r  = boost::proto::child_c<0>(a1);
      //      typedef typename A0::index_type       index_type;
      typedef nt2::table<value_type>     r_type;
      value_type n = value_type(nn);
      BOOST_ASSERT_MSG(is_flint(n), "impower requires the second argument to be int or flint");
      if(nt2::isscalar(a))
        {
          r = nt2::pow(a, n);
          return;
        }
      bool is_ltz_n = is_ltz(n);
      if(is_ltz_n) n = -n;
      value_type m = nt2::round(n); //MAYBE UNECESSARY
      r_type q, t;
      // nt2::tie(q, t) = schur(a0,'N'/*"complex"*/); // t is complex schur form.
      if (false && nt2::isdiagonal(t))
        {
          t = nt2::from_diag(nt2::pow(diag_of(t), m));
          if(is_ltz_n) t = nt2::inv(t);
          r = nt2::mtimes(q, nt2::mtimes(t, nt2::trans(nt2::conj(q))));
        }
      else
        { //use iterative method
          r = nt2::eye(nt2::size(a0), meta::as_<value_type>());
          r_type a00 = a;
          while (m >=  nt2::One<value_type>())
            {
              if (nt2::is_odd(m))
                {
                  r = nt2::mtimes(a00, r);
                }
              a00 =  nt2::mtimes(a00, a00);
              m =  nt2::trunc(m/2); //Half<value_type>(); or >> 1
            }
          if(is_ltz_n) r = nt2::inv(r);
        }
    }
  };

} }

#endif
