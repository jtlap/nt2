//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_0D_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_0D_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <nt2/core/settings/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/core/utility/of_size/fusion.hpp>

namespace nt2
{
  //============================================================================
  // Specialisation for _0D case
  //============================================================================
  template<> struct of_size_<>
  {
    typedef tag::of_size_                           fusion_tag;
    typedef boost::fusion::fusion_sequence_tag      tag;
    typedef boost::mpl::vector_c< std::ptrdiff_t >  values_type;
    typedef std::size_t                             value_type;
    typedef std::size_t                             reference;
    typedef std::size_t                             const_reference;
    typedef std::size_t*                            iterator;
    typedef std::size_t const*                      const_iterator;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    static const std::size_t  static_size   = 0;
    static const bool         static_status = true;
    static const std::size_t  static_numel  = 1;

    static std::size_t size() { return 0;     }
    static bool empty()       { return true;  }

    const_reference    operator[](std::size_t i) const { return 1; }

    std::size_t* data()             { return 0; }
    std::size_t const* data() const { return 0; }

    iterator        begin()       { return iterator(0);       }
    const_iterator  begin() const { return const_iterator(0); }
    iterator        end()         { return iterator(0);       }
    const_iterator  end()   const { return const_iterator(0); }

    reverse_iterator        rbegin()       { return reverse_iterator(0);        }
    const_reverse_iterator  rbegin() const { return const_reverse_iterator(0);  }
    reverse_iterator        rend()         { return reverse_iterator(0);        }
    const_reverse_iterator  rend()   const { return const_reverse_iterator(0);  }

    of_size_() {}

    template<class Seq>
    of_size_( Seq const& other
            , typename  boost::enable_if
                        < boost::fusion::traits::is_sequence<Seq> >::type* = 0
            )
    {
      details::check_all_equal(other, 1);
    }
  };
}

#endif
