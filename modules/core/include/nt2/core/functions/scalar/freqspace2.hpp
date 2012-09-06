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

//         tab_t f1 = ((_(0, minusone(s2))-nt2::floor(s2*Half<value_type>()))*(Two<value_type>()/s2));
//         tab_t f2 = ((_(0, minusone(s1))-nt2::floor(s1*Half<value_type>()))*(Two<value_type>()/s1));

// f1 = ((0:n(2)-1)-floor(n(2)/2))*(2/(n(2)));

// ou
//    n odd,  f1 = (-1+1/n:2/n:1-1/n).
//    n even  f1 = (-1    :2/n:1-2/n).
// %
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates freqspace2 from m and n to a given floating type
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(A1)(T)
                              , (scalar_< integer_<A0> >)
                                (scalar_< integer_<A1> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace2_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<value_type> >
      , T
      >::type             type;
    typedef boost::fusion::vector< type,type>  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, T const&) const
    {
      value_type hvm = m*Half<value_type>();
      value_type hm = nt2::rec(hvm);
      value_type lm = -nt2::floor(hvm)*hm;
      value_type hvn = n*Half<value_type>();
      value_type hn = nt2::rec(hvn);
      value_type ln = -nt2::floor(hvn)*hn;
        return boost::fusion::make_vector(
                  boost::proto::
                  make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                      , boxify(nt2::details::colon<value_type>(ln,hn))
                      , T()
                      ),
                    boost::proto::
                  make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, m))
                      , boxify(nt2::details::colon<value_type>(lm,hm))
                      , T()
                      )
                );
    }
  };

  //============================================================================
  // Generates freqspace2 from n to a given floating type
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                                ((target_<scalar_< floating_<T> > > ))
                              )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace2_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<value_type> >
      , T
      >::type             type;
    typedef boost::fusion::vector< type,type>  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const&) const
    {
      value_type hv = n*Half<value_type>();
      value_type h =nt2::rec(hv);
      value_type l = -nt2::floor(hv)*h;
        return boost::fusion::make_vector(
                  boost::proto::
                  make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                      , boxify(nt2::details::colon<value_type>(l,h))
                      , T()
                      ),
                  boost::proto::
                  make_expr < nt2::tag::freqspace2_
                  , container::domain
                  > ( boxify(of_size(1, n))
                      , boxify(nt2::details::colon<value_type>(l,h))
                      , T()
                      )
                  );
    }
  };

  //============================================================================
  // Generates freqspace2 from m and n to double
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                                (scalar_< integer_<A1> >)
                              )
  {
    typedef double value_type;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace2_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<double> >
      , meta::as_<double >
      >::type             type;
    typedef boost::fusion::vector<type,type>  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n) const
    {
      return freqspace2(n, m, nt2::meta::as_<double>());
    }
  };


  //============================================================================
  // Generates freqspace2 from n to double
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace2_, tag::cpu_
                              , (A0)
                              , (scalar_< integer_<A0> >)
                              )
  {
    typedef double value_type;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace2_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<double> >
      , meta::as_<double >
      >::type             type;
    typedef boost::fusion::vector< type,type>  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
      return freqspace2(n, nt2::meta::as_<double>());
    }
  };
} }

#endif
