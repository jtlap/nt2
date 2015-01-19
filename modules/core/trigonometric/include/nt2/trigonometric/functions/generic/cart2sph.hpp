//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_CART2SPH_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_CART2SPH_HPP_INCLUDED
#include <nt2/trigonometric/functions/cart2sph.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <boost/fusion/tuple.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( cart2sph_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0,A0>        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x, A0 const& y,A0 const& z) const
    {
      A0 r0 = hypot(x, y);
      return result_type(atan2(y, x), atan2(z, r0), hypot(r0, z));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cart2sph_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0>        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x, A0 const& y,A0 const& z
                                            , A0 & r) const
    {
      A0 r0 = hypot(x, y);
      r = hypot(r0, z);
      return result_type(atan2(y, x), atan2(z, r0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( cart2sph_
                            , tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                             )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x,A0 const& y,A0 const& z
                                            ,A0 & elev,A0 & r)
    {
      r = hypot(x, y);
      elev = atan2(z, r);
      r = hypot(r, z);
      return atan2(y, x);
    }
  };



  BOOST_DISPATCH_IMPLEMENT  ( cart2sph_, tag::cpu_
                            , (A0)
                            , ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                           )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A0 const& y,A0 const& z
                                            , A0 & az, A0 & elev, A0 & r) const
    {
      r = hypot(x, y);
      elev = atan2(z, r);
      r = hypot(r, z);
      az = atan2(y, x);
    }
  };

} }

#endif
