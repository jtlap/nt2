//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_SPENCE_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_SPENCE_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/spence.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/log.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return spence(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      static boost::array<A0, 8> A = {{
        A0(4.65128586073990045278E-5),
        A0(7.31589045238094711071E-3),
        A0(1.33847639578309018650E-1),
        A0(8.79691311754530315341E-1),
        A0(2.71149851196553469920E0),
        A0(4.25697156008121755724E0),
        A0(3.29771340985225106936E0),
        A0(1.00000000000000000126E0),
      }};
      static boost::array<A0, 8> B = {{
        A0(6.90990488912553276999E-4),
        A0(2.54043763932544379113E-2),
        A0(2.82974860602568089943E-1),
        A0(1.41172597751831069617E0),
        A0(3.63800533345137075418E0),
        A0(5.03278880143316990390E0),
        A0(3.54771340985225096217E0),
        A0(9.99999999999999998740E-1),
      }};
      static const A0 C = (Pi<A0>()*Pi<A0>())/Six<A0>();
      A0 x = a0;
      if( x < Zero<A0>() )        return Nan<A0>();
      if( x == One<A0>() ) return Zero<A0>();
      if( is_eqz(x) )       return C ;
      int flag = 0;
      if( x > Two<A0>() ){ x = rec(x); flag |= 2;}
      A0 w;
      if( x > static_cast<A0>(1.5) )      { w = minusone(rec(x)); flag |= 2;}
      else if( x < Half<A0>() ) { w = -x; flag |= 1;}
      else w = minusone(x);
      A0 y = -w * polevl( w, A) / polevl( w, B);
      if( flag & 1 ) y = C -nt2::log(x) * nt2::log(One<A0>()-x) - y;
      if( flag & 2 )
        {
          A0 z = nt2::log(x);
          y = Mhalf<A0>() * sqr(z)  -  y;
        }
      return y;
    }
  };
} }


#endif
