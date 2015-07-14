//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_DETAILS_SINHC_KERNEL_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_DETAILS_SINHC_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/polyadd.hpp>
#include <nt2/include/functions/polysub.hpp>
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
  struct dsinhc_kernel
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename container::table<sA0> pol_t;

    static BOOST_FORCEINLINE  void sinhc_pl(pol_t& p, pol_t& q)
    {
      p = cons<sA0>(of_size(1, 3), -1, 0, 0);
      q = cons<sA0>(of_size(1, 2), 1, 0);
      compute(p, q);
    }

  private:
    static BOOST_FORCEINLINE  void compute(pol_t& p, pol_t& q)
    {
      pol_t mx2 =  cons<sA0>(of_size(1, 3), -1, 0, 0);
      for (int i = 1; i < P; ++i)
      {
        pol_t pp = polyadd(conv(mx2, polyder(p)), q);
        pol_t qq = polyadd(conv(mx2, polyder(q)), p);
        p = pp;
        q = qq;
      }
    }
  };

} }

#endif
