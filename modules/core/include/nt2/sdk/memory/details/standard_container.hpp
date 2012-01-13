//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_STANDARD_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_STANDARD_CONTAINER_HPP_INCLUDED

#include <nt2/core/settings/id.hpp>
#include <nt2/sdk/memory/details/container_base.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * container is the base class handling a container semantic, layout and
   * memory used by the table proto terminal class. It is built from a value
   * \c Type and a list of \c Settings describing how it should behave both at
   * runtime and compile-time.
   *
   * \tparam Type Value type to store in the table
   * \tparam Setting Compound options list describing the behavior of the table
   **/
  //============================================================================
  template<class Tag, class T, class S>
  struct container<Tag, id_<0>, T, S> : nt2::details::container_base<Tag,T,S>
  {
    typedef nt2::details::container_base<Tag,T,S>         parent;
    typedef typename parent::block_t                      block_t;
    typedef typename parent::allocator_type               allocator_type;
    typedef typename parent::iterator                     iterator;
    typedef typename parent::const_iterator               const_iterator;
    typedef typename parent::extent_type                  extent_type;
    typedef typename parent::sizes_type                   sizes_type;
    typedef typename parent::size_type                    size_type;
    typedef typename parent::difference_type              difference_type;
    typedef typename parent::is_static_sized              is_static_sized;
    typedef typename parent::reference                    reference;
    typedef typename parent::const_reference              const_reference;

    //==========================================================================
    /*!
     * Default constructor
     */
    //==========================================================================
    container( allocator_type const& a = allocator_type() ) : block_(a)
    {
      parent::init(block_,sizes_, is_static_sized());
    }

    //==========================================================================
    /*!
     * Constructor from a Dimensions set
     */
    //==========================================================================
    template<class Size>
    container( Size const& sz, allocator_type const& a = allocator_type() )
            : block_( pad(sz,parent::lead_t::value) ,a), sizes_(sz)
    {}

    //==========================================================================
    /*!
     * Copy Constructor
     */
    //==========================================================================
    container( container const& s) : block_( s.block_ ), sizes_(s.sizes_) {}

    //==========================================================================
    /*!
     * Swap two container
     */
    //==========================================================================
    void swap( container& src )
    {
      block_.swap(src.block_);
      sizes_.swap(src.sizes_);
    }

    //==========================================================================
    /*!
     * Random access to container element
     */
    //==========================================================================
    template<class Position> BOOST_FORCEINLINE
    reference operator[]( Position const& pos )
    {
      return parent::access(pos,block_,sizes_);
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference operator[]( Position const& pos ) const
    {
      return parent::access(pos,block_,sizes_);
    }

    //==========================================================================
    /*!
     * Redefine the container shape using a new Dimensions Set
     */
    //==========================================================================
    template<class Size> BOOST_FORCEINLINE void resize( Size const& szs )
    {
      parent::resize( block_,szs,sizes_,is_static_sized() );
    }

    //==========================================================================
    /*!
     * Return the current container dimensions set
     */
    //==========================================================================
    BOOST_FORCEINLINE extent_type extent() const { return sizes_;  }

    //==========================================================================
    /*!
     * Return the number of allocated element of the container
     */
    //==========================================================================
    BOOST_FORCEINLINE size_type size()        const { return block_.size();       }
    BOOST_FORCEINLINE size_type inner_size()  const { return block_.inner_size(); }
    BOOST_FORCEINLINE size_type outer_size()  const { return block_.outer_size(); }

    //==========================================================================
    /*!
     * Return true if the container is empty
     */
    //==========================================================================
    BOOST_FORCEINLINE bool empty() const { return block_.empty(); }

    //==========================================================================
    /*!
     * Return the begin of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       begin()       { return block_.data().begin(); }
    BOOST_FORCEINLINE const_iterator begin() const { return block_.data().begin(); }

    //==========================================================================
    /*!
     * Return the end of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       end()       { return block_.data().end(); }
    BOOST_FORCEINLINE const_iterator end() const { return block_.data().end(); }
    //==========================================================================
    /*!
     * Return the current container dimensions lower indices
     */
    //==========================================================================
    BOOST_FORCEINLINE difference_type lower()       const { return block_.lower();        }
    BOOST_FORCEINLINE difference_type inner_lower() const { return block_.inner_lower();  }
    BOOST_FORCEINLINE difference_type outer_lower() const { return block_.outer_lower();  }

    //==========================================================================
    /*!
     * Return the current container dimensions upper indices
     */
    //==========================================================================
    BOOST_FORCEINLINE difference_type upper()       const { return block_.upper();        }
    BOOST_FORCEINLINE difference_type inner_upper() const { return block_.inner_upper();  }
    BOOST_FORCEINLINE difference_type outer_upper() const { return block_.outer_upper();  }

    private:
    block_t     block_;
    sizes_type  sizes_;
  };
} }

#endif
