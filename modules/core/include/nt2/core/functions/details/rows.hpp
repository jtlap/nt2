//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_ROWS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_ROWS_HPP_INCLUDED

#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // rows actual functor
  //============================================================================
  template<class T> struct rows
  {
    rows() {}
    rows(const T & start) : start_(start) {}

    template<class Pos, class Size, class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const& sz, Target const& ) const
    {
      typedef typename Target::type                                   type;
      typedef typename meta::call<nt2::tag::ind2sub_(Size,Pos)>::type  sub_t;

      sub_t const pos = ind2sub(sz,p);
      return nt2::enumerate<type>(pos[0]+start_);
    }

    private :
    T start_;
  };

//   template < class T, class T1>
//   struct rows_scaled
//   {
//     rows_scaled()                : start_(T()), h_(One<T>())  {}
//     rows_scaled(const T & start, const T1 & h) : start_(start), h_(h){}
//     template<class Pos, class Size, class Target>
//     typename Target::type operator()(Pos const& p, Size const&, Target const& ) const
//     {
//       typedef typename Target::type result_type;
//       typedef typename meta::scalar_of<result_type>::type s_type;
//       return nt2::arith<result_type>(boost::fusion::at_c<0>(p)+s_type(start_), s_type(h_));
//     }
//   private :
//     T start_;
//     T h_;
//   };
} }

#endif
