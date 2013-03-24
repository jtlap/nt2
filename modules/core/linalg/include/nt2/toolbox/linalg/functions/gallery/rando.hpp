//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_RANDO_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_RANDO_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/rando.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/iceil.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type                                                    v_t;
    BOOST_DISPATCH_RETURNS(4, (A0 const& n, A1 const& m, A2 const& k, T const & t),
                           (nt2::rando(nt2::_(k == 1?v_t(0):v_t(-1),
                                              k == 2? v_t(k):v_t(1),
                                              v_t(1)), n, m))
                          )
      };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type                                                    v_t;
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const& m, T const & t),
                           (nt2::rando(nt2::_(T(0), T(1)), n, m))
                          )
      };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::rando_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t>                                               tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(x,boost::proto::child_c<0>(in));
      size_t n = boost::proto::child_c<1>(in);
      size_t m = boost::proto::child_c<2>(in);
      tab_t rnd = nt2::rand(n*m, 1, nt2::meta::as_<value_t>());
      value_t p = nt2::numel(x);
      out.resize(of_size(n, m));
      out(nt2::_) = x(nt2::iceil(rnd*p));
      return out;
    }
  };

}

//   meta::call<tag::rando_(const ptrdiff_t &, meta::as_<double> const &)>::type
//   rando(ptrdiff_t n)
//   {
//     return nt2::rando(n,  meta::as_<double>());
//   }
//   template<class T>
//   typename meta::call<tag::rando_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
//   rando(ptrdiff_t n)
//   {
//     return nt2::rando(n,  meta::as_<T>());
//   }
//   meta::call<tag::rando_(const ptrdiff_t &, const ptrdiff_t &, meta::as_<double> const &)>::type
//   rando(ptrdiff_t n, ptrdiff_t k)
//   {
//     return nt2::rando(n, k, meta::as_<double>());
//   }
//   template<class T>
//   typename meta::call<tag::rando_(const ptrdiff_t &, const ptrdiff_t &, typename meta::as_<T> const &)>::type
//   rando(ptrdiff_t n, ptrdiff_t k)
//   {
//     return nt2::rando(n,  k, meta::as_<T>());
//   }

}


#endif
