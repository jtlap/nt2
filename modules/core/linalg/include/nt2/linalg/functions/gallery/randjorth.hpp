//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GALLERY_RANDJORTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GALLERY_RANDJORTH_HPP_INCLUDED
#include <nt2/linalg/functions/randjorth.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/qmult.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/rec.hpp>

#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/colvect.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> >)
                            )
  {
    typedef  A2 value_t;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::randjorth_
      , container::domain
      , size_t
      , size_t
      , A2
      , size_t
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& p,  A1 const & q, A2 const & c, A3 const & symm) const
    {
      _2D sizee;
      sizee[0] = p; sizee[1] = q;
      return  boost::proto::
        make_expr<nt2::tag::randjorth_, container::domain>
        ( size_t(p)
        , size_t(q)
        , c
        , size_t(symm)
        , boxify(sizee)
        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                            )
  {
    typedef A2 value_t;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::randjorth_
      , container::domain
      , size_t
      , size_t
      , value_t
      , size_t
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& p,  A1 const & q, A2 const & c) const
    {
      _2D sizee;
      sizee[0] = p; sizee[1] = q;
      return  boost::proto::
        make_expr<nt2::tag::randjorth_, container::domain>
        (
          size_t(p)
          , size_t(q)
          , c
          , size_t(0)
          , boxify(sizee)
        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<floating_<A2> >)
                            )
  {
    typedef typename A2::type value_t;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::randjorth_
      , container::domain
      , size_t
      , size_t
      , value_t
      , size_t
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& p,  A1 const & q, A2 const &) const
    {
      _2D sizee;
      sizee[0] = p; sizee[1] = q;
      value_t c =  nt2::rec(nt2::Sqrteps<value_t>());
      return  boost::proto::
        make_expr<nt2::tag::randjorth_, container::domain>
        (
          size_t(p)
          , size_t(q)
          , c
          , size_t(0)
          , boxify(sizee)
        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randjorth_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (target_<floating_<A1> >)
                            )
  {
    typedef typename  A1::type value_t;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::randjorth_
      , container::domain
      , size_t
      , size_t
      , value_t
      , size_t
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n, A1 const &) const
    {
      _2D sizee;
      size_t p = n >> 1;
      size_t q = n-p;
      sizee[0] = p; sizee[1] = q;
      value_t c =  nt2::rec(nt2::Sqrteps<value_t>());
      return  boost::proto::
        make_expr<nt2::tag::randjorth_, container::domain>
        (
          size_t(p)
          , size_t(q)
          , c
          , size_t(0)
          , boxify(sizee)
        );
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randjorth_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,2>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t> tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t p = boost::proto::child_c<0>(in);
      size_t q = boost::proto::child_c<1>(in);
      bool swaped =  (p > q);
      if (swaped) std::swap(p, q);
      value_t cc = boost::proto::child_c<2>(in);
      size_t symm =  boost::proto::child_c<3>(in);
      size_t n =  p+q;
      BOOST_ASSERT_MSG(cc >= 1, "provided condition number must be greater or equal one");
      value_t c1 =  nt2::oneplus(cc)/(nt2::Two<value_t>()*nt2::sqrt(cc));
      tab_t c = nt2::catv(c1, nt2::oneplus(nt2::minusone(c1)*nt2::rand(p-1, 1, nt2::meta::as_<value_t>())));
      tab_t s = nt2::sqrt(nt2::minusone(nt2::sqr(c)));
      tab_t a =  nt2::blkdiag(nt2::catv(nt2::cath(nt2::from_diag( c), nt2::from_diag(-s)),
                                        nt2::cath(nt2::from_diag(-s), nt2::from_diag( c))),
                              nt2::eye(q-p, nt2::meta::as_<value_t>()));
      tab_t b(nt2::of_size(n, n));
      if(symm)
      {
        tab_t u =  nt2::blkdiag(nt2::qmult(p, nt2::meta::as_<value_t>()),
                                nt2::qmult(q, nt2::meta::as_<value_t>()));
        b =   nt2::mtimes(nt2::mtimes(u, a), nt2::transpose(u));
        a = nt2::average(b, nt2::transpose(b));
        out = a;
        return out;
      }
      b(nt2::_(1, p),nt2::_)     = nt2::qmult(a(nt2::_(1, p),nt2::_));
      b(nt2::_(p+1, p+q),nt2::_) = nt2::qmult(a(nt2::_(p+1, p+q),nt2::_));
      a =  transpose(b);
      b(nt2::_(1, p),nt2::_)     = nt2::qmult(a(nt2::_(1, p),nt2::_));
      b(nt2::_(p+1, p+q),nt2::_) = nt2::qmult(a(nt2::_(p+1, p+q),nt2::_));
      if(swaped)
      {
        a = b(  nt2::cath( nt2::_(p+1, p+q),  nt2::_(1, p)), _); // Permute to produce J-orthogonal matrix.
        b = a(_,  nt2::cath( nt2::_(p+1, p+q), nt2:: _(1, p)));
      }
      out = b;
      return out;
    }
  };

}

//   meta::call<tag::randjorth_(const size_t &, meta::as_<double> const &)>::type
//   randjorth(ptrdiff_t n)
//   {
//     return nt2::randjorth(n,  meta::as_<double>());
//   }
//   template<class T>
//   typename meta::call<tag::randjorth_(const size_t &, typename meta::as_<T> const &)>::type
//   randjorth(ptrdiff_t n)
//   {
//     return nt2::randjorth(n,  meta::as_<T>());
//   }
//   meta::call<tag::randjorth_(const ptrdiff_t &, const ptrdiff_t &, meta::as_<double> const &)>::type
//   randjorth(ptrdiff_t n, ptrdiff_t k)
//   {
//     return nt2::randjorth(n, k, meta::as_<double>());
//   }
//   template<class T>
//   typename meta::call<tag::randjorth_(const ptrdiff_t &, const ptrdiff_t &, typename meta::as_<T> const &)>::type
//   randjorth(ptrdiff_t n, ptrdiff_t k)
//   {
//     return nt2::randjorth(n,  k, meta::as_<T>());
//   }

}


#endif
