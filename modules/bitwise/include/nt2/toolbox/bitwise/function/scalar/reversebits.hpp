//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_REVERSEBITS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_REVERSEBITS_HPP_INCLUDED

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints8_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef union { A0 a; nt2::uint8_t b; } trick;
      trick z = {a0};
      z.b = ((z.b * 0x0802LU & 0x22110LU) | (z.b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
      return z.a;
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints64_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef union { A0 a; nt2::uint32_t b[2]; } trick;
      trick z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints16_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef union { A0 a; nt2::uint8_t b[2]; } trick;
      trick z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return  z.a;
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints32_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef union { A0 a; nt2::uint16_t b[2]; } trick;
      trick z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
      }
  };
} }

#endif
