/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_INVHESS_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_INVHESS_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/invhess.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/uminus.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhess_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           ( nt2::invhess(n, nt2::meta::as_<double>())
                           )
                          )

      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhess_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> > )
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type v_t;
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, T const& t),
                           ( boost::proto::make_expr<nt2::tag::invhess_, container::domain>
                             ( boost::cref(nt2::_(v_t(1), v_t(n)))
                             , boost::cref(-nt2::_(v_t(1), v_t(n-1)))
                             , boxify(of_size(n, n))
                             )
                           )
                          )

      };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhess_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {

    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           ( boost::proto::make_expr<nt2::tag::invhess_, container::domain>
                             ( boost::cref(a0)
                             , boost::cref(a1)
                             , boxify(of_size(numel(a0), numel(a0)))
                             )
                           )
                          )

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhess_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {

    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                           ( boost::proto::make_expr<nt2::tag::invhess_, container::domain>
                             ( boost::cref(a0)
                             , boost::cref(-a0(nt2::_(1, numel(a0)-1)))
                             , boxify(of_size(numel(a0), numel(a0)))
                             )
                           )
                          )
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::invhess_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(x, nt2::rowvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL(y, nt2::colvect(boost::proto::child_c<1>(in)));
      size_t n =  numel(x);
      out.resize(nt2::of_size(n, n));
      out = nt2::repmat(x, n, 1);
      for (size_t j = 2; j <= n; ++j)
        out(nt2::_(1, j-1),j) = y(nt2::_(1, j-1));
      return out;
    }
  };

} }

#endif
