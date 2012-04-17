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

#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/freqspace1.hpp>
#include <nt2/core/functions/details/colon.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>


namespace nt2 { namespace ext
{
  //============================================================================
  // Generates freqspace1 from n to a given floating type
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(T)
                              , (scalar_< integer_<A0> >)
                              ((target_<scalar_< floating_<T> > > ))   
                              )
  {
    typedef typename T::type value_type; 
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace1_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<value_type> >
      , T
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const&) const
    {
      return  boost::proto::
        make_expr < nt2::tag::freqspace1_
        , container::domain
        > ( boxify(of_size(1,n/2+1))
            , boxify(nt2::details::colon<value_type>(Zero<value_type>(), Two<value_type>()/n))
            , T()
            );
    }
  };
  
  //============================================================================
  // Generates freqspace1 from n to double
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)
                              , (scalar_< integer_<A0> >)
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace1_
      , container::domain
      , box<_2D>
      , box< nt2::details::colon<double> >
      , meta::as_<double > 
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& n) const
    {
      return  boost::proto::
        make_expr < nt2::tag::freqspace1_
        , container::domain
        > ( boxify(of_size(1,n/2+1))
            , boxify(nt2::details::colon<double>(0.0, 2.0/n))
            , meta::as_<double>()
            );
    }
  };
  
  
  //============================================================================
  // Generates freqspace1 from to a given type as 'whole'
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)(T)
                              , (scalar_< integer_<A0> >)
                              ((target_<unspecified_<A1> >))
                              ((target_<scalar_< floating_<T> > > ))   
                              )
  {
    typedef typename T::type value_type; 
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace1_
                                          , container::domain
                                          , box< _2D >
                                          , box< nt2::details::colon<value_type> >
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& n, A1 const&, T const &) const
    {
      return  boost::proto::
              make_expr < nt2::tag::freqspace1_
                        , container::domain
                        > ( boxify(of_size(1,n))
                            , boxify(nt2::details::colon<value_type>(Zero<value_type>(), Two<value_type>()/n))
                            , T()
                          );
    }
  };

  //============================================================================
  // Generates freqspace1 from to double as 'whole'
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace1_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                              ((target_<unspecified_<A1> >))
                              )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::freqspace1_
      , container::domain
      , box< _2D >
      , box< nt2::details::colon<double> >
      , meta::as_<double>
      >::type             result_type;
    
    BOOST_FORCEINLINE result_type
      operator()(A0 const& n, A1 const&) const
    {
      return  boost::proto::
        make_expr < nt2::tag::freqspace1_
        , container::domain
        > ( boxify(of_size(1,n))
            , boxify(nt2::details::colon<double>(0.0, 2.0/n))
            , meta::as_<double>()
            );
    }
  };
  
} }


#endif
 
