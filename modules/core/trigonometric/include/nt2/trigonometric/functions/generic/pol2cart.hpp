//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_POL2CART_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_POL2CART_HPP_INCLUDED
#include <nt2/trigonometric/functions/pol2cart.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/multiplies.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( pol2cart_
                            , tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& r,A0 const& t,A0 & y)
    {
      A0 x;
      y = r*sincos(t, x);
      return x*= r;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pol2cart_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& r, A0 const& t) const
    {
      A0 x, y;
      sincos(t, x, y);
      return result_type(r*y, r*x);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( pol2cart_, tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& r, A0 const& t, A0 & x, A0 & y) const
    {
      y = r*sincos(t, x);
      x *= r;
    }
  };

} }

#endif
