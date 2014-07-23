//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_GENEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_GENEIG_HPP_INCLUDED

#include <nt2/linalg/functions/geneig.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/ggev_w.hpp>
#include <nt2/include/functions/ggev_wvr.hpp>
#include <nt2/include/functions/ggev_wvrvl.hpp>

#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/linalg/options.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <iostream>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A0& a1) const
    {
      return result_type(a0/a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A0& a1, const A1&) const
    {
      return result_type(a1/a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A0& a1, const A1&, const A2&) const
    {
      return result_type(a1/a0);
    }
  };


  //============================================================================
  //Geneig computations
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geneig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::geneig_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                  type_t;
    typedef typename nt2::meta::as_real<type_t>::type                   rtype_t;
    typedef typename nt2::meta::as_complex<rtype_t>::type               ctype_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - W = GENEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_3(a0, a1, nt2::policy<ext::vector_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - W = GENEIG(A, B, matrix_/vector_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_3(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 1o 3i
    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t>  beta(nt2::of_size(n,1));
      nt2::ggev_w( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(boost::proto::child_c<0>(a1))
                 , boost::proto::value(beta));
      boost::proto::child_c<0>(a1) /= beta;
    }


    /// INTERNAL ONLY: 1o 3i
    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t> beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));

      nt2::ggev_w( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(alpha)
                 , boost::proto::value(beta));
      boost::proto::child_c<0>(a1) = from_diag(alpha/beta);
      //from_diag doesnt support aliasing currently
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::lambda_> const &
                 ) const
    {
      eval1_2(a0, a1, nt2::policy<ext::vector_>());
    }

    template < class T > BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , T const &
                 ) const
    {
      BOOST_ASSERT_MSG(false, "unknown option or not enough outputs to support the option");
    }

    //==========================================================================
    /// INTERNAL ONLY - [alpha, beta] = GENEIG(A, B, alphabeta_) or
    ///                 [vr, w]       = GENEIG(A, B, matrix_/vectors/lambda)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_3(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::alphabeta_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      nt2::ggev_w( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(boost::proto::child_c<0>(a1))
                 , boost::proto::value(boost::proto::child_c<1>(a1)));
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t>  beta(nt2::of_size(n,1));
      nt2::ggev_wvr( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(boost::proto::child_c<1>(a1))
                 , boost::proto::value(beta)
                 , boost::proto::value(boost::proto::child_c<0>(a1)));
      boost::proto::child_c<1>(a1) /= beta;
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t> beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));

      nt2::ggev_wvr( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(alpha)
                 , boost::proto::value(beta)
                 , boost::proto::value(boost::proto::child_c<0>(a1)));
      boost::proto::child_c<1>(a1) = from_diag(alpha/beta);
      //from_diag doesnt support aliasing currently
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
      void eval2_3 ( A0& a0, A1& a1
                   ,  nt2::policy<ext::lambda_> const &
                   ) const
    {
      eval2_3(a0, a1,   nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY: 2o 3i
    template < class T > BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , T const &
                 ) const
    {
      BOOST_ASSERT_MSG(false, "unknown option");
    }

    //==========================================================================
    /// INTERNAL ONLY - [alpha, beta] = GENEIG(A, B, alphabeta_, matrix_/vectors)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<4> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_4(a0, a1, boost::proto::value(boost::proto::child_c<3>(a0)));
    }

    /// INTERNAL ONLY: 2o 4i
    BOOST_FORCEINLINE
    void eval2_4 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      eval2_3(a0, a1, nt2::policy<ext::alphabeta_>());
    }

    /// INTERNAL ONLY: 2o 4i
    BOOST_FORCEINLINE
    void eval2_4 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t> beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));

      nt2::ggev_w( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(alpha)
                 , boost::proto::value(beta)
                 );
      boost::proto::child_c<0>(a1) = from_diag(alpha);
      boost::proto::child_c<1>(a1) = from_diag(beta);
      //from_diag doesnt support aliasing currently
    }

    /// INTERNAL ONLY: 2o 4i
    template < class T > BOOST_FORCEINLINE
    void eval2_4 ( A0& a0, A1& a1
                 , T const &
                 ) const
    {
      BOOST_ASSERT_MSG(false, "unknown or not fit option");
    }


    //==========================================================================
    /// INTERNAL ONLY - [vr, alpha, beta] = GENEIG(A, B, alphabeta_) or
    ///                 [vr, w, vl]       = GENEIG(A, B, matrix_/vectors/lambda)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_3(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::alphabeta_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      nt2::ggev_wvr( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(boost::proto::child_c<1>(a1))//alpha
                 , boost::proto::value(boost::proto::child_c<2>(a1))//beta
                 , boost::proto::value(boost::proto::child_c<0>(a1))//vr
                 );
    }

    /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t>  beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));
      nt2::ggev_wvrvl( boost::proto::value(a)
                     , boost::proto::value(b)
                     , boost::proto::value(boost::proto::child_c<1>(a1))
                     , boost::proto::value(beta)
                     , boost::proto::value(boost::proto::child_c<0>(a1))//vr
                     , boost::proto::value(boost::proto::child_c<2>(a1))//vl
                     );
      boost::proto::child_c<1>(a1) /= beta;
    }

    /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t> beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));

      nt2::ggev_wvrvl( boost::proto::value(a)
                     , boost::proto::value(b)
                     , boost::proto::value(alpha)
                     , boost::proto::value(beta)
                     , boost::proto::value(boost::proto::child_c<0>(a1))//vr
                     , boost::proto::value(boost::proto::child_c<2>(a1))//vl
                     );
      boost::proto::child_c<1>(a1) = from_diag(alpha/beta);
      //from_diag doesnt support aliasing currently
    }

    /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::lambda_>
                 ) const
    {
      eval3_3(a0, a1,  nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY: 3o 3i
    template < class T > BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 , T const &
                 ) const
    {
      BOOST_ASSERT_MSG(false, "unknown option");
    }

    //==========================================================================
    /// INTERNAL ONLY - [vr, alpha, beta, vl] = GENEIG(A, B) or
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<4> const&
              ) const
    {
      eval4_3(a0, a1, nt2::policy<ext::matrix_>());
    }
    //==========================================================================
    /// INTERNAL ONLY - [vr, alpha, beta, vl] = GENEIG(A, B, matrix_/vectors) or
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<4> const&
              ) const
    {
      eval4_3(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 4o 3i
    BOOST_FORCEINLINE
    void eval4_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      nt2::ggev_wvrvl( boost::proto::value(a)
                 , boost::proto::value(b)
                 , boost::proto::value(boost::proto::child_c<1>(a1))//alpha
                 , boost::proto::value(boost::proto::child_c<2>(a1))//beta
                 , boost::proto::value(boost::proto::child_c<0>(a1))//vr
                 , boost::proto::value(boost::proto::child_c<3>(a1))//vl
                 );
    }

     /// INTERNAL ONLY: 4o 3i
    BOOST_FORCEINLINE
    void eval4_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = boost::proto::child_c<1>(a0);
      size_t n = height(boost::proto::child_c<0>(a0));
      container::table <type_t> beta(nt2::of_size(n,1));
      container::table <ctype_t> alpha(nt2::of_size(n,1));

      nt2::ggev_wvrvl( boost::proto::value(a)
                     , boost::proto::value(b)
                     , boost::proto::value(alpha)
                     , boost::proto::value(beta)
                     , boost::proto::value(boost::proto::child_c<0>(a1))//vr
                     , boost::proto::value(boost::proto::child_c<3>(a1))//vl
                     );
      boost::proto::child_c<1>(a1) = from_diag(alpha);
      boost::proto::child_c<2>(a1) = from_diag(beta);
      //from_diag doesnt support aliasing currently
    }

     /// INTERNAL ONLY: 4o 3i
    template < class T > BOOST_FORCEINLINE
    void eval4_3 ( A0& a0, A1& a1
                 , T const &
                 ) const
    {
//      BOOST_ASSERT_MSG(false, "unknown option, or not suited to 4 ouputs");
      eval4_3(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

  };
} }

#endif
