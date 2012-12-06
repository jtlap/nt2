/*******************************************************************************
 *         Copyright 2003-2012 LASME UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CHOW_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CHOW_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/chow.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/toeplitz.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::result_of::make_expr< nt2::tag::chow_
      , container::domain
      , A0 const &, double, double, box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      return  boost::proto::make_expr<nt2::tag::chow_, container::domain>
        ( boost::cref(a0), 1.0, 0.0, boxify(sizee));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::result_of::make_expr< nt2::tag::chow_
      , container::domain
      , A0 const &, value_type, value_type, box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,T const& ) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      return  boost::proto::make_expr<nt2::tag::chow_, container::domain>
        ( boost::cref(a0), value_type(1), value_type(0), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> > )
                            )
  {
    typedef typename  boost::proto::result_of::make_expr< nt2::tag::chow_
      , container::domain
      , A0 const &, A1, A1, box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      return  boost::proto::make_expr<nt2::tag::chow_, container::domain>
        ( boost::cref(a0), boost::cref(a1), A1(0), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chow_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> >  )
                              (scalar_<unspecified_<A2> >  )
                            )
  {
    typedef typename A1::type value_type;
    typedef typename  boost::proto::result_of::make_expr< nt2::tag::chow_
      , container::domain
      , A0 const &, A1, A1, box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      return  boost::proto::make_expr<nt2::tag::chow_, container::domain>
        ( boost::cref(a0), boost::cref(a1), cref(a2), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::chow_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      typedef typename A0::value_type value_type;
      out.resize(extent(in));
      typedef typename meta::as_real<value_type>::type r_type;
      typedef typename meta::as_integer<r_type>::type i_type;
      size_t n =  boost::proto::child_c<0>(in);
      NT2_DISPLAY(n);
      value_type alpha =  boost::proto::child_c<1>(in);
      NT2_DISPLAY(alpha);
      value_type delta = boost::proto::child_c<2>(in);
      NT2_DISPLAY(delta);
      BOOST_AUTO_TPL(y2, nt2::zeros(1, n-2, meta::as_<value_type>()));
      NT2_DISPLAY(y2);
      BOOST_AUTO_TPL(y1, nt2::rowvect(nt2::cons(alpha, nt2::One<value_type>())));
      NT2_DISPLAY(y1);
      BOOST_AUTO_TPL(z2, nt2::cath(y1, y2));
      NT2_DISPLAY(z2);
      BOOST_AUTO_TPL(expo, nt2::_(i_type(1), i_type(n)));
      NT2_DISPLAY(expo);
      BOOST_AUTO_TPL(z1, nt2::pow(alpha, expo));
      NT2_DISPLAY(z1);
      container::table<value_type> q = nt2::toeplitz(z1,z2);
      NT2_DISPLAY(q);
      q = q+delta*nt2::eye(n, nt2::meta::as_<value_type>());
      NT2_DISPLAY(q);
      BOOST_AUTO_TPL(z3,  nt2::toeplitz(z1,z2)+delta*nt2::eye(n, nt2::meta::as_<value_type>()));
      NT2_DISPLAY(z3);
      return out = q;
    }
  };
} }


#endif
// function A = chow(n, alpha, delta, classname)
// %CHOW Chow matrix (singular Toeplitz lower Hessenberg matrix).
// %   A = GALLERY('CHOW',N,ALPHA,DELTA) returns A such that
// %      A = H(ALPHA) + DELTA*EYE, where H(i,j) = ALPHA^(i-j+1).
// %   H(ALPHA) has p = FLOOR(N/2) zero eigenvalues, the rest being
// %   4*ALPHA*COS( k*PI/(N+2) )^2, k=1:N-p.
// %   Defaults: ALPHA = 1, DELTA = 0.

// %   References:
// %   [1] T. S. Chow, A class of Hessenberg matrices with known eigenvalues
// %       and inverses, SIAM Review, 11 (1969), pp. 391-395.
// %   [2] G. Fairweather, On the eigenvalues and eigenvectors of a class of
// %       Hessenberg matrices, SIAM Review, 13 (1971), pp. 220-221.
// %   [3] I. Singh, G. Poole and T. Boullion, A class of Hessenberg matrices
// %       with known pseudoinverse and Drazin inverse, Math. Comp., 29 (1975),
// %       pp. 615-619.
// %
// %   Nicholas J. Higham
// %   Copyright 1984-2005 The MathWorks, Inc.
// %   $Revision: 1.10.4.1 $  $Date: 2005/11/18 14:14:45 $

// if isempty(alpha), alpha = ones(classname); end
// if isempty(delta), delta = zeros(classname); end

// A = toeplitz( alpha.^(1:n), [alpha 1 zeros(1,n-2,classname)] ) + ...
//               delta*eye(n,classname);
