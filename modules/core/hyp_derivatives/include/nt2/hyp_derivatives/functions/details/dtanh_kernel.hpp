//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_DETAILS_DTANH_KERNEL_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_DETAILS_DTANH_KERNEL_HPP_INCLUDED
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
  struct dtanh_kernel
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename container::table<sA0> pol_t;
    static BOOST_FORCEINLINE  void tanh_pl(pol_t& pol)
    {
      pol_t p1 = cons<sA0>(of_size(1, 3), -1, 0, 1);
      compute(pol, p1);
    }
  private:
    static BOOST_FORCEINLINE  void compute(pol_t& pol, const pol_t& p1)
    {
      pol = p1;
      for (int i = 1; i < P; ++i)
      {
        pol_t pol1 = conv(p1, polyder(pol));
        pol = pol1;
      }
    }
  };

} }

#endif
