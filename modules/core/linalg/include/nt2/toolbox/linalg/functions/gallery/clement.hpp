/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CLEMENT_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CLEMENT_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/clement.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>

namespace nt2 { namespace ext
{ //1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clement_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::clement_
      , container::domain
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
        make_expr<nt2::tag::clement_, container::domain>
        ( size_t(a0)
          , size_t(a1)
          , T()
          , boxify(sizee)
          );
    }
  };

 //1bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clement_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::clement_
      , container::domain
      , size_t
      , size_t
      , T
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::clement_, container::domain>
        ( size_t(a0)
          , size_t(0)
          , T()
          , boxify(sizee)
          );
    }
  };

  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clement_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::clement_
      , container::domain
      , size_t
      , size_t
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::clement_, container::domain>
        ( size_t(a0)
          , size_t(a1)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };

  //2bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clement_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::clement_
      , container::domain
      , size_t
      , size_t
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::clement_, container::domain>
        ( size_t(a0)
          , size_t(0)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::clement_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,2>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                        v_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  nt2::minusone(boost::proto::child_c<0>(in));
      size_t k =  boost::proto::child_c<1>(in);
      BOOST_AUTO_TPL(z, nt2::_(v_type(1), v_type(n)));
      BOOST_AUTO_TPL(x, nt2::_(v_type(n), v_type(-1), v_type(1)));
      out.resize(of_size(n, n));
      if (k == 0)
      {
        out = nt2::from_diag(x, -1)+nt2::from_diag(z, 1);
      }
      else
      {
        BOOST_AUTO_TPL(y, nt2::sqrt(x*z));
        out = nt2::from_diag(y, -1)+nt2::from_diag(y, 1);
      }
      return out;
    }
  };
} }

#endif
