//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_OF_SIZE_HPP_INCLUDED

#include <cstddef>
#include <boost/array.hpp>
#include <boost/mpl/at.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/assert.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/details/of_size_meta.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/fusion/include/iterator_range.hpp>

namespace nt2
{
  namespace detail
  {
    // Initialization helpers
    template<class Begin, class End>
    boost::fusion::iterator_range<Begin const, End const>
    make_iterator_range(Begin const& begin, End const& end)
    {
      return boost::fusion::iterator_range<Begin const, End const>(begin, end);
    }
    
    template<class InB, class InE, class Out>
    void copy(InB const& inb, InE const& inE, Out const& out);
    
    template<class InB, class InE, class Out>
    void copy(InB const& inb, InE const&, Out const&, boost::mpl::true_)
    {
    }
    
    template<class InB, class InE, class Out>
    void copy(InB const& inb, InE const& inE, Out const& out, boost::mpl::false_)
    {
      *out = *inb;
      return copy(boost::fusion::next(inb), inE, boost::next(out));
    }
    
    template<class InB, class InE, class Out>
    void copy(InB const& inb, InE const& inE, Out const& out)
    {
      typename boost::fusion::result_of::equal_to<InB, InE>::type eq;
      return copy(inb, inE, out, eq);
    }
    
    template<class Src, class Dst>
    void copy(Src const& src, Dst const& dst)
    {
      return copy(boost::fusion::begin(src), boost::fusion::end(src), dst);
    }
    
    template<class InB, class InE, class Value>
    void check_all_equal(InB const& inb, InE const& inE, Value const& value);
    
    template<class InB, class InE, class Value>
    void check_all_equal(InB const& inb, InE const&, Value const&, boost::mpl::true_)
    {
    }
    
    template<class InB, class InE, class Value>
    void check_all_equal(InB const& inb, InE const& inE, Value const& value, boost::mpl::false_)
    {
      BOOST_ASSERT_MSG(*inb == value, "Incompatible size in of_size conversion");
      return copy(boost::fusion::next(inb), inE, value);
    }
    
    template<class InB, class InE, class Value>
    void check_all_equal(InB const& inb, InE const& inE, Value const& value)
    {
      typename boost::fusion::result_of::equal_to<InB, InE>::type eq;
      return check_all_equal(inb, inE, value, eq);
    }
    
    template<class Src, class Value>
    void check_all_equal(Src const& src, Value const& value)
    {
      check_all_equal(boost::fusion::begin(src), boost::fusion::end(src), value);
    }
  }
    
  //============================================================================
  /*! of_size_<D0,..,Dn> is a size value containing up to n dimensions.
   **/
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct of_size_
  {
    typedef tag::of_size_ fusion_tag;
    typedef boost::fusion::fusion_sequence_tag tag;
   
    typedef std::size_t         value_type;
    typedef std::size_t&        reference;
    typedef std::size_t const&  const_reference;
    typedef std::size_t*        iterator;
    typedef std::size_t const*  const_iterator;

    //==========================================================================
    // Count non-trivial size values
    //==========================================================================
    #define M0(z,n,t)                                                          \
    : BOOST_PP_CAT(D, BOOST_PP_DEC(BOOST_PP_SUB(NT2_MAX_DIMENSIONS, n))) != 1  \
    ? BOOST_PP_SUB(NT2_MAX_DIMENSIONS, n)

    static const std::size_t
    static_size = 0 ? 0 BOOST_PP_REPEAT(NT2_MAX_DIMENSIONS,M0,~) : 0;
    #undef M0

    //==========================================================================
    // Check if size is entirely known at compile-time
    //==========================================================================
    #define M0(z,n,t) && (BOOST_PP_CAT(D,n) >= 0)
    static const bool
    static_status = (D0 >= 0)
                    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~);
    #undef M0

    //==========================================================================
    // Compute its potential compile-time numel
    //==========================================================================
    #define M0(z,n,t) * (BOOST_PP_CAT(D,n) >= 0 ? BOOST_PP_CAT(D,n) : 1)
    static const std::size_t
    static_numel = (D0 >= 0 ? D0 : 1)
                    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~);
    #undef M0

    //==========================================================================
    // Static size values used internally by MPL/Fusion
    //==========================================================================
    typedef boost::mpl::
            vector_c< std::ptrdiff_t
                    , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)
                    >                                               values_type;

    //==========================================================================
    // Size values storage
    //==========================================================================
    boost::array<std::size_t,static_size> data_;

    //==========================================================================
    // Default constructor either generate [0 1 .. 1] or [D0 ... Dn]
    //==========================================================================
    of_size_()
    {
      data_[0] = (D0 < 0 ) ? 0 : D0;
      default_(boost::mpl::size_t<static_size-1>());
    }

    of_size_( of_size_ const& src ) : data_(src.data_) {}
    
    template<class Sz>
    of_size_( Sz const& other )
    {
      static const std::size_t other_size = boost::fusion::result_of::size<Sz>::type::value;
      static const std::size_t min_size = other_size < static_size ? other_size : static_size;
      
      detail::
      copy( detail::
            make_iterator_range( boost::fusion::begin(other)
                               , boost::fusion::advance_c< min_size - other_size >(boost::fusion::end(other))
                               )
          , &data_[0]
          );
                
      for(std::size_t i = min_size; i != static_size; ++i)
        data_[i] = 1;

#ifndef NDEBUG
      detail::
      check_all_equal( detail::
                       make_iterator_range( boost::fusion::advance_c< min_size - other_size >(boost::fusion::end(other))
                                          , boost::fusion::end(other)
                                          )
                     , boost::mpl::int_<1>()
                     );
#endif
    }

    //==========================================================================
    // Constructors from [D0 .. Dn]
    //==========================================================================
    #define M1(z,n,t) data_[n]= BOOST_PP_CAT(d,n); \
    /**/

    #define M0(z,n,t)                                      \
    of_size_( BOOST_PP_ENUM_PARAMS(n,std::size_t d) )      \
    {                                                      \
      BOOST_PP_REPEAT(n,M1,~)                              \
      for(std::size_t i=n;i<static_size;++i) data_[i] = 1; \
    }                                                      \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

    #undef M0
    #undef M1

    //==========================================================================
    // Access operators
    //==========================================================================
    reference       operator[](std::size_t i)       { return data_[i]; }
    const_reference operator[](std::size_t i) const { return data_[i]; }

    //==========================================================================
    // Sequence interface
    //==========================================================================
    iterator        begin()       { return &data_[0];               }
    const_iterator  begin() const { return &data_[0];               }
    iterator        end()         { return &data_[0] + static_size; }
    const_iterator  end()   const { return &data_[0] + static_size; }

    static std::size_t size() { return static_size; }

    boost::array<std::size_t,static_size> const& data() const { return data_; }

    private:
    template<std::size_t N> inline void default_(boost::mpl::size_t<N> const&)
    {
      typedef typename boost::mpl::at_c<values_type,N>::type value;
      data_[N] = (value::value < 0) ? 1U : value::value;
      default_(boost::mpl::size_t<N-1>());
    }

    inline void default_(boost::mpl::size_t<0> const&) {}
  };

  //============================================================================
  // Specialisation for _0D case
  //============================================================================
  template<> struct of_size_<>
  {
    typedef tag::of_size_ fusion_tag;
    typedef boost::fusion::fusion_sequence_tag tag;
    typedef boost::mpl::vector_c<std::size_t> values_type;
      
    typedef std::size_t value_type;
    typedef std::size_t reference;
    typedef std::size_t const_reference;
    typedef void*       iterator;
    typedef void*       const_iterator;

    static const std::size_t  static_size   = 0;
    static const bool         static_status = true;
    static const std::size_t  static_numel  = 0;

    static std::size_t size() { return 0; }
    const_reference    operator[](std::size_t i) const { return 1; }

    iterator        begin()       { return iterator(0);       }
    const_iterator  begin() const { return const_iterator(0); }
    iterator        end()         { return iterator(0);       }
    const_iterator  end()   const { return const_iterator(0); }
    
    of_size_() {}
    
    template<class Sz>
    of_size_( Sz const& other )
    {
      for(std::size_t i = 0; i != Sz::static_size; ++i)
        BOOST_ASSERT_MSG(other.data_[i] == 1, "Incompatible size in of_size conversion");
    }
  };

  //============================================================================
  // Defines some usual short-cuts for runtime of_size_
  //============================================================================
  #define M0(z,n,t)                                                           \
  typedef of_size_<BOOST_PP_ENUM_PARAMS(n, -1 BOOST_PP_INTERCEPT)>            \
  BOOST_PP_CAT(BOOST_PP_CAT(_, n), D);                                        \
  /**/
  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)
  #undef M0

  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D1)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D2)>
  bool operator==( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)> const& a0
                 , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)> const& a1
                 )
  {
    std::size_t const* it0 = a0.begin();
    std::size_t const* it1 = a1.begin();

    for(; it0 != a0.end() && it1 != a1.end(); ++it0, ++it1)
      if(*it0 != *it1)
        return false;

    return it0 == a0.end() && it1 == a1.end();
  }
}

#endif
