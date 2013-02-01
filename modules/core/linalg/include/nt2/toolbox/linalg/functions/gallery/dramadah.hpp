/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_DRAMADAH_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_DRAMADAH_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/dramadah.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/table/table.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/toeplitz.hpp>

namespace nt2 { namespace ext
{
  //0
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dramadah_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          , meta::as_<double>
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      size_t k = 1;
      return  boost::proto::
        make_expr<nt2::tag::dramadah_, container::domain>
        ( boost::cref(a0)
          , k
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };
 //00
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dramadah_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          , T
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      size_t k = 1;
      return  boost::proto::
        make_expr<nt2::tag::dramadah_, container::domain>
        ( boost::cref(a0)
          , k
          , T()
          , boxify(sizee)
          );
    }
  };

//1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dramadah_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , meta::as_<double>
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::dramadah_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };
  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dramadah_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , T
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::dramadah_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , T()
          , boxify(sizee)
          );
    }

  };

///////////////////////////////////////////////////////////////////////////////////

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::dramadah_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    typedef typename A0::value_type                                         v_t;
    typedef typename nt2::container::table <v_t>                          tab_t;

    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      size_t k =  boost::proto::child_c<1>(in);
      if (n == 0)
      {
        out.resize(nt2::of_size(0, 1));
        return out;
      }
      out.resize(of_size(n, n));
      compute(out, n, k);
      return out;
    }
  private :
    static void compute(A0& out, size_t n,  size_t k)
    {
      if(k == 1)
      {
        // Toeplitz
        tab_t c = nt2::ones<v_t>(n,1);
        for(size_t i=2; i <= n; i+= 4)
        {
          size_t m = nt2::min(size_t(1),n-i);
          c(nt2::_(i,i+m)) = Zero<v_t>();
        }
        tab_t r = zeros<v_t>(n,1);
        r(1) = r(n >= 2 ? 2 : 1) = r(n >= 4 ? 4 : 1) = nt2::One<v_t>();
        out = nt2::toeplitz (c,r);
      }
      else if (k == 2)
      {
        // Upper triangular and Toeplitz
        tab_t c = nt2::zeros<v_t>(n,1);
        c(1) = 1;
        tab_t r =nt2::ones<v_t>(n,1);
        r(nt2::_(size_t(3),size_t(2),n)) = nt2::Zero<v_t>();
        out = nt2::toeplitz (c,r);
      }
      else
      {
        //  Lower Hessenberg.
        tab_t c = nt2::ones<v_t>(n,1);
        c(nt2::_(size_t(2), size_t(2), n)) = nt2::Zero<v_t>();
        tab_t d = nt2::zeros<v_t>(n,1);
        d(1) = d(2) = 1;
        out = nt2::toeplitz(c, d);
      }

    }

  };

} }

#endif
