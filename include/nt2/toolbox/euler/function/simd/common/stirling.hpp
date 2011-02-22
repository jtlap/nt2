//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
// #ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_STIRLING_HPP_INCLUDED
// #define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_STIRLING_HPP_INCLUDED
// #include <nt2/sdk/simd/meta/is_real_convertible.hpp>
// #include <nt2/sdk/constant/digits.hpp>
// #include <nt2/sdk/constant/real.hpp>
// #include <nt2/sdk/meta/strip.hpp>
// #include <nt2/include/functions/pow.hpp>
// #include <nt2/include/functions/polevl.hpp>
// #include <nt2/include/functions/fma.hpp>
// #include <nt2/include/functions/rec.hpp>
// #include <nt2/include/functions/exp.hpp>



// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is arithmetic_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::stirling_, tag::cpu_,
//                            (A0)(X),
//                            ((simd_<arithmetic_<A0>,X>))
//                           );

// namespace nt2 { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<tag::stirling_(tag::simd_<tag::arithmetic_, X> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0)>: meta::as_real<A0>{};

//     NT2_FUNCTOR_CALL(1)
//     {
//       typedef typename NT2_RETURN_TYPE(1)::type type;
//       return stirling(type(a0));
//     }
//   };
// } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is double
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::stirling_, tag::cpu_,
//                            (A0)(X),
//                            ((simd_<double_<A0>,X>))
//                           );

// namespace nt2 { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<tag::stirling_(tag::simd_<tag::double_, X> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0)>: meta::as_real<A0>{};

//     NT2_FUNCTOR_CALL(1)
//     {
//       typedef typename meta::scalar_of<A0>::type  sA0;
//       static const A0 MAXSTIR = splat<A0>(143.01608);
//       static const boost::array<sA0, 5 > STIR = {{
//         7.87311395793093628397E-4,
//         -2.29549961613378126380E-4,
//         -2.68132617805781232825E-3,
//         3.47222221605458667310E-3,
//         8.33333333333482257126E-2,
//       }};
//       static const A0 SQTPI =  splat<A0>(2.50662827463100050242E0);
//       A0 w = rec(a0);
//       w = fma(w, polevl( w, STIR), One<A0>());
//       A0 y = exp(-a0);
//       const A0 v = pow(a0, fma(Half<A0>(), a0, - Quarter<A0>()));
//       y *= v;
//       y *= v;
//       y *= SQTPI*w;
//       return y;
//     }
//   };
// } }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is float
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::stirling_, tag::cpu_,
//                            (A0)(X),
//                            ((simd_<float_<A0>,X>))
//                           );

// namespace nt2 { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<tag::stirling_(tag::simd_<tag::float_, X> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0)>: meta::as_real<A0>{};

//     NT2_FUNCTOR_CALL(1)
//     {
//       typedef typename meta::scalar_of<A0>::type  sA0;
//       static const A0 SQTPI = splat<A0>(2.50662827463100050242); /* sqrt( 2 pi ) */
//       static const boost::array<sA0, 3 > STIR = {{
//         -2.705194986674176E-003f,
//         3.473255786154910E-003f,
//         8.333331788340907E-002f,
//       }};
//       static const A0 MAXSTIR = splat<A0>(26.77);

//       A0 w = rec(a0);
//       w = fma(w, polevl( w, STIR), One<A0>());
//       A0 r = Nan<A0>();
//       A0 y = exp( -a0 );
//       A0 test = gt(a0, MAXSTIR);
//       const A0 v = pow( a0, fma(Half<A0>(), a0, - Quarter<A0>()) );
//       y *= v;
//       y *= v;
//       y *= SQTPI * w;
//       return y;
//     }
//   };
// } }

// #endif
// // modified by jt the 05/01/2011
