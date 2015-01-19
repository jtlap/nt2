//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_SPH2CART_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_SPH2CART_HPP_INCLUDED
#include <nt2/trigonometric/functions/sph2cart.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <boost/fusion/tuple.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0,A0>        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& az, A0 const& elev,A0 const& r) const
    {
      A0 x, y, tmp;
      sincos(az, y, x); //y = sin(az),  x =  cos(az)
      A0 z = r*sincos(elev, tmp); // z = r*sin(elev), tmp =  cos(elev)
      tmp *= r; //tmp = r*cos(elev)
      return result_type(x*tmp, y*tmp, z); //
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0>        result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& az, A0 const& elev,A0 const& r
                                            , A0 & z) const
    {
      A0 x, y, tmp;
      sincos(az, y, x);
      z = r*sincos(elev, tmp);
      tmp *= r;
      return  result_type(x*tmp, y*tmp);

    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_
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
    BOOST_FORCEINLINE result_type operator()(A0 const& az,A0 const& elev,A0 const& r
                                            ,A0 & y, A0& z)
    {
      A0 x, tmp;
      sincos(az, y, x);
      z = r*sincos(elev, tmp);
      tmp *= r;
      y *= tmp;
      return  x*tmp;
    }
  };



  BOOST_DISPATCH_IMPLEMENT  ( sph2cart_, tag::cpu_
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
    BOOST_FORCEINLINE result_type operator()(A0 const& az, A0 const& elev,A0 const& r
                                            , A0 & x, A0 & y, A0 & z) const
    {
      A0 tmp;
      sincos(az, y, x);
      z = r*sincos(elev, tmp);
      tmp *= r;
      y *= tmp;
      x *= tmp;
    }
  };

} }

#endif
