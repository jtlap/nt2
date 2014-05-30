//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SCHUR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SCHUR_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/geesx.hpp>
#include <nt2/include/functions/geesx_no_w.hpp>
#include <nt2/include/functions/geesx1.hpp>
#include <nt2/include/functions/geesxw.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/linalg/options.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //SCHUR Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::schur_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::schur_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };


  //============================================================================
  //SCHUR
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::schur_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::schur_
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
    typedef typename nt2::meta::as_complex<type_t>::type                ctype_t;
    typedef typename nt2::meta::as_real<type_t>::type                   rtype_t;
    typedef rtype_t T;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }
  private:
    //==========================================================================
    /// INTERNAL ONLY - T = SCHUR(A)
    // returns the schur matrix
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx(boost::proto::value( boost::proto::child_c<0>(a1)), type_t(0));
    }

    //==========================================================================
    /// INTERNAL ONLY - T = SCHUR(A, cmplx_/real_)
    // returns T in its real or complex form or only the eigenvalues
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
       eval1_2(a0, a1,
               boost::proto::value(boost::proto::child_c<1>(a0)));
    }


    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::real_>
                 ) const
    {
      BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                       "all input matrix element are to be real to support 'real_' option with complex type input");
      // Here one cannot be sure that boost::proto::child_c<0>(a1) is real typed
      // as the 'real'schur decomposition can be put in a complex table
      // so we cannot pass it to geesx that needs a real table
      nt2::container::table<rtype_t> t = real(boost::proto::child_c<0>(a0));
      nt2::geesx(boost::proto::value(t), rtype_t(0));
      boost::proto::child_c<0>(a1) = t;
    }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::eigs_>
                 ) const
    {
      nt2::container::table<type_t> t = boost::proto::child_c<0>(a0);
      nt2::geesxw(boost::proto::value(t),
                  boost::proto::value( boost::proto::child_c<0>(a1)));
   }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::cmplx_>
                 ) const
    {
      typedef typename meta::is_complex<type_t>::type is_cmplx_t;
      eval1_2c(a0, a1, is_cmplx_t());
    }

    BOOST_FORCEINLINE
    void eval1_2c ( A0& a0, A1& a1
                 , boost::mpl::false_
                 ) const
    {
      // Here boost::proto::child_c<0>(a0) is real and geesx has to receive a complex table
      nt2::container::table<ctype_t> t = boost::proto::child_c<0>(a0);
      nt2::geesx(boost::proto::value(t), ctype_t(0));
      boost::proto::child_c<0>(a1) = t;
    }

    BOOST_FORCEINLINE
    void eval1_2c ( A0& a0, A1& a1
                 , boost::mpl::true_
                 ) const
    {
      // Here  boost::proto::child_c<0>(a0) is complex
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx(boost::proto::child_c<0>(a1), ctype_t(0));
    }

    //==========================================================================
    /// INTERNAL ONLY - [T, U]= SCHUR(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      size_t n =   height(boost::proto::child_c<0>(a0));
      boost::proto::child_c<1>(a1).resize(of_size(n, n));
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx_no_w( boost::proto::value( boost::proto::child_c<0>(a1))
                     , boost::proto::value( boost::proto::child_c<1>(a1))
                     );
    }

    //==========================================================================
    /// INTERNAL ONLY - [T, U]= SCHUR(A, sort_/cmplx_/real_ )
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2( a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));

    }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::real_>
                 ) const
    {
      BOOST_ASSERT_MSG(isreal(boost::proto::child_c<0>(a0)),
                       "all input matrix element are to be real to support 'real_' option with complex type input");
      nt2::container::table<rtype_t> t = real(boost::proto::child_c<0>(a0));
      size_t n = nt2::height(t);
      nt2::container::table<rtype_t>  u;
      u.resize(of_size(n, n));
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx_no_w( boost::proto::value(t)
                     , boost::proto::value(u)
                     );
       boost::proto::child_c<0>(a1) = t;
       boost::proto::child_c<1>(a1) = u;
    }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::cmplx_>
                 ) const
    {
      nt2::container::table<ctype_t> t = boost::proto::child_c<0>(a0);
      size_t n = nt2::height(t);
      nt2::container::table<ctype_t>  u;
      u.resize(of_size(n, n));
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx_no_w( boost::proto::value(t)
                     , boost::proto::value(u)
                     );
      boost::proto::child_c<0>(a1) = t;
      boost::proto::child_c<1>(a1) = u;
    }

    //==========================================================================
    /// INTERNAL ONLY - [T, U, W]= SCHUR(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      size_t n =   height(boost::proto::child_c<0>(a0));
      boost::proto::child_c<1>(a1).resize(of_size(n, n));
      boost::proto::child_c<2>(a1).resize(of_size(n, 1));
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      nt2::geesx( boost::proto::value( boost::proto::child_c<0>(a1))
                , boost::proto::value( boost::proto::child_c<2>(a1))
                , boost::proto::value( boost::proto::child_c<1>(a1))
                );

    }
  };


} }

#endif


