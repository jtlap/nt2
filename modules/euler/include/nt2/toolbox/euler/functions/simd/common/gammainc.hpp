//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_GAMMAINC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_GAMMAINC_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/gammainc.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/eps.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/options.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammainc_, tag::cpu_
                              , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A1>,X>)) 
                            )
  {
    typedef typename meta::as_floating<A0, A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return gammainc(tofloat(a0), tofloat(a1));
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is floating_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gammainc_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_<floating_<A0>,X>))
                             ((simd_<floating_<A1>,X>))
                             )
  {
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(const A0& xx, const A1& aa) const
      {
        typedef typename meta::as_logical<A0>::type bA0;
        A0 x = xx;
        A1 a = aa;
        const A1 amax = splat<A1>(1048576); 
        bA0 test = gt(a, amax); 
        std::size_t nb =   boost::simd::inbtrue(test);
        if (nb) {
          x =  nt2::max(nt2::fma(nt2::sqrt(amax/a), x-(a-Third<A1>()), amax-Third<A1>()),Zero<A1>()); 
          a =  if_else(test,  amax, a);
        }; 
        A0 res = Nan<A0>();
        size_t nbt = 0u; 
        test = lt(x, oneplus(a));
        if ((nb = boost::simd::inbtrue(test)))
          {
            res = boost::simd::if_else(test, gammainc(x, a, test, case0_), res);
            nbt+= nb; 
            if (nbt >= meta::cardinal_of<A0>::value) return res; 
          }
        test = logical_not(test); 
        res = boost::simd::if_else(test, gammainc(x, a, test, case1_), res);
        return res; 
      }
  };

    NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gammainc_, tag::cpu_,
                             (A0)(A1)(A3)(X),
                             ((simd_<floating_<A0>,X>))
                             ((simd_<floating_<A1>,X>))
                             ((target_<unspecified_<A3> >))
                             )
  {
    // target case1_ means x < a+1
    // target case2_ means x >= a+1
    typedef typename nt2::meta::scalar_of<A0>::type sA0; 
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(const A0& xx, const A1& a, const A3 &) const
      {
        return doit(xx, a, typename A3::type());
      }
  private :
    static inline result_type doit(const A0& x, const A1& a, const details::case0_ &)
      {
        //Series expansion for x < a+1
        // k = find(a ~= 0 & x ~= 0 & x < a+1);
        A1 ap = a;
        A0 del = One<A0>();
        A0 sum = del;
        while (nt2::maximum(nt2::abs(del)) >= Hundred<sA0>()*nt2::eps(nt2::maximum(nt2::abs(sum))))
          {
            ap += One<A0>();
            del = x*del/ap;
            sum += del;
          }
        A0  b = sum*nt2::exp(-x + a*nt2::log(x) - nt2::gammaln(oneplus(a)));
        //  For very small a, the series may overshoot very slightly.
        b =  nt2::min(b, One<A0>()); 
        //     if lower, b(k) = bk; else b(k) = 1-bk; end
        return b; 
      }
    static inline result_type doit(const A0& x, const A1& a, const details::case1_ &)
      {
        // Continued fraction for x >= a+1
//           std::cout << "1a " << a << std::endl; 
//           std::cout << "1x " << x << std::endl; 

        //k = find(a ~= 0 & x >= a+1); % & x ~= 0
        A0 a0 = One<A0>();
        A0 a1 = x;
        A0 b0 = Zero<A0>();
        A0 b1 = a0;
        A0 fac = nt2::rec(a1);
        A0 n = One<A0>();
        A0 g = b1*fac;
        A0 gold = b0;
        while (maximum(nt2::abs(g-gold)) >= Hundred<sA0>()*nt2::eps(nt2::maximum(nt2::abs(g))))
          {
            gold = g;
            A0 ana = n - a;
            a0 = (a1 + a0*ana)* fac;
            b0 = (b1 + b0*ana)* fac;
            A0 anf = n*fac;
            a1 = x * a0 + anf * a1;
            b1 = x * b0 + anf * b1;
            fac = nt2::rec(a1);
            g = b1 * fac;
            n = oneplus(n);
          }
//         std::cout << "1g " << g << std::endl; 
//         std::cout << "x  " << x << std::endl;
//         std::cout << "isinf " << nt2::is_inf(x) << std::endl; 
        return if_else(nt2::is_inf(x), One<A0>(), oneminus(nt2::exp(-x + a*nt2::log(x) - gammaln(a))*g));
        //    if lower, b(k) = 1-bk; else b(k) = bk; end
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gammainc_, tag::cpu_,
                             (A0)(A1)(A2)(A3)(X),
                             ((simd_<floating_<A0>,X>))
                             ((simd_<floating_<A1>,X>))
                             ((simd_<logical_<A2>, X>))
                             ((target_<unspecified_<A3> >))
                             )
  {
    typedef typename nt2::meta::scalar_of<A0>::type sA0; 
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(const A0& xx, const A1& a, const A2& test, const A3 &) const
      {
        const A0 x = clipit(xx, a, test, typename A3::type()); 
        return nt2::gammainc(x, a, A3());
      }
  private :
    static inline result_type  clipit(const A0& x, const A1& a, const A2& test , const details::case0_ &)
      {
        return nt2::if_else(test, x, a); //insure convergence in each case for all members of simd vector making x =  a <  a+1 when the test do not succeed
      }
    static inline result_type  clipit(const A0& x, const A1& a, const A2& test , const details::case1_ &)
      {
        return nt2::if_else(test, x, oneplus(a)); //insure convergence in each case for all members of simd vector making x = a+1 >= a+1  when the test do not succeed
      }

  };  
} }
#endif
