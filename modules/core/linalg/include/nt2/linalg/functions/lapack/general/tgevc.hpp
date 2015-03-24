//==============================================================================
//         Copyright 2015  J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_TGEVC_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_TGEVC_HPP_INCLUDED

#include <nt2/linalg/functions/tgevc.hpp>
#include <nt2/linalg/details/lapack/declare/tgevc.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/core/container/table/table.hpp>
// #include <nt2/linalg/functions/details/combine.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( tgevc_, tag::cpu_
                            , (SIDE)(HOWMNY)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<SIDE> >)
                              (scalar_< ints8_<HOWMNY> >)
                              ((container_< nt2::tag::table_, double_<A>, S0 >))
                              ((container_< nt2::tag::table_, double_<B>, S1 >))
                              ((container_< nt2::tag::table_, double_<Q>, S2 >))
                              ((container_< nt2::tag::table_, double_<Z>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    BOOST_FORCEINLINE result_type operator()(SIDE const & side, HOWMNY const &howmny
                                            , A& a, B& b
                                            , Q& q, Z& z) const
    {
      result_type that;
      nt2_la_int  n  = nt2::height(a);
      nt2_la_int  mm;
      if(howmny == 'a' || howmny == 'A')
      {
        q.resize(of_size(n,n));
        z.resize(of_size(n,n));
      }
      nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
      nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
      nt2_la_int nw = nt2::max(6*n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      NT2_F77NAME(dtgevc)(&side, &howmny, 0, &n
                         , a.data(), &lda
                         , b.data(), &ldb
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , &n, &mm
                         , w.data()
                         , &that);
 //      combine_vects(q, alphai, vl);

      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( tgevc_, tag::cpu_
                            , (SIDE)(HOWMNY)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<SIDE> >)
                              (scalar_< ints8_<HOWMNY> >)
                              ((container_< nt2::tag::table_, single_<A>, S0 >))
                              ((container_< nt2::tag::table_, single_<B>, S1 >))
                              ((container_< nt2::tag::table_, single_<Q>, S2 >))
                              ((container_< nt2::tag::table_, single_<Z>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef  typename A::value_type type_t;
    BOOST_FORCEINLINE result_type operator()(SIDE const & side, HOWMNY const &howmny
                                            , A& a, B& b
                                            , Q& q, Z& z) const
    {
      result_type that;
      nt2_la_int  n  = nt2::height(a);
      nt2_la_int  mm;
      if(howmny == 'a' || howmny == 'A')
      {
        q.resize(of_size(n,n));
        z.resize(of_size(n,n));
      }
      nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
      nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
      nt2_la_int nw = nt2::max(6*n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      NT2_F77NAME(stgevc)( &side, &howmny, 0, &n
                         , a.data(), &lda
                         , b.data(), &ldb
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , &n, &mm
                         , w.data()
                         , &that);
      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( tgevc_, tag::cpu_
                            , (SIDE)(HOWMNY)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<SIDE> >)
                              (scalar_< ints8_<HOWMNY> >)
                              ((container_< nt2::tag::table_, complex_<single_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<single_<Z>>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    typedef typename meta::as_real<type_t>::type  rtype_t;
    BOOST_FORCEINLINE result_type operator()(SIDE const & side, HOWMNY const &howmny
                                            , A& a, B& b
                                            , Q& q, Z& z) const
    {
      result_type that;
      nt2_la_int  n  = nt2::height(a);
      nt2_la_int  mm;
      if(howmny == 'a' || howmny == 'A')
      {
        q.resize(of_size(n,n));
        z.resize(of_size(n,n));
      }
      nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
      nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
      nt2_la_int nw = nt2::max(2*n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      container::table<rtype_t> rw(of_size(nw, 1));

      NT2_F77NAME(ctgevc)(&side, &howmny, 0, &n
                         , a.data(), &lda
                         , b.data(), &ldb
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , &n, &mm
                         , w.data(), rw.data()
                         , &that);

      return that;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( tgevc_, tag::cpu_
                            , (SIDE)(HOWMNY)(A)(S0)(B)(S1)(Q)(S2)(Z)(S3)
                            , (scalar_< ints8_<SIDE> >)
                              (scalar_< ints8_<HOWMNY> >)
                              ((container_< nt2::tag::table_, complex_<double_<A>>, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<B>>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<Q>>, S2 >))
                              ((container_< nt2::tag::table_, complex_<double_<Z>>, S3 >))
                            )
  {
    typedef nt2_la_int result_type;
    typedef typename A::value_type type_t;
    typedef typename meta::as_real<type_t>::type  rtype_t;
    BOOST_FORCEINLINE result_type operator()(SIDE const & side, HOWMNY const &howmny
                                            , A& a, B& b, Q& q, Z& z) const
    {
      result_type that;
      nt2_la_int  n  = nt2::height(a);
      nt2_la_int  mm;
      if(howmny == 'a' || howmny == 'A')
      {
        q.resize(of_size(n,n));
        z.resize(of_size(n,n));
      }

      nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int  ldb = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
      nt2_la_int  ldz = nt2::max(z.leading_size(), One<size_t>());
      nt2_la_int nw = nt2::max(2*n, One<nt2_la_int>());
      container::table<type_t> w(of_size(nw, 1));
      container::table<rtype_t> rw(of_size(nw, 1));

      NT2_F77NAME(ztgevc)(&side, &howmny, 0, &n
                         , a.data(), &lda
                         , b.data(), &ldb
                         , q.data(), &ldq
                         , z.data(), &ldz
                         , &n, &mm
                         , w.data(), rw.data()
                         , &that);
      return that;
     }
  };

} }

#endif
