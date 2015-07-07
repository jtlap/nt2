//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_DETAILS_SEC_KERNEL_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_DETAILS_SEC_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/polyder.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/table.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < long P, class A0>
  struct sec_kernel
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename container::table<sA0> pol_t;
    static BOOST_FORCEINLINE  void csc_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), -1, 0, -1);
      pol_t p0 = cons<sA0>(of_size(1, 2), -1, 0);
      compute(pol, p0, p1);
    }
    static BOOST_FORCEINLINE  void sec_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), 1, 0, 1);
      pol_t p0 = cons<sA0>(of_size(1, 2), 1, 0);
      compute(pol, p0, p1);
    }
    static BOOST_FORCEINLINE  void cscd_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), -1, 0, -1);
      pol_t p0 = cons<sA0>(of_size(1, 2), -1, 0);
      compute(pol, p0, p1, Deginrad<sA0>());
    }
    static BOOST_FORCEINLINE  void secd_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), 1, 0, 1);
      pol_t p0 = cons<sA0>(of_size(1, 2), 1, 0);
      compute(pol, p0, p1, Deginrad<sA0>());
    }
    static BOOST_FORCEINLINE  void cscpi_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), -1, 0, -1);
      pol_t p0 = cons<sA0>(of_size(1, 2), -1, 0);
      compute(pol, p0, p1, Invpi<sA0>());
    }
    static BOOST_FORCEINLINE  void secpi_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), 1, 0, 1);
      pol_t p0 = cons<sA0>(of_size(1, 2), 1, 0);
      compute(pol, p0, p1, Invpi<sA0>());
    }
  private:
    static BOOST_FORCEINLINE  void compute(pol_t& pol
                                          , const pol_t& p0
                                          , const pol_t& p1)
    {
      pol = p0;
      for (int i = 1; i < P; ++i)
      {
        pol_t pol1 = conv(p0, pol)+ conv(p1, polyder(pol));
        pol = pol1;
      }
    }
    static BOOST_FORCEINLINE  void compute(pol_t& pol
                                          , const pol_t& p0
                                          , const pol_t& p1
                                          , sA0 coef)
    {
      pol = p0*coef;
      for (int i = 1; i < P; ++i)
      {
        pol_t pol1 = conv(p0, pol)+ conv(p1, polyder(pol));
        pol = pol1*coef;
      }
    }
  };

} }

#endif
