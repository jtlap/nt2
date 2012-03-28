//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_BAND_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // band functor:
  // band(a)(i, j) == (i == j) ? a(i, j) : 0
  //============================================================================
  struct band
  {
    template<class Sig> struct result;

    template<class This, class Pos,class Target>
    struct result<This(Pos,Target)>
    {
      typedef typename meta::strip<Target>::type::type        base;
      typedef typename meta::as_integer<base>::type           in;
      typedef typename meta::call<tag::is_less_(in,in)>::type type;
    };

    template<class Pos,class Target> BOOST_FORCEINLINE
    typename result<band(Pos const&, Target const&)>::type
    operator()(Pos const& p, Target const& t) const
    {
      typedef typename result<band(Pos const&, Target const&)>::in type;

      return is_equal ( nt2::enumerate<type>( boost::fusion::at_c<0>(p) )
                      , nt2::splat<type>    ( boost::fusion::at_c<1>(p) )
                        );
    }
  };

  //============================================================================
  // band with one width functor
  //  band(a, k)(i, j)   is equal to: (i >= j-k)&&(i <= j+k) ? a(i, j) : 0
  //============================================================================
  struct offset_band1
  {
    offset_band1() {}
    offset_band1(std::ptrdiff_t k) : k_(k) {}

    std::ptrdiff_t k_;

    template<class Sig> struct result;

    template<class This, class Pos,class Target>
    struct result<This(Pos,Target)>
    {
      typedef typename meta::strip<Target>::type::type                   base;
      typedef typename meta::as_integer<base>::type                        in;
      typedef typename meta::call<tag::is_greater_equal_(in,in)>::type  type1;
      typedef typename meta::call<tag::is_less_equal_(in,in)>::type     type2; 
      typedef typename meta::call<tag::logical_and_(type1, type2)>::type type; 
    };

    template<class Pos,class Target> BOOST_FORCEINLINE
    typename result<offset_band1(Pos const&, Target const&)>::type
    operator()(Pos const& p, Target const& t) const
    {
      typedef typename result<offset_band1(Pos const&, Target const&)>::in type;

      return logical_and(ge ( nt2::enumerate<type>( boost::fusion::at_c<0>(p)     ), 
                              nt2::splat<type>    ( boost::fusion::at_c<1>(p)-k_  )
                              ), 
                         le ( nt2::enumerate<type>( boost::fusion::at_c<0>(p)     ), 
                              nt2::splat<type>    ( boost::fusion::at_c<1>(p)+k_  )
                              )
                         );
    }
  };

  //============================================================================
  // band with two width functor
  //  band(a, k, l)(i, j)   is equal to: (i >= j-k)&&(i <= j+l) ? a(i, j) : 0
  //============================================================================
  struct offset_band2
  {
    offset_band2() {}
    offset_band2(std::size_t k, std::size_t l) : k_(k), l_(l) {}

    std::size_t k_;
    std::size_t l_;

    template<class Sig> struct result;

    template<class This, class Pos,class Target>
    struct result<This(Pos,Target)>
    { 
      typedef typename meta::strip<Target>::type::type                   base;
      typedef typename meta::as_integer<base>::type                        in;
      typedef typename meta::call<tag::is_greater_equal_(in,in)>::type  type1;
      typedef typename meta::call<tag::is_less_equal_(in,in)>::type     type2; 
      typedef typename meta::call<tag::logical_and_(type1, type2)>::type type; 
    };

    template<class Pos,class Target> BOOST_FORCEINLINE
    typename result<offset_band2(Pos const&, Target const&)>::type
    operator()(Pos const& p, Target const& t) const
    {
      typedef typename result<offset_band2(Pos const&, Target const&)>::in type;

      return logical_and(ge ( nt2::enumerate<type>( boost::fusion::at_c<0>(p)     ), 
                              nt2::splat<type>    ( boost::fusion::at_c<1>(p)-k_  )
                              ), 
                         le ( nt2::enumerate<type>( boost::fusion::at_c<0>(p)     ), 
                              nt2::splat<type>    ( boost::fusion::at_c<1>(p)+l_  )
                              )
                         );
    }
  };  
} }

#endif
