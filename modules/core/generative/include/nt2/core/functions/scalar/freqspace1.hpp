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
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/colon.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type target_t;

    BOOST_DISPATCH_RETURNS( 2
                          , (A0 const& n, T const& tgt)
                          , nt2::_(target_t(0), target_t(2)/n, target_t(1))
                          );
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& n)
                          , nt2::_(0., 2./n, 1.)
                          );

  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)(T)
                              , (scalar_< integer_<A0> >)
                                (target_<unspecified_<A1> >)
                                (target_<scalar_< floating_<T> > >)
                              )
  {
    typedef typename T::type target_t;

    BOOST_DISPATCH_RETURNS( 3
                          , (A0 const& n, A1 const& w, T const& tgt)
                          , nt2::_( target_t(0)
                                  , target_t(2)/n
                                  , target_t(2)*(n-1)/n
                                  )
                          );
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                                ((target_<unspecified_<A1> >))
                              )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 const& n, A1 const& w)
                          , nt2::_(0., 2./n, 2.*(n-1)/n)
                          );
  };
} }

#endif
