//==============================================================================
//         Copyright 2015  J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HGEQZ_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HGEQZ_HPP_INCLUDED

#include <nt2/linalg/functions/hgeqz.hpp>
#include <nt2/linalg/details/lapack/declare/hgeqz.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/functions/details/combine.hpp>
#include <iostream>
#include <nt2/table.hpp>
namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( hgeqz_, tag::cpu_
                            , (JOB)(COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(ALPHA)(SALPHA)(BETA)(SBETA)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<JOB> >)
                              (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, double_<A>, S0 >))
                              ((container_< nt2::tag::table_, double_<B>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<ALPHA>>, SALPHA>))
                              ((container_< nt2::tag::table_, double_<BETA>, SBETA>))
                              ((container_< nt2::tag::table_, double_<Q>, S2 >))
                              ((container_< nt2::tag::table_, double_<Z>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    BOOST_FORCEINLINE result_type operator()(JOB const & job, COMPQ const &compq,  COMPZ const & compz
                                            , ILO const & il, IHI const & ih
                                            , A& a, B& b
                                            , ALPHA& alpha, BETA& beta
                                            , Q& q, Z& z) const
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
      nt2_la_int nw = nt2::max(n, One<nt2_la_int>());
      nt2::container::table<type_t> alphar(of_size(nw, 1)), alphai(of_size(nw, 1));
      container::table<type_t> w(of_size(nw, 1));
      alpha.resize(of_size(nw,1));
      beta.resize(of_size(nw,1));

      NT2_F77NAME(dhgeqz)(&job, &compq, &compz, &n
                         , &ilo, &ihi
                         , a.data(), &lda
                         , b.data(), &ldb
                         , alphar.data(), alphai.data(), beta.data()
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , w.data(), &nw
                         , &that);
      combine_eigens(alphar, alphai, alpha);

      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( hgeqz_, tag::cpu_
                            , (JOB)(COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(ALPHA)(SALPHA)(BETA)(SBETA)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<JOB> >)
                              (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, single_<A>, S0 >))
                              ((container_< nt2::tag::table_, single_<B>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<ALPHA>>, SALPHA>))
                              ((container_< nt2::tag::table_, single_<BETA>, SBETA>))
                              ((container_< nt2::tag::table_, single_<Q>, S2 >))
                              ((container_< nt2::tag::table_, single_<Z>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef  typename A::value_type type_t;
    BOOST_FORCEINLINE result_type operator()(JOB const & job, COMPQ const &compq,  COMPZ const & compz
                                            , ILO const & il, IHI const & ih
                                            , A& a, B& b
                                            , ALPHA& alpha, BETA& beta
                                            , Q& q, Z& z) const
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
      nt2_la_int nw = nt2::max(n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      nt2::container::table<type_t> alphar(of_size(nw, 1)), alphai(of_size(nw, 1));
      alpha.resize(of_size(nw,1));
      beta.resize(of_size(nw,1));
      NT2_F77NAME(shgeqz)( &job, &compq, &compz, &n
                         , &ilo, &ihi
                         , a.data(), &lda
                         , b.data(), &ldb
                         , alphar.data(), alphai.data(), beta.data()
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , w.data(), &nw
                         , &that);
      combine_eigens(alphar, alphai, alpha);
      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( hgeqz_, tag::cpu_
                            , (JOB)(COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(ALPHA)(SALPHA)(BETA)(SBETA)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<JOB> >)
                              (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, complex_<single_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<ALPHA>>, SALPHA>))
                              ((container_< nt2::tag::table_, complex_<single_<BETA>>, SBETA>))
                              ((container_< nt2::tag::table_, complex_<single_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<single_<Z>>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    typedef typename meta::as_real<type_t>::type  rtype_t;
    BOOST_FORCEINLINE result_type operator()(JOB const & job, COMPQ const &compq,  COMPZ const & compz
                                            , ILO const & il, IHI const & ih
                                            , A& a, B& b
                                            , ALPHA& alpha, BETA& beta
                                            , Q& q, Z& z) const
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
      nt2_la_int nw = nt2::max(n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      container::table<rtype_t> rw(of_size(nw, 1));
      alpha.resize(of_size(nw,1));
      beta.resize(of_size(nw,1));
      NT2_F77NAME(chgeqz)(&job, &compq, &compz, &n
                         , &ilo, &ihi
                         , a.data(), &lda
                         , b.data(), &ldb
                         , alpha.data()
                         , beta.data()
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , w.data(), &nw, rw.data()
                         , &that);

      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( hgeqz_, tag::cpu_
                            , (JOB)(COMPQ)(COMPZ)(ILO)(IHI)(A)(S0)(B)(S1)(ALPHA)(SALPHA)(BETA)(SBETA)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<JOB> >)
                              (scalar_< ints8_<COMPQ> >)
                              (scalar_< ints8_<COMPZ> >)
                              (scalar_< integer_<ILO>>)
                              (scalar_< integer_<IHI>>)
                              ((container_< nt2::tag::table_, complex_<double_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<ALPHA>>, SALPHA>))
                              ((container_< nt2::tag::table_, complex_<double_<BETA>>, SBETA>))
                              ((container_< nt2::tag::table_, complex_<double_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<double_<Z>>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    typedef typename meta::as_real<type_t>::type  rtype_t;
    BOOST_FORCEINLINE result_type operator()(JOB const & job, COMPQ const &compq,  COMPZ const & compz
                                            , ILO const & il, IHI const & ih
                                            , A& a, B& b
                                            , ALPHA& alpha, BETA& beta
                                            , Q& q, Z& z) const
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
      nt2_la_int nw = nt2::max(n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      container::table<rtype_t> rw(of_size(nw, 1));
      alpha.resize(of_size(nw,1));
      beta.resize(of_size(nw,1));
      NT2_F77NAME(zhgeqz)(&job, &compq, &compz, &n
                         , &ilo, &ihi
                         , a.data(), &lda
                         , b.data(), &ldb
                         , alpha.data()
                         , beta.data()
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , w.data(), &nw, rw.data()
                         , &that);

      return that;
    }
  };

} }

#endif
