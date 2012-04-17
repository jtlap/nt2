/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_DETAILS_FREQSPACE1_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_FREQSPACE1_HPP_INCLUDED


namespace nt2 { namespace details
                {
  //============================================================================
  // freqspace1 actual functor : precompute step and just iterate over
  //============================================================================
  template<class T> struct freqspace1
  {
    typedef T value_type; 
    freqspace1() {}
    freqspace1(size_t n)
      : lower_(Zero<value_type>()), step_(Two<value_type>()/n) {}
    
    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      
      return nt2::fma ( nt2::enumerate<type>(p)
                        , nt2::splat<type>(step_)
                        , nt2::splat<type>(lower_)
                        );
    }
    
   value_type lower_, step_;
  };
} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of freqspace1.hpp<3>
// /////////////////////////////////////////////////////////////////////////////
