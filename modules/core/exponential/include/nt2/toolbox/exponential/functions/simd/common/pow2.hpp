//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW2_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow2.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/twopower.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>  
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_< floating_<A0>,X >))
                              ((simd_< integer_<A1>,X >))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::ldexp(a0, a1);
    }
  };
} }


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X >))
                              ((simd_< floating_<A0>,X >))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ldexp(a0, nt2::toint(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< integer_<A0>,X >))
                              ((simd_< integer_<A0>,X >))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ldexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< integer_<A0>,X >))
                            )
  {

    typedef typename  boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return nt2::ldexp(One<A0>(), a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X >))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return nt2::if_allbits_else(is_nan(a0),
                                  nt2::if_else(is_inf(a0),
                                               if_else(is_gtz(a0), a0, Zero<result_type>()),
                                               nt2::ldexp(One<A0>(), nt2::toint(a0))
                                               )
                                  );
    }
  };  
    
} }


#endif
