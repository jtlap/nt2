/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CYCOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CYCOL_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/cycol.hpp>
#include <nt2/core/container/table/table.hpp>

#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/idivround.hpp>
#include <nt2/include/functions/idivceil.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cycol_
      , container::domain
      , size_t
      , size_t
      , size_t
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = a0; sizee[1] = a1;
      return  boost::proto::
        make_expr<nt2::tag::cycol_, container::domain>
        ( size_t(a0)
          , size_t(a1)
          , size_t(0)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cycol_
      , container::domain
      , A2 const&
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      _2D sizee;
      sizee[0] = a0; sizee[1] = a1;
      return  boost::proto::
        make_expr<nt2::tag::cycol_, container::domain>
        ( boost::cref(a2)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };

 //
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cycol_
      , container::domain
      , size_t
      , size_t
      , size_t
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
        make_expr<nt2::tag::cycol_, container::domain>
        ( size_t(a0)
          , size_t(a1)
          , size_t(0)
          , T()
          , boxify(sizee)
          );
    }
  };
 //
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::cycol_
      , container::domain
      , size_t
      , size_t
      , size_t
      , T
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::cycol_, container::domain>
        ( size_t(a0)
          , size_t(a1)
          , size_t(a2)
          , T()
          , boxify(sizee)
          );
    }
  };
 //////////////////////////////////////////////////////////////////////////////////////////

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::cycol_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                            result_type;
    typedef typename boost::proto::result_of::child_c<A1&,N::value-2>::type     p_type;
    typedef typename meta::strip<p_type>::type                               tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type>::type        t_type;
    typedef typename t_type::type                                                  v_t;
    typedef typename nt2::container::table<v_t>                                  tab_t;

    result_type operator()(A0& out, const A1& in) const
    {
      NT2_DISPLAY(type_id<v_t>());
      _2D sizee =boost::proto::value(boost::proto::child_c<N::value-1>(in));
      size_t m =  sizee[0];
      size_t n =  sizee[1];
      size_t k =  boost::proto::child_c<0>(in);
      out.resize(nt2::of_size(m, n));

      if(k == 0) k = nt2::max(nt2::idivround (n, size_t(4)), size_t(1));
      tab_t c = nt2::randn<v_t>(m, k);
      tab_t c1;
      for (size_t i=2;  i <= idivceil(n, k);  ++i)
      {
        c1 = nt2::cath(c, c(_,_(size_t(1), k)));
        c =  c1; // ALIASING
      }
      out = c(_, _(1, n-1));
      return out;
    }
  };
} }

#endif
