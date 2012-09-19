//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE2_HPP_INCLUDED

#include <nt2/core/functions/freqspace2.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/freqspace2.hpp>
#include <nt2/core/functions/details/colon.hpp>
#include <nt2/include/functions/scalar/splat.hpp>
#include <nt2/include/functions/scalar/enumerate.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(A1)(T)
                              , (scalar_< integer_<A0> >)
                                (scalar_< integer_<A1> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type value_t;
    typedef meta::constant_<nt2::tag::colon_,value_t> constant_t;

    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace2_
                                , container::domain
                                , box<_2D>
                                , box<constant_t>
                                , T
                                >::type             type;
    typedef boost::fusion::vector<type,type>  result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& m, A1 const& n, T const& tgt) const
    {
      value_t hvm = m*Half<value_t>();
      value_t hm  = nt2::rec(hvm);
      value_t lm  = -nt2::floor(hvm)*hm;
      value_t hvn = n*Half<value_t>();
      value_t hn  = nt2::rec(hvn);
      value_t ln  = -nt2::floor(hvn)*hn;

      return boost::fusion::make_vector
      (
        boost::proto::
        make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                    , boxify(constant_t(ln,hn))
                    , tgt
                    )
      , boost::proto::
        make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, m))
                    , boxify(constant_t(lm,hm))
                    , tgt
                    )
      );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type value_t;
    typedef meta::constant_<nt2::tag::colon_,value_t> constant_t;

    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace2_
                                , container::domain
                                , box<_2D>
                                , box<constant_t>
                                , T
                                >::type             type;
    typedef boost::fusion::vector< type,type>  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const& tgt) const
    {
      value_t hv  = n*Half<value_t>();
      value_t h   = nt2::rec(hv);
      value_t l   = -nt2::floor(hv)*h;

      return  boost::fusion::make_vector
      ( boost::proto::
        make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                    , boxify(constant_t(l,h))
                    , tgt
                    )
      , boost::proto::
        make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                    , boxify(constant_t(l,h))
                    , tgt
                    )
      );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                                (scalar_< integer_<A1> >)
                              )
  {
    typedef meta::constant_<nt2::tag::colon_,double> constant_t;

    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace2_
                                , container::domain
                                , box<_2D>
                                , box< constant_t >
                                , meta::as_<double >
                                >::type             type;
    typedef boost::fusion::vector<type,type>  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n) const
    {
      return freqspace2(n,m,nt2::meta::as_<double>());
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)
                              , (scalar_< integer_<A0> >)
                              )
  {
    typedef meta::constant_<nt2::tag::colon_,double> constant_t;

    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace2_
                                , container::domain
                                , box<_2D>
                                , box< constant_t >
                                , meta::as_<double >
                                >::type             type;
    typedef boost::fusion::vector< type,type>       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
      return freqspace2(n, nt2::meta::as_<double>());
    }
  };
} }

#endif
