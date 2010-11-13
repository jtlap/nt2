/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/or.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <nt2/sdk/memory/meta/is_power_of_2.hpp>

namespace nt2 { namespace result
{
  struct align_on
  {
    template<class Sig> struct result;

    template<class This, class T, class Align>
    struct  result<This(T,Align)>
          : boost::mpl::eval_if < boost::mpl::or_ < boost::is_arithmetic<T>
                                                  , boost::is_pointer<T>
                                                  >
                                , boost::mpl::identity<T>
                                , meta::align_on<T,Align>
                                >
    {};

    template<class This, class T>
    struct  result<This(T)>
          : result<This(T, boost::mpl::int_<NT2_CONFIG_ALIGNMENT>)>
    {};

    template<class T, class Align> inline
    typename result<align_on(T,Align)>::type
    operator()( T const& v, Align const& a)
    {
      return eval ( v, a, typename boost::is_arithmetic<T>::type()
                        , typename boost::is_pointer<T>::type()
                  );
    }

    template<class T> inline
    typename result<align_on(T)>::type
    operator()( T const& v )
    {
      return this->operator()(v,boost::mpl::int_<NT2_CONFIG_ALIGNMENT>());
    }

    template<class T, class Align> inline
    typename result<align_on(T,Align)>::type
    eval( T const& v, Align const& a
        , boost::mpl::true_ const&, boost::mpl::false_ const&
        )
    {
      return (v+Align::value-1) & ~(Align::value-1);
    }

    template<class T, class Align> inline
    typename result<align_on(T,Align)>::type
    eval( T const& v, Align const& a
        , boost::mpl::false_ const&, boost::mpl::true_ const&
        )
    {
      std::size_t ptr = reinterpret_cast<std::size_t>(v);
      return reinterpret_cast<T>(this->operator()(ptr,a));
    }

    template<class T, class Align> inline
    typename result<align_on(T,Align)>::type
    eval( T const& v, Align const& a
        , boost::mpl::false_ const&, boost::mpl::false_ const&
        )
    {
       return typename result<align_on(T,Align)>::type();
    }
  };
} }

namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Align a runtime value onto a static power of 2 boundary.
  // If N is not a power of 2, the function is disabled by SFINAE
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N,class T> inline
  typename  boost::enable_if_c< meta::is_power_of_2_c<N>::value
          , typename std::tr1::result_of<result::align_on(T,boost::mpl::int_<N>)>::type
                              >::type
  align_on( T const& value )
  {
    result::align_on callee;
    return callee( value, boost::mpl::int_<N>());
  }

  //////////////////////////////////////////////////////////////////////////////
  // Align a runtime value onto current alignment value
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline
  typename std::tr1::result_of<result::align_on(T)>::type
  align_on( T const& value )
  {
    result::align_on callee;
    return callee( value );
  }
} }

#endif
