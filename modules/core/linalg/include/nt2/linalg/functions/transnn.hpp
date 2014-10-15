//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRANSNN_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRANSNN_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag expm_ of functor expm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct transnn_ : boost::dispatch::tag::formal_
    {
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /**
   * @brief compute transpose of statically sized small matrices
   *
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::transnn_       , transnn, 3)

  template <long N, long M, class T>
  table<T, nt2::of_size_<M, N>> transnn(const  table<T, nt2::of_size_<N, M>>& a0)
  {
    std::cout << N << "   " << M << std::endl;
    NT2_DISPLAY(a0);
    return nt2::transnn(a0,  boost::mpl::long_<N>(),  boost::mpl::long_<M>());
  }
//   template <int N, int M  class T>
//   auto transnn(const T& a0) -> decltype( nt2::transnn(a0,boost::mpl::long_<N>(),boost::mpl::long_<M>()))
//   {
//     return nt2::transnn(a0,  boost::mpl::long_<N>(),  boost::mpl::long_<M>());
//   }

}

#endif
