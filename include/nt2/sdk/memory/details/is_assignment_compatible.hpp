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
  // Two static buffer are assignment compatible if they have the same Size
  // Any number of dynamic buffer to compare two
  ////////////////////////////////////////////////////////////////////////////
  template< class B1,class B2
          , bool IsB1Static = B1::is_static::value
          , bool IsB2Static = B2::is_static::value
          >
  struct  is_assignment_compatible
        : boost::mpl::bool_ <   B1::size_value_type::value
                            ==  B2::size_value_type::value
                            >
  {
    bool operator()(B1 const& ,B2 const& ) const
    {
      return B1::size_value_type::value == B2::size_value_type::value;
    }
  };

  template<class B1,class B2>
  struct is_assignment_compatible<B1,B2,false,false> : boost::mpl::true_
  {
    bool operator()(B1 const& ,B2 const& ) const { return true; }
  };

  template<class B1,class B2>
  struct is_assignment_compatible<B1,B2,true,false> : boost::mpl::true_
  {
    bool operator()(B1 const& s1,B2 const& s2) const
    {
      return s2.size() == (typename B2::size_type)(B1::size_value_type::value);
    }
  };

  template<class B1,class B2>
  struct is_assignment_compatible<B1,B2,false,true> : boost::mpl::true_
  {
    bool operator()(B1 const& s1,B2 const& s2) const
    {
      return true;
    }
  };
} }
#endif
