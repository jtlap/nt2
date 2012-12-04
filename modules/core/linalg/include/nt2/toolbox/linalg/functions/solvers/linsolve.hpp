//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_LINSOVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_LINSOVE_HPP_INCLUDED

// #include <nt2/toolbox/linalg/functions/linsolve.hpp>
// #include <nt2/options.hpp>
// #include <nt2/core/container/table/table.hpp>
// #include <nt2/include/functions/ismatrix.hpp>

// namespace nt2 { namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::linsolve_, tag::cpu_
//                               , (A0)(A1)
//                               , ((ast_<A0, nt2::container::domain>))
//                               ((ast_<A1, nt2::container::domain>))
//                             )
//   {
//     typedef typename meta::strip<A0>::type                                base_t;
//     typedef typename base_t::value_type                                  value_t;
//     typedef typename base_t::settings_type                            settings_t;
//     typedef details::linsolve_result< table<value_t,settings_t> >    result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
//     {
//       BOOST_ASSERT_MSG( nt2::ismatrix(a)
//                       , "??? Error using 'linsolve' : argument a must be matrix."
//                       );
//       BOOST_ASSERT_MSG( nt2::ismatrix(b)
//                       , "??? Error using 'linsolve' : argument b must be matrix."
//                       );
//       result_type that(a, b);
//       return that;
//     }
//   };
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::linsolve_, tag::cpu_
//                               , (A0)(A1)(IP)
//                               , ((ast_<A0, nt2::container::domain>))
//                               ((ast_<A1, nt2::container::domain>))
//                               (unspecified_<IP>)
//                             )
//   {
//     typedef typename meta::strip<A0>::type                                base_t;
//     typedef typename base_t::value_type                                  value_t;
//     typedef typename base_t::settings_type                            settings_t;
//     typedef details::linsolve_result< table<value_t,settings_t> >    result_type;

//     BOOST_FORCEINLINE result_type operator()(A0& a, A1 const& b, IP const &) const
//     {
//       BOOST_ASSERT_MSG( nt2::ismatrix(a)
//                       , "??? Error using 'linsolve' : argument a must be matrix."
//                       );
//       BOOST_ASSERT_MSG( nt2::ismatrix(b)
//                       , "??? Error using 'linsolve' : argument b must be matrix."
//                       );
//       result_type that(a, b);
//       return that;
//     }
//   };
// //   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::linsolve_, tag::cpu_
// //                               , (A0)(A1)(A2)
// //                               , ((ast_<A0, nt2::container::domain>))
// //                               ((ast_<A1, nt2::container::domain>))
// //                               (unspecified_<A2>)
// //                             )
// //   {
// //     typedef typename meta::strip<A0>::type                                base_t;
// //     typedef typename base_t::value_type                                  value_t;
// //     typedef typename base_t::settings_type                            settings_t;
// //     typedef details::linsolve_result< table<value_t,settings_t> >    result_type;

// //     BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b, A2 const & opts) const
// //     {
// //       BOOST_ASSERT_MSG( nt2::ismatrix(a)
// //                       , "??? Error using 'linsolve' : argument a must be matrix."
// //                       );
// //       BOOST_ASSERT_MSG( nt2::ismatrix(b)
// //                       , "??? Error using 'linsolve' : argument b must be matrix."
// //                       );
// //       result_type that(a, b, opts);
// //       return that;
// //     }
// //   };
// //   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::linsolve_, tag::cpu_
// //                               , (A0)(A1)(A2)(IP)
// //                               , ((ast_<A0, nt2::container::domain>))
// //                               ((ast_<A1, nt2::container::domain>))
// //                               (options_<A2>)
// //                               (unspecified_<IP>)
// //                             )
// //   {
// //     typedef typename meta::strip<A0>::type                                base_t;
// //     typedef typename base_t::value_type                                  value_t;
// //     typedef typename base_t::settings_type                            settings_t;
// //     typedef details::linsolve_result< table<value_t,settings_t> >    result_type;

// //     BOOST_FORCEINLINE result_type operator()(A0& a, A1 const& b,
// //                                              A2 const & opts, IP const &) const
// //     {
// //       BOOST_ASSERT_MSG( nt2::ismatrix(a)
// //                       , "??? Error using 'linsolve' : argument a must be matrix."
// //                       );
// //       BOOST_ASSERT_MSG( nt2::ismatrix(b)
// //                       , "??? Error using 'linsolve' : argument b must be matrix."
// //                       );
// //       result_type that(a, b, opts);
// //       return that;
// //     }
// //   };

// } }

#endif
