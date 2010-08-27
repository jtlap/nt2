/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_IS_ASSIGNMENT_COMPATIBLE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_IS_ASSIGNMENT_COMPATIBLE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Check for two buffer to be comaptible in an assignment operation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  ////////////////////////////////////////////////////////////////////////////
  // For any buffer instances, check if it is assignment compatible
  // at both compile-time and run-time with current one
  ////////////////////////////////////////////////////////////////////////////
  template< class Dst,class Src
          , bool IsDstStatic = Dst::has_static_size::value
          , bool IsSrcStatic = Src::has_static_size::value
          >
  struct  is_assignment_compatible
        : boost::mpl::bool_< (!IsDstStatic || !IsSrcStatic) >
  {
    bool operator()(Dst const& d,Src const& s) const
    {
      return eval(d,s,Dst::has_static_size(),Src::has_static_size());
    }

    private:
    bool eval ( Dst const& ,Src const&
              , boost::mpl::true_ const&, boost::mpl::true_ const&
              ) const
    {
      return Dst::size_value_type::value == Src::size_value_type::value;
    }

    bool eval ( Dst const& , Src const& s
              , boost::mpl::true_ const&, boost::mpl::false_ const&
              ) const
    {
      return s.size() == (typename Src::size_type)(Dst::size_value_type::value);
    }

    template<class State>
    bool eval ( Dst const& ,Src const&
              , boost::mpl::false_ const&, State const&
              ) const
    {
      return true;
    }
  };
} }
#endif
