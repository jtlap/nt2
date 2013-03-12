//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_KMS_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_KMS_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/kms.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
    )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& rho),
                           (boost::proto::
                            make_expr<nt2::tag::kms_, container::domain>
                            ( rho
                            , boxify(nt2::of_size(size_t(n), size_t(n)))
                            )
                           )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kms_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const& rho, T  const& t),
                           (boost::proto::
                            make_expr<nt2::tag::kms_, container::domain>
                            ( value_t(rho)
                            , boxify(nt2::of_size(size_t(n), size_t(n)))
                            )
                           )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::kms_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef typename  meta::is_complex<value_t>::type                      iscplx_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(siz,boost::proto::value( boost::proto::child_c<1>(in)));
      value_t rho =  boost::proto::child_c<0>(in);
      size_t n = siz[0];
      out.resize(siz);
      finalize(out, n, rho, iscplx_t());

      return out;
    }
  private :
    static BOOST_FORCEINLINE void finalize(A0& out, const size_t & n, const value_t & rho, const boost::mpl::false_ &)
    {
      out = nt2::pow(rho, nt2::abs(nt2::rif(n, meta::as_<value_t>())-cif(n, meta::as_<value_t>())));
    }
    static BOOST_FORCEINLINE void finalize(A0& out, const size_t & n, const value_t & rho, const boost::mpl::true_ &)
    {
      out = pow(rho, nt2::abs(nt2::rif(n, meta::as_<value_t>())-nt2::cif(n, meta::as_<value_t>())));
      out = whereij(nt2::functor<nt2::tag::is_less_>(), nt2::conj(out), out); //nt2::conj(nt2::tril(out,-1)) + nt2::triu(out);
    }

  };
} }

#endif
