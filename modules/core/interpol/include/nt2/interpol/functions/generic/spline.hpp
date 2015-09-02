//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_SPLINE_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_SPLINE_HPP_INCLUDED

#include <nt2/interpol/functions/spline.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/erase.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/globalnone.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/lastnonsingleton.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/ppval.hpp>
#include <nt2/include/functions/pwch.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/interpol/functions/details/extrapol.hpp>



#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/assert.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/mpl/bool.hpp>
namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( spline_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( spline_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & , const A0 & , const A0 & , const A0 & ) const
    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::spline_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef typename child0::value_type                                   x_type;
    typedef typename child1::value_type                               value_type;
    typedef typename meta::as_integer<x_type>::type                   index_type;
    typedef table<x_type>                                                 xtab_t;
    typedef table<value_type>                                             vtab_t;
    typedef table<index_type>                                             itab_t;
    typedef A0&                                                      result_type;
    typedef typename meta::is_complex<value_type>::type               is_cmplx_t;

    result_type operator()(A0& yi, A1& inputs) const
    {
      BOOST_ASSERT_MSG(!is_cmplx_t::value, "Interpolation requires real abscissae.");
      const child0 & xx   =  boost::proto::child_c<0>(inputs);
      const child1 & yy   =  boost::proto::child_c<1>(inputs);
      table<x_type> x = xx;
      table<value_type> y = yy;
      table<value_type> endslopes;
      size_t yd;
      check(x, y,  endslopes, yd);
      auto sizey = y.extent();
      sizey[lastnonsingleton(y)-1] = 1;
      const child2 & xi  =  boost::proto::child_c<2>(inputs);
      bool extrap = false;
      value_type extrapval = Nan<value_type>();
      choices(inputs, extrap, extrapval, N1());
      xtab_t dx = diff(x);
      vtab_t divdif = diff(y,1,2);
      divdif /= expand_to(dx, size(divdif));
      size_t n = numel(x);
      if (n==2u)
      {
        if (isempty(endslopes)) // the interpolant is a straight line
        {
          ppval<value_type> pp(x,cath(divdif, y(_,1)), sizey);
          yi =pp.eval(xi);
        }
        else         // the interpolant is the cubic Hermite polynomial
        {
          ppval<value_type> pp = pwch(x,y,endslopes,dx,divdif);
          pp.setdim(sizey);
          yi =pp.eval(xi);
        }
      }
      else if  (n==3u && isempty(endslopes)) //the interpolant is a parabola
      {
        y(_,_(2, 3))=divdif;
        y(_,3)=trans(diff(trans(divdif)))/(x(3)-x(1));
        y(_,2)=y(_,2)-y(_,3)*dx(1);
        ppval<value_type> pp(x(_(1, 2, 3)),y(_,_(3, -1, 1)),sizey);
        yi =pp.eval(xi);
      }
      else // set up the tridiagonal linear system
      {
        auto dd = ones(yd, 1, meta::as_<size_t>());
        x_type x31, xn;
        xtab_t b=zeros(yd,n, meta::as_<value_type>());
        auto inds = _(1u, n-2);
        auto indsp1 = oneplus(inds);
        b(_,indsp1)=Three<x_type>()*(dx(dd,indsp1)*divdif(_,inds)+dx(dd,inds)*divdif(_,indsp1));
        if (isempty(endslopes))
        {
          x31 = x(3)-x(1);
          xn = x(n)-x(n-2);
          b(_,1) = ((dx(1)+Two<x_type>()*x31)*dx(2)*divdif(_,1)+sqr(dx(1))*divdif(_,2))/x31;
          b(_,n) = (sqr(dx(n-1))*divdif(_,n-2)+(Two<x_type>()*xn+dx(n-1))*dx(n-2)*divdif(_,n-1))/xn;
        }
        else
        {
          x31 = Zero<x_type>();
          xn = x31;
          auto _1n = cons<size_t>(1, n);
          auto _2nm2 = cons<size_t>(2, n-2);
          b(_, _1n) = dx(dd, _2nm2)*endslopes;
        }
        auto dxt = dx(_);
        auto sub = catv(x31, dxt(inds));
        auto dia = catv(catv(dxt(2), Two<x_type>()*(dxt(indsp1)+dxt(inds))), dxt(n-2));
        auto sup = catv(dxt(indsp1), xn);

        xtab_t c = from_diag(sub,-1) + from_diag(dia)+  from_diag(sup,+1);
        table<x_type> s =  trans(linsolve(trans(c), trans(b))); // at least replace by mrdivide when available and by a proper tridiagonal solver when available
        ppval<value_type> pp = pwch(x,y,s,dx,divdif);
        pp.setdim(sizey);
        yi =pp.eval(xi);
      }
//       if (!extrap)
//       {
//         auto sizee = of_size(height(xi), width(xi), width(y)); // this is incorrect if xi0 is properly _3D
//         details::extrapol(yi, x, xi, extrapval, sizee);
//       }
      return yi;
    }
  private :
    static void choices(const A1&, bool &,  value_type&
                       , boost::mpl::long_<3> const &)
    { }
    static void choices(const A1& inputs, bool & extrap
                       , value_type& extrapval, boost::mpl::long_<4> const &)
    {
      typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
      typedef typename meta::scalar_of<child3>::type                    cref_param_type;
      typedef typename meta::strip<cref_param_type>::type                    param_type;
      get(inputs, extrap, extrapval, param_type());
    }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
    {
      extrap =  boost::proto::child_c<3>(inputs);
    }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
    {
      extrapval =  boost::proto::child_c<3>(inputs);
    }


    //   [x,y,sizey] = chckxy(xin,yin, sizey, x, y) checks the data sites x and corresponding data
    //   values y, making certain that there are exactly as many sites as values,
    //   that no two data sites are the same, removing any data points that involve
    //   nans, reordering the sites if necessary to ensure that x is a strictly
    //   increasing row vector and reordering the data values correspondingly,
    //   and reshaping y if necessary to make sure that it is a matrix, with y(:,j)
    //   the data value corresponding to the data site x(j), and with sizey the
    //   actual dimensions of the given values.
    //   this call to chckxy is suitable for spline.
    //
    //   [x,y,sizey,endslopes] = chckxy(x,y) also considers the possibility that

    //   if there are, then the first and the last data value are removed from y
    //   and returned separately as endslopes. otherwise, an empty endslopes is
    //   returned.  this call to chckxy is suitable for spline.
    //    template < class Xin, class Yin,  class Xout, class Yout>

    template < class ES >
    BOOST_FORCEINLINE
      static void check(xtab_t & x, vtab_t& y, ES & endslopes, size_t & yd)
    {
      BOOST_ASSERT_MSG(isvector(x), "x is not a vector");
      BOOST_ASSERT_MSG(globalnone(is_nan(x)), "x contains Nans");
      BOOST_ASSERT_MSG(numel(x) >  1, "Interpolation requires at least two sample points in each dimension.");
      BOOST_ASSERT_MSG(issorted(x, 'a'), "for 'spline' interpolation x values must be sorted in ascending order");
      x =  rowvect(x);
      BOOST_ASSERT_MSG(globalnone(is_nan(y)), "y contains Nans");
      size_t yn = size(y, lastnonsingleton(y));
      yd =  numel(y)/yn;
      if (!iscolumn(y))
      {
        y =  reshape(y, yd, yn);
      }
      else
      {
        y =  rowvect(y);

      }
      BOOST_ASSERT_MSG((numel(x) == width(y) ) ||(numel(x)+2u == width(y) )
                      , "The grid vectors do not define a grid of points that match the given values.");
      if (size(y, lastnonsingleton(y)) == numel(x))
      {
        endslopes = zeros(1, 0, meta::as_<value_type>());
      }
      else
      {
        size_t n =  numel(x);
        auto inds = cons<size_t>(of_size_<1, 2>(), 1, n+2);
        NT2_DISPLAY(inds);
        endslopes = y(_,inds);
        y(_,inds) = _();
      }
    }
  };
} }


#endif

