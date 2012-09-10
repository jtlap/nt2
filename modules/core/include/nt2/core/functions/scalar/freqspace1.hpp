//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE1_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE1_HPP_INCLUDED

#include <nt2/core/functions/freqspace1.hpp>
#include <nt2/core/functions/colon.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/core/utility/box.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type                              value_t;
    typedef meta::constant_<nt2::tag::colon_,value_t>  constant_t;
    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace1_
                                , container::domain
                                , box<_2D>
                                , box<constant_t>
                                , T
                                >::type               result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const&) const
    {
      return  boost::proto::
        make_expr < nt2::tag::freqspace1_
                  , container::domain
                  > ( boxify(of_size(1,n/2+1))
                    , boxify(constant_t(Zero<value_t>(), Two<value_t>()/n))
                    , T()
                    );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef meta::constant_<nt2::tag::colon_,double>  constant_t;
    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace1_
                                , container::domain
                                , box<_2D>
                                , box< constant_t >
                                , meta::as_<double >
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
      return  boost::proto::
              make_expr < nt2::tag::freqspace1_
                        , container::domain
                        > ( boxify(of_size(1,n/2+1))
                          , boxify(constant_t(0.0, 2.0/n))
                          , meta::as_<double>()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)(T)
                              , (scalar_< integer_<A0> >)
                                (target_<unspecified_<A1> >)
                                (target_<scalar_< floating_<T> > >)
                              )
  {
    typedef typename T::type                              value_t;
    typedef meta::constant_<nt2::tag::colon_,value_t>  constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace1_
                                          , container::domain
                                          , box< _2D >
                                          , box< constant_t >
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& n, A1 const&, T const &) const
    {
      return  boost::proto::
              make_expr < nt2::tag::freqspace1_
                        , container::domain
                        > ( boxify(of_size(1,n))
                          , boxify(constant_t(Zero<value_t>(), Two<value_t>()/n))
                          , T()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                              ((target_<unspecified_<A1> >))
                              )
  {
    typedef meta::constant_<nt2::tag::colon_,double>  constant_t;
    typedef typename  boost::proto::result_of::
                      make_expr < nt2::tag::freqspace1_
                                , container::domain
                                , box< _2D >
                                , box<constant_t>
                                , meta::as_<double>
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n, A1 const&) const
    {
      return  boost::proto::
              make_expr < nt2::tag::freqspace1_
                        , container::domain
                        > ( boxify(of_size(1,n))
                          , boxify(constant_t(0.0, 2.0/n))
                          , meta::as_<double>()
                          );
    }
  };
} }

#endif
