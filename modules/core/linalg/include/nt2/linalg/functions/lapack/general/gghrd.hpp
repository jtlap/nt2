//==============================================================================
//         Copyright 2015  J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGHRD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGHRD_HPP_INCLUDED

#include <nt2/linalg/functions/gghrd.hpp>
#include <nt2/linalg/details/lapack/declare/gghrd.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/max.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( gghrd_, tag::cpu_
                            , (COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, double_<A>, S0 >))
                              ((container_< nt2::tag::table_, double_<B>, S1 >))
                              ((container_< nt2::tag::table_, double_<Q>, S2 >))
                              ((container_< nt2::tag::table_, double_<Z>, S3 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A::value_type type_t;
     BOOST_FORCEINLINE result_type operator()(COMPQ const &compq,  COMPZ const & compz
                                             , ILO const & il, IHI const & ih
                                            ,  A& a, B& b, Q& q, Z& z) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a);
        if(compq == 'i' || compq == 'I') q.resize(of_size(n,n));
        if(compz == 'i' || compz == 'I') z.resize(of_size(n,n));
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
        nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
        nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
        nt2_la_int  ilo = il;
        nt2_la_int  ihi = ih;

        NT2_F77NAME(dgghrd)(&compq, &compz, &n
                           , &ilo, &ihi
                           , a.data(), &lda
                           , b.data(), &ldb
                           , q.data(), &ldq
                           , z.data(), &ldz,
                            &that);

        return that;
     }
  };

  BOOST_DISPATCH_IMPLEMENT  ( gghrd_, tag::cpu_
                            , (COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, single_<A>, S0 >))
                              ((container_< nt2::tag::table_, single_<B>, S1 >))
                              ((container_< nt2::tag::table_, single_<Q>, S2 >))
                              ((container_< nt2::tag::table_, single_<Z>, S3 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef  typename A::value_type type_t;
     BOOST_FORCEINLINE result_type operator()(COMPQ const &compq,  COMPZ const & compz
                                             , ILO const & il, IHI const & ih
                                            ,  A& a, B& b, Q& q, Z& z) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a);
        if(compq == 'i' || compq == 'I') q.resize(of_size(n,n));
        if(compz == 'i' || compz == 'I') z.resize(of_size(n,n));
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
        nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
        nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
        nt2_la_int  ilo = il;
        nt2_la_int  ihi = ih;
        NT2_F77NAME(sgghrd)(&compq, &compz, &n
                           , &ilo, &ihi
                           , a.data(), &lda
                           , b.data(), &ldb
                           , q.data(), &ldq
                           , z.data(), &ldz,
                            &that);

        return that;
     }
  };

  BOOST_DISPATCH_IMPLEMENT  ( gghrd_, tag::cpu_
                            , (COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, complex_<single_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<single_<Z>>, S3 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A::value_type type_t;
     BOOST_FORCEINLINE result_type operator()(COMPQ const &compq,  COMPZ const & compz
                                             , ILO const & il, IHI const & ih
                                            ,  A& a, B& b, Q& q, Z& z) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a);
        if(compq == 'i' || compq == 'I') q.resize(of_size(n,n));
        if(compz == 'i' || compz == 'I') z.resize(of_size(n,n));
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
        nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
        nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
        nt2_la_int  ilo = il;
        nt2_la_int  ihi = ih;

        NT2_F77NAME(cgghrd)(&compq, &compz, &n
                           , &ilo, &ihi
                           , a.data(), &lda
                           , b.data(), &ldb
                           , q.data(), &ldq
                           , z.data(), &ldz,
                            &that);

        return that;
     }
  };

  BOOST_DISPATCH_IMPLEMENT  ( gghrd_, tag::cpu_
                            , (COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, complex_<double_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<double_<Z>>, S3 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A::value_type type_t;
     BOOST_FORCEINLINE result_type operator()(COMPQ const &compq,  COMPZ const & compz
                                             , ILO const & il, IHI const & ih
                                            ,  A& a, B& b, Q& q, Z& z) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a);
        if(compq == 'i' || compq == 'I') q.resize(of_size(n,n));
        if(compz == 'i' || compz == 'I') z.resize(of_size(n,n));
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
        nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
        nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
        nt2_la_int  ilo = il;
        nt2_la_int  ihi = ih;

        NT2_F77NAME(zgghrd)(&compq, &compz, &n
                           , &ilo, &ihi
                           , a.data(), &lda
                           , b.data(), &ldb
                           , q.data(), &ldq
                           , z.data(), &ldz,
                            &that);

        return that;
     }
  };

} }

#endif
