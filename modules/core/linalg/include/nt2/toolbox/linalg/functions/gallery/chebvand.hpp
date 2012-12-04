/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CHEBVAND_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CHEBVAND_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/chebvand.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  //1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A1 const &
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = a0;
      sizee[1] = a1;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };
  //1bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A1 const &
      , T
      , T
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             T const& tgt) const
    {
      _2D sizee;
      sizee[0] = a0;
      sizee[1] = a1;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , T()
          , T()
          , boxify(sizee)
          );
    }
  };

  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A0 const &
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = a0;
      sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a0)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };
  //2bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A0 const &
      , T
      , T
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& tgt) const
    {
      _2D sizee;
      sizee[0] = a0;
      sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a0)
          , tgt
          , tgt
          , boxify(sizee)
          );
    }
  };
  //3
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const&
      , size_t const&
      , A1 const&
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      _2D sizee;
      size_t n = numel(a1);
      sizee[0] = a0;
      sizee[1] = n;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(n)
          , boost::cref(a1)
          , boxify(sizee)
          );
    }
  };
  //4
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::chebvand_
                                          , container::domain
                                          , size_t const&
                                          , size_t const&
                                          , A0 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      size_t n = numel(a0);
      sizee[0] = n;
      sizee[1] = n;
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(n)
          , boost::cref(n)
          , boost::cref(a0)
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::chebvand_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,2>::type            p_type;
    typedef typename meta::strip<p_type>::type                             tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type>::type   tmp2_type;
    typedef typename details::is_target<tmp2_type>::type                    choice_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t m =  boost::proto::child_c<0>(in);
      size_t n =  boost::proto::child_c<1>(in);
      prepare(out, in, m, n, choice_type());
      return out;
    }
  private :
    static void prepare(A0& out, const A1 & in, size_t m, size_t n,boost::mpl::true_)
    {
      typedef typename A0::value_type                                   v_type;
      BOOST_AUTO_TPL(p, nt2::linspace(Zero<v_type>(), One<v_type>(), n));
      out.resize(nt2::of_size(m, n));
      compute(out, m, n, p);
    }
    static void prepare(A0& out, const A1 & in, size_t m, size_t n, boost::mpl::false_)
    {
      BOOST_AUTO_TPL(p, boost::proto::child_c<2>(in));
      out.resize(nt2::of_size(m, nt2::numel(p)));
      compute(out, m, n, p);
    }
    template < class P >
    static void compute(A0& c, size_t m, size_t n, const P& p)
    {
      typedef typename A0::value_type                                   v_type;
      BOOST_AUTO_TPL(rp, nt2::rowvect(p));
      c = ones(m,n,meta::as_<v_type>());
      if (n == 1) return;
      c(2, _) = rp;
      //      Use Chebyshev polynomial recurrence.
      for (size_t i = 3; i <= m; ++i){
        c(i, _) = nt2::Two<v_type>()*rp*c(i-1, _)-c(i-2, _);
      }
    }
  };
} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of chebvand.hpp
// /////////////////////////////////////////////////////////////////////////////
