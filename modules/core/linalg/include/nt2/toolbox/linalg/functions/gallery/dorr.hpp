//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_DORR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_DORR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/dorr.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/include/functions/ifloor.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dorr_
                                          , container::domain
                                          , A0 const&
                                          , double
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
     double d = 0.01;
     return  boost::proto::
        make_expr<nt2::tag::dorr_, container::domain>
        ( boost::cref(a0)
          , boost::cref(d)
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dorr_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::dorr_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (target_ < scalar_<floating_<A1> > > )
                            )
  {
    typedef typename A1::type value_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dorr_
                                          , container::domain
                                          , A0 const&
                                          , value_t
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      value_t d = value_t(0.01);
      return  boost::proto::
        make_expr<nt2::tag::dorr_, container::domain>
        ( boost::cref(a0)
          , d
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> > )
                              (target_ < scalar_<floating_<A2> > > )
                            )
  {
    typedef typename A2::type value_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::dorr_
                                          , container::domain
                                          , A0 const&
                                          , value_t
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      value_t d = value_t(a1);
      return  boost::proto::
        make_expr<nt2::tag::dorr_, container::domain>
        ( boost::cref(a0)
          , d
          , boxify(sizee)
          );
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::dorr_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          schild0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       child1;
    typedef typename schild0::value_type                                 value_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      size_t n = boost::proto::child_c<0>(a0);
      value_t theta =   boost::proto::child_c<1>(a0);
      compute(n, theta, a1, N1());
    }

  private:
    BOOST_FORCEINLINE
    void compute(const size_t & n, const value_t & theta, A1& a1,
                 boost::mpl::long_<3> const&) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       c_t;
      typedef typename boost::proto::result_of::child_c<A1&,1>::type       d_t;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type       e_t;
      c_t & c = boost::proto::child_c<0>(a1);
      c.resize(nt2::of_size(n,1));
      d_t & d = boost::proto::child_c<1>(a1);
      d.resize(nt2::of_size(n,1));
      e_t & e= boost::proto::child_c<2>(a1);
      e.resize(nt2::of_size(n,1));
      doit(n, theta, c, d, e);
    }

    BOOST_FORCEINLINE
    void compute(const size_t & n, const value_t & theta, A1 & a1,
                boost::mpl::long_<1> const&) const
    {
      nt2::table<value_t> c(nt2::of_size(n,1));
      nt2::table<value_t> d(nt2::of_size(n,1));
      nt2::table<value_t> e(nt2::of_size(n,1));
      doit(n, theta, c, d, e);
      boost::proto::child_c<0>(a1) = nt2::tridiag(c, d, e);
    }

    template < class C, class D,  class E> BOOST_FORCEINLINE
    void doit(const size_t & n, const value_t & theta, C & c, D&d, E& e) const
    {
      value_t np1 = nt2::oneplus(value_t(n));
      value_t h = nt2::rec(np1);
      size_t m = ifloor(np1*nt2::Half<value_t>());
      value_t term = -theta/nt2::sqr(h);
      c = nt2::zeros(n, 1, meta::as_<value_t>());
      d = nt2::zeros(n, 1, meta::as_<value_t>());
      e = nt2::zeros(n, 1, meta::as_<value_t>());
      BOOST_AUTO_TPL(p, (nt2::repnum(Half<value_t>(), n, 1)-nt2::colvect(_(value_t(1), value_t(n))*h))/h);
      c(_(1, m)) = nt2::repnum(term, m, 1);
      e(_(1, m)) = c(_(1, m)) - p(_(1, m));
      d(_(1, m)) = -(c(_(1, m)) + e(_(1, m)));
      e(_(m+1, n)) = nt2::repnum(term,n-m, 1);
      c(_(m+1, n)) = e(_(m+1, n)) + p(_(m+1, n));
      d(_(m+1, n)) = -(c(_(m+1, n)) + e(_(m+1, n)));
      c = c(_(2, n));
      e.resize(of_size(n-1, 1));
    }

  };
} }

#endif
// if isempty(theta), theta = 0.01; cast(theta,classname); end
