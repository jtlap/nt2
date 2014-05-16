//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/hsev.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>


namespace nt2 { namespace ext
{
  //============================================================================
  //SYMEIG Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
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

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
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

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      return a0;
    }
  };


  //============================================================================
  //SYMEIG
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::symeig_
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
    typedef typename child0::value_type                                 ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type                   type_t;
    typedef type_t T;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      nt2::container::table<type_t>  w;
      nt2::container::table<ctype_t> v;
      char uplo =  'U';
      char jobz =  'N';
      eval(a0, a1, w, v, jobz, uplo, N0(), N1());
    }
  private:
    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A)
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::container::table<type_t>& w
              , nt2::container::table<ctype_t>& v
              , char jobz
              , char uplo
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_2(a0, a1, w, v, jobz, uplo, nt2::vector_);
    }
    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A, matrix_/vector_/'L'/'U')
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1
                , nt2::container::table<type_t>& w
                , nt2::container::table<ctype_t>& v
                , char jobz
                , char uplo
                , boost::mpl::long_<2> const&
                , boost::mpl::long_<1> const&
                ) const
    {
      eval1_2(a0, a1, w, v, jobz, uplo,
               boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    BOOST_FORCEINLINE
      void eval1_2 ( A0& a0, A1& a1
                   , nt2::container::table<type_t>& w
                   , nt2::container::table<ctype_t>& v
                   , char jobz
                   , char uplo
                   , nt2::policy<ext::vector_>
                   ) const
    {
      nt2::container::table<ctype_t> work = boost::proto::child_c<0>(a0);
      size_t h = nt2::height(work);
      boost::proto::child_c<0>(a1).resize(nt2::of_size(h, 1));
      nt2::hsev( boost::proto::value(work)
               , boost::proto::value(boost::proto::child_c<0>(a1))
               , jobz, uplo);
    }

    BOOST_FORCEINLINE
      void eval1_2 ( A0& a0, A1& a1
                   , nt2::container::table<type_t>& w
                   , nt2::container::table<ctype_t>& v
                   , char /*dummy*/
                   , char uplo
                   , nt2::policy<ext::matrix_>
                   ) const
    {
      nt2::container::table<ctype_t> work = boost::proto::child_c<0>(a0);
      size_t h = nt2::height(work);
      w.resize(nt2::of_size(h, 1));
      char jobz =  'N';
      nt2::hsev( boost::proto::value(work)
               , boost::proto::value(w)
               , jobz, uplo);
      boost::proto::child_c<0>(a1) = from_diag(w);
    }

    BOOST_FORCEINLINE
      void eval1_2 ( A0& a0, A1& a1
                   , nt2::container::table<type_t>& w
                   , nt2::container::table<ctype_t>& v
                   , char jobz
                   , char /*dummy*/
                   , char uplo
                   ) const
    {
      eval(a0, a1, w, v, jobz, uplo,
           boost::mpl::long_<1>(),
           boost::mpl::long_<1>()
          );
    }


    //==========================================================================
    /// INTERNAL ONLY - [W, V]= SYMEIG(A, matrix_/vector_/'L'/'U')
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::container::table<type_t>& w
              , nt2::container::table<ctype_t>& v
              , char /*dummy*/
              , char uplo
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      char jobz = 'V';
      eval2_2(a0, a1, w, v, jobz, uplo,
              boost::proto::value(boost::proto::child_c<1>(a0)));

    }

    //==========================================================================
    /// INTERNAL ONLY - [W, V]= SYMEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::container::table<type_t>& w
              , nt2::container::table<ctype_t>& v
              , char /*dummy*/
              , char uplo
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      char jobz = 'V';
      eval2_2(a0, a1, w, v, jobz, uplo, nt2::matrix_);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::container::table<type_t>& w
                 , nt2::container::table<ctype_t>& v
                 , char /*dummy*/
                 , char uplo
                 , nt2::policy<ext::matrix_>
                 ) const
    {
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a0);
      size_t h = nt2::height(boost::proto::child_c<1>(a1));
      w.resize(nt2::of_size(h, 1));
      char jobz =  'V';
      nt2::hsev( boost::proto::value(boost::proto::child_c<1>(a1))
               , boost::proto::value(w)
               , jobz, uplo);
      boost::proto::child_c<0>(a1) = from_diag(w);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::container::table<type_t>& /*w*/
                 , nt2::container::table<ctype_t>& v
                 , char /*dummy*/
                 , char uplo
                 , nt2::policy<ext::vector_>
                 ) const
    {
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a0);
      size_t h = nt2::height(boost::proto::child_c<1>(a1));
      boost::proto::child_c<0>(a1).resize(nt2::of_size(h, 1));
      char jobz =  'V';
      nt2::hsev( boost::proto::value(boost::proto::child_c<1>(a1))
               , boost::proto::value(boost::proto::child_c<0>(a1))
               , jobz, uplo);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::container::table<type_t>& w
                 , nt2::container::table<ctype_t>& v
                 , char /*dummy*/
                 , char /*dummy*/
                 , char uplo
                 ) const
    {
      boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a0);
      size_t h = nt2::height(boost::proto::child_c<1>(a1));
      w.resize(nt2::of_size(h, 1));
      char jobz =  'V';
      nt2::hsev( boost::proto::value(boost::proto::child_c<1>(a1))
               , boost::proto::value(w)
               , jobz, uplo);
      boost::proto::child_c<0>(a1) = from_diag(w);
    }

    //==========================================================================
    /// INTERNAL ONLY - [W, V]= SYMEIG(A, matrix_/vector_, 'L'/'U')
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::container::table<type_t>& w
              , nt2::container::table<ctype_t>& v
              , char /*dummy*/
              , char uplo
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      char jobz = 'V';
      eval2_2( a0, a1, w, v, jobz
             , boost::proto::value(boost::proto::child_c<2>(a0))
             , boost::proto::value(boost::proto::child_c<1>(a0))
             );

    }

    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A, matrix_/vector_, 'L'/'U')
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , nt2::container::table<type_t>& w
              , nt2::container::table<ctype_t>& v
              , char /*dummy*/
              , char uplo
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      char jobz = 'N';
      eval1_2( a0, a1, w, v, jobz
             , boost::proto::value(boost::proto::child_c<2>(a0))
             , boost::proto::value(boost::proto::child_c<1>(a0))
             );
    }
  };
} }

#endif


