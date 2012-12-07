/*******************************************************************************
 *         Copyright 2003-2012 LASME UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CIRCUL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FUNCTIONS_GALLERY_CIRCUL_HPP_INCLUDED
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/toeplitz.hpp>

namespace nt2{ namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef typename nt2::meta::call<nt2::tag::colon_(A0, A0)>::type C;
    typedef typename boost::proto::result_of::make_expr< nt2::tag::circul_
      , container::domain
      , C const&, box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {

      _2D sizee; sizee[0] = a0; sizee[1] = a0;
      C v = nt2::_(A0(1), a0);
      return  boost::proto::make_expr<nt2::tag::circul_, container::domain>
        ( boost::cref(v), boxify(sizee));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename T::type value_type;
    typedef typename nt2::meta::call < nt2::tag::colon_(value_type, value_type)>::type C;
    typedef typename boost::proto::result_of::make_expr< nt2::tag::circul_
      , container::domain
      , C const &,
      box<_2D> >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,T const& ) const
    {
      _2D sizee; sizee[0] = a0; sizee[1] = a0;
       typedef typename meta::call < tag::colon_(value_type, value_type) > ::type C;

       C v = nt2::_(value_type(1), value_type(a0));

     return  boost::proto::make_expr<nt2::tag::circul_, container::domain>
        ( boost::cref(v), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::circul_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain >))
                            )
  {
    typedef typename  boost::proto::result_of::make_expr< nt2::tag::circul_
      , container::domain
      , A0 const &, box<_2D>
      >::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee; sizee[0] = nt2::numel(a0); sizee[1] = nt2::numel(a0);
      return  boost::proto::make_expr<nt2::tag::circul_, nt2::container::domain>
        ( boost::cref(a0), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::circul_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      typedef typename A0::value_type value_type;
      out.resize(extent(in));
      BOOST_AUTO_TPL( v, nt2::rowvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL( idx, nt2::_(ptrdiff_t(nt2::numel(v)), ptrdiff_t(-1), ptrdiff_t(2)));
      BOOST_AUTO_TPL( vr, nt2::cath(v(1), v(1, idx)));
      out =  nt2::toeplitz(vr, v);
      return out;
    }
  };
} }


#endif
