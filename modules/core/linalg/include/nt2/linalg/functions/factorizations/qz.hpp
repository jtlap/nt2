//==============================================================================
//         Copyright 2015 - Jean-Thierry Lapresté
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_QZ_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_QZ_HPP_INCLUDED


#include <nt2/include/functions/qz.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/hess.hpp>
#include <nt2/include/functions/hgeqz.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tgevc.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //QZ Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( qz_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( qz_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (unspecified_<A2>)
                            )
  {
    typedef A0                                                      otype_t;
    typedef typename nt2::meta::as_real<A0>::type                   rtype_t;
    typedef typename meta::strip<A2>::type                            opt_t;
    typedef typename boost::mpl::if_ < boost::is_same< opt_t, nt2::policy<ext::real_> >
                              , rtype_t
                              , otype_t
                              >::type                           result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      return eval(a0, opt_t());
    }
  private :
    template < class T >
    BOOST_FORCEINLINE result_type eval( const A0& a0, const T& ) const
    {
      return a0;
    }

    BOOST_FORCEINLINE result_type eval( const A0& a0, nt2::policy<ext::real_> const & ) const
    {
      BOOST_ASSERT_MSG(isreal(a0),
                       "all input matrix elements are to be real to support"
                       "'real_' option with complex type input");
      return real(a0);
    }

  };


  //============================================================================
  //QZ
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( qz_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qz_
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
    typedef typename child0::value_type                                 type0_t;
    typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
    typedef typename child1::value_type                                 type1_t;
    typedef typename nt2::meta::as_complex<type0_t>::type               ctype_t;
    typedef typename nt2::meta::as_real<type0_t>::type                  rtype_t;
    typedef typename meta::is_complex<type0_t>::type                  iscplx0_t;
    typedef typename meta::is_complex<type1_t>::type                  iscplx1_t;
    typedef typename  boost::mpl::or_< iscplx0_t, iscplx1_t>::type     iscplx_t;
    typedef typename boost::mpl::if_ <
      boost::mpl::or_< iscplx0_t, iscplx1_t>
      , ctype_t
      , rtype_t
      >::type                                                            type_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>   r_semantic;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::_2D>   c_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(a0)),"first input must be square");
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<1>(a0)),"second input must be square");
      eval(a0, a1, N0(), N1());
    }
  private:
    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z] = qz(a, b)
    // returns the qz matrix
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& //2 inputs
              , boost::mpl::long_<4> const& //4 outputs
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      container::table<type_t> q, z;
      tie(a, b, q, z) = nt2::hess(a, b);
      //now a is hessenberg and b triangular, we can use hgeqz
      std::size_t n = height(a);
      container::table<ctype_t> alpha;
      container::table<type_t> beta;
      NT2_LAPACK_VERIFY(nt2::hgeqz('S', 'V', 'V'
                                  , 1, n
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(alpha)
                                  , boost::proto::value(beta)
                                  , boost::proto::value(q)
                                  , boost::proto::value(z)));
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
    }
    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, lambda] = qz(a, b)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& //2 inputs
              , boost::mpl::long_<5> const& //5 outputs so option must be lambda_
              ) const
    {
      eval3_5(a0, a1, policy<nt2::ext::lambda_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, lambda] = qz(a, b)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& //2 inputs
              , boost::mpl::long_<7> const& //7 outputs so option must be lambda_
              ) const
    {
      eval3_7(a0, a1, policy<nt2::ext::lambda_>());
    }
    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, lambda] = qz(a, b, option)
    // returns the qz matrix
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const& //3 inputs
              , boost::mpl::long_<5> const& //5 outputs
              ) const
    {
      eval3_5(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    BOOST_FORCEINLINE
    void eval3_5 ( A0& a0, A1& a1,  policy<nt2::ext::lambda_> const &) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, z, boost::proto::child_c<3>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<4>(a1));
      tie(a, b, q, z) = nt2::hess(a, b);
      //now a is hessenberg and b triangular, we can use hgeqz
      std::size_t n = height(a);
      container::table<type_t> beta(of_size(n, 1));
      NT2_LAPACK_VERIFY(nt2::hgeqz('S', 'V', 'V'
                                  , 1, n
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(alpha)
                                  , boost::proto::value(beta)
                                  , boost::proto::value(q)
                                  , boost::proto::value(z)));
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
      assign_swap(boost::proto::child_c<4>(a1), alpha);
      boost::proto::child_c<4>(a1) /= beta;
    }
    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, lambda] = qz(a, b, option)
    // returns the qz matrix
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const& //3 inputs
              , boost::mpl::long_<7> const& //7 outputs
              ) const
    {
      eval3_7(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    BOOST_FORCEINLINE
    void eval3_7 ( A0& a0, A1& a1,  policy<nt2::ext::lambda_> const &) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, z, boost::proto::child_c<3>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<6>(a1));
      container::table<type_t> beta(of_size(height(a), 1));
      tie(a, b, q, z, v, w, alpha, beta) = nt2::qz(a, b);
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
      assign_swap(boost::proto::child_c<4>(a1), v);
      assign_swap(boost::proto::child_c<5>(a1), w);
      assign_swap(boost::proto::child_c<6>(a1), alpha);
      boost::proto::child_c<6>(a1) /= beta;
    }




    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, alpha/v, beta/w] = qz(a, b, option) // option can be real_/cmplx_
    // option can be alphabeta_ or eigs_
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const& //3 inputs
              , boost::mpl::long_<4> const& //4 outputs
              ) const
    {
      eval3_4(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }


    BOOST_FORCEINLINE
      void eval3_4 ( A0& a0, A1& a1,  policy<nt2::ext::real_> const &) const
    {
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                        "all input matrix elements are to be real to support"
                        "'real_' option with complex type input");
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<1>(a0)),
                        "all input matrix elements are to be real to support"
                       "'real_' option with complex type input");
       NT2_AS_TERMINAL_INOUT(r_semantic, a, real(boost::proto::child_c<0>(a0))
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(r_semantic, b, real(boost::proto::child_c<1>(a0))
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, z, boost::proto::child_c<3>(a1));
       tie(a, b, q, z) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
    }

    BOOST_FORCEINLINE
    void eval3_4 ( A0& a0, A1& a1,  policy<nt2::ext::cmplx_> const &) const
    {
      NT2_AS_TERMINAL_INOUT(c_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(c_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, z, boost::proto::child_c<3>(a1));
      tie(a, b, q, z) = qz(a, b);
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
    }

    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, alpha/v, beta/w] = qz(a, b, option)
    // option can be alphabeta_ or eigs_
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const& //3 inputs
              , boost::mpl::long_<6> const& //6 outputs
              ) const
    {
      eval3_6(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    BOOST_FORCEINLINE
    void eval3_6 ( A0& a0, A1& a1,  policy<nt2::ext::alphabeta_> const &) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, z, boost::proto::child_c<3>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<4>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, beta, boost::proto::child_c<5>(a1));
      tie(a, b, q, z) = nt2::hess(a, b);
      //now a is hessenberg and b triangular, we can use hgeqz
      std::size_t n = height(a);
      NT2_LAPACK_VERIFY(nt2::hgeqz('S', 'V', 'V'
                                  , 1, n
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(alpha)
                                  , boost::proto::value(beta)
                                  , boost::proto::value(q)
                                  , boost::proto::value(z)));
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
      assign_swap(boost::proto::child_c<4>(a1), alpha);
      assign_swap(boost::proto::child_c<5>(a1), beta);
    }

    BOOST_FORCEINLINE
    void eval3_6 ( A0& a0, A1& a1,  policy<nt2::ext::eigs_> const &) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, z, boost::proto::child_c<3>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
      std::size_t n = height(a);
      tie(a, b, q, z) = nt2::hess(a, b);
      //now a is hessenberg and b triangular, we can use hgeqz
      container::table<ctype_t> alpha(of_size(n, 1));
      container::table<type_t> beta(of_size(n, 1));
      NT2_LAPACK_VERIFY(nt2::hgeqz('S', 'V', 'V'
                                  , 1, n
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(alpha)
                                  , boost::proto::value(beta)
                                  , boost::proto::value(q)
                                  , boost::proto::value(z)));

      container::table<type_t> vl(of_size(n, n));
      container::table<type_t> vr(of_size(n, n));
      vl = q;
      vr = z;
      NT2_LAPACK_VERIFY(nt2::tgevc('B', 'B'
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(vl)
                                  , boost::proto::value(vr)));
      combine(vl, alpha, v, iscplx_t());
      combine(vr, alpha, w, iscplx_t());
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
      assign_swap(boost::proto::child_c<4>(a1), v);
      assign_swap(boost::proto::child_c<5>(a1), w);
    }

    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, alpha/v, beta/w] = qz(a, b, option1, option2)
    // option1 can be alphabeta_ or eigs_,  option2 real_, cmplx_
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<4> const& //4 inputs
              , boost::mpl::long_<6> const& //6 outputs
              ) const
    {
      eval4_6(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0))
             , boost::proto::value(boost::proto::child_c<3>(a0)));
    }

    BOOST_FORCEINLINE
    void eval4_6( A0& a0, A1& a1
                , nt2::policy<ext::alphabeta_> const &
                , nt2::policy<ext::real_> const & ) const
    {
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                        "all input matrix elements are to be real to support"
                        "'real_' option with complex type input");
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<1>(a0)),
                        "all input matrix elements are to be real to support"
                       "'real_' option with complex type input");
       NT2_AS_TERMINAL_INOUT(r_semantic, a, real(boost::proto::child_c<0>(a0))
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(r_semantic, b, real(boost::proto::child_c<1>(a0))
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, z, boost::proto::child_c<3>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<4>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, beta, boost::proto::child_c<5>(a1));
       tie(a, b, q, z, alpha, beta) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
       assign_swap(boost::proto::child_c<4>(a1), alpha);
       assign_swap(boost::proto::child_c<5>(a1), beta);
    }

    BOOST_FORCEINLINE
    void eval4_6( A0& a0, A1& a1
                , nt2::policy<ext::eigs_> const &
                , nt2::policy<ext::real_> const & ) const
    {
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                        "all input matrix elements are to be real to support"
                        "'real_' option with complex type input");
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<1>(a0)),
                        "all input matrix elements are to be real to support"
                       "'real_' option with complex type input");
       NT2_AS_TERMINAL_INOUT(r_semantic, a, real(boost::proto::child_c<0>(a0))
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(r_semantic, b, real(boost::proto::child_c<1>(a0))
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, z, boost::proto::child_c<3>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
       tie(a, b, q, z, v, w) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
       assign_swap(boost::proto::child_c<4>(a1), v);
       assign_swap(boost::proto::child_c<5>(a1), w);
    }

    BOOST_FORCEINLINE
    void eval4_6( A0& a0, A1& a1
                , nt2::policy<ext::alphabeta_> const &
                , nt2::policy<ext::cmplx_> const & ) const
    {
       NT2_AS_TERMINAL_INOUT(c_semantic, a, boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(c_semantic, b, boost::proto::child_c<1>(a0)
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, z, boost::proto::child_c<3>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<4>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, beta, boost::proto::child_c<5>(a1));
       tie(a, b, q, z, alpha, beta) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
       assign_swap(boost::proto::child_c<4>(a1), alpha);
       assign_swap(boost::proto::child_c<5>(a1), beta);
    }

    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, v, w, alpha, beta] = qz(a, b)
    // option can be alphabeta_ or eigs_
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& //2 inputs
              , boost::mpl::long_<8> const& //8 outputs
              ) const
    {
      eval2_8(a0, a1);
    }
    BOOST_FORCEINLINE
    void eval2_8 ( A0& a0, A1& a1) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, q, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, z, boost::proto::child_c<3>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
      NT2_AS_TERMINAL_OUT(c_semantic, alpha, boost::proto::child_c<6>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, beta,  boost::proto::child_c<7>(a1));
      tie(a, b, q, z) = nt2::hess(a, b);
      //now a is hessenberg and b triangular, we can use hgeqz
      std::size_t n = height(a);
      alpha.resize(of_size(n, 1));
      beta.resize(of_size(n, 1));
      NT2_LAPACK_VERIFY(nt2::hgeqz('S', 'V', 'V'
                                  , 1, n
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(alpha)
                                  , boost::proto::value(beta)
                                  , boost::proto::value(q)
                                  , boost::proto::value(z)));
      container::table<type_t> vl(of_size(n, n));
      container::table<type_t> vr(of_size(n, n));
      vl = q;
      vr = z;
      NT2_LAPACK_VERIFY(nt2::tgevc('B', 'B'
                                  , boost::proto::value(a)
                                  , boost::proto::value(b)
                                  , boost::proto::value(vl)
                                  , boost::proto::value(vr)));
      combine(vl, alpha, v, iscplx_t());
      combine(vr, alpha, w, iscplx_t());
      assign_swap(boost::proto::child_c<0>(a1), a);
      assign_swap(boost::proto::child_c<1>(a1), b);
      assign_swap(boost::proto::child_c<2>(a1), q);
      assign_swap(boost::proto::child_c<3>(a1), z);
      assign_swap(boost::proto::child_c<4>(a1), v);
      assign_swap(boost::proto::child_c<5>(a1), w);
      assign_swap(boost::proto::child_c<6>(a1), alpha);
      assign_swap(boost::proto::child_c<7>(a1), beta);
    }

    template < class IN1, class IN2, class OUT>
    void combine(const IN1&in1 , const IN2&
           , const OUT&out , boost::mpl::true_ const &) const
    {
      out = in1;
    }
    template < class IN1, class IN2, class OUT>
    void combine(const IN1& in1, const IN2& in2
           , const OUT& out, boost::mpl::false_ const &) const
    {
      combine_vects(in1, imag(in2), out);
    }

    //==========================================================================
    /// INTERNAL ONLY - [aa, bb, q, z, v, w, alpha, beta] = qz(a, b, option) //option can be real_ or cmplx_
    // option can be alphabeta_ or eigs_
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const& //3 inputs
              , boost::mpl::long_<8> const& //8 outputs
              ) const
    {
      eval3_8(a0, a1, boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    BOOST_FORCEINLINE
    void eval3_8 ( A0& a0, A1& a1, nt2::policy<ext::real_> const &) const
    {
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                        "all input matrix elements are to be real to support"
                        "'real_' option with complex type input");
       BOOST_ASSERT_MSG(isreal(boost::proto::child_c<1>(a0)),
                        "all input matrix elements are to be real to support"
                       "'real_' option with complex type input");
       NT2_AS_TERMINAL_INOUT(r_semantic, a, real(boost::proto::child_c<0>(a0))
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(r_semantic, b, real(boost::proto::child_c<1>(a0))
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(r_semantic, z, boost::proto::child_c<3>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
       tie(a, b, q, z, v, w) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
       assign_swap(boost::proto::child_c<4>(a1), v);
       assign_swap(boost::proto::child_c<5>(a1), w);
    }

    BOOST_FORCEINLINE
    void eval3_8 ( A0& a0, A1& a1, nt2::policy<ext::cmplx_> const &) const
    {
       NT2_AS_TERMINAL_INOUT(c_semantic, a, real(boost::proto::child_c<0>(a0))
                            , boost::proto::child_c<0>(a1));
       NT2_AS_TERMINAL_INOUT(c_semantic, b, real(boost::proto::child_c<1>(a0))
                            , boost::proto::child_c<1>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, q, boost::proto::child_c<2>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, z, boost::proto::child_c<3>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, v, boost::proto::child_c<4>(a1));
       NT2_AS_TERMINAL_OUT(c_semantic, w, boost::proto::child_c<5>(a1));
       tie(a, b, q, z, v, w) = qz(a, b);
       assign_swap(boost::proto::child_c<0>(a1), a);
       assign_swap(boost::proto::child_c<1>(a1), b);
       assign_swap(boost::proto::child_c<2>(a1), q);
       assign_swap(boost::proto::child_c<3>(a1), z);
       assign_swap(boost::proto::child_c<4>(a1), v);
       assign_swap(boost::proto::child_c<5>(a1), w);
    }
  };


} }

#endif
