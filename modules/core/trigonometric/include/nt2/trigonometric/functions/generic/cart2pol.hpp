//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_CART2POL_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_CART2POL_HPP_INCLUDED
#include <nt2/trigonometric/functions/cart2pol.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/hypot.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( cart2pol_
                            , tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x,A0 const& y,A0 & theta)
    {
      theta = atan2(y, x);
      return hypot(x, y);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cart2pol_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x, A0 const& y) const
    {
      return result_type(hypot(x, y), atan2(y, x));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cart2pol_, tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A0 const& y, A0 & rho, A0 & theta) const
    {
      theta = atan2(y, x);
      rho =  hypot(x, y);
    }
  };

} }

#endif
