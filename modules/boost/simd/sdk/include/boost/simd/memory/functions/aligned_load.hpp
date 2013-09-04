//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief aligned_load generic tag

      Represents the aligned_load function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct aligned_load_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Load data from memory

    Retrieves data from a pointer and an offset using the most efficient
    operations and register types for the chosen destination type.

    @pre  If @c Type is a SIMD register type, the value of
          @c ptr + @c offset - @c Misalignment must satisfy SIMD
          alignment constraint.

    @par Semantic

    Depending on the type of its arguments, aligned_load exhibits different semantics.
    For any type @c Type, @c ptr of type @c Pointer and @c offset of type @c
    Offset, consider:

    @code
    Type x = aligned_load<Type>(ptr,offset);
    @endcode

    If @c Type is a SIMD value, this code is equivalent to:
    - If @c offset is a scalar integer:

      @code
      for(int i=0;i<Value::static_size;++i)
        x[i] = *(ptr+offset+i);
      @endcode

    - If @c offset is a SIMD integral register:

      @code
      for(int i=0;i<Value::static_size;++i)
        x[i] = *(ptr+offset[i]);
      @endcode

      In this case, the aligned_load operation is equivalent to a gather operation.

    If @c Type and @c ptr are Fusion Sequences of size @c N, this code is
    equivalent to:

    @code
    at_c<0>(x)   = aligned_load(at_c<0>(ptr),offset);
    ...
    at_c<N-1>(x) = aligned_load(at_c<N-1>(ptr),offset);
    @endcode

    If @c Type is a scalar type, then it is equivalent to:

    @code
    x = *(ptr+offset);
    @endcode

    @par Misalignment handling

    In all these cases, the @c Misalignment optional template parameter can be
    used to notify aligned_load that the current pointer used is misaligned by
    a specific amount. In this case, aligned_load can be issued by using an
    architecture specific strategy to perform this aligned_loading efficiently.

    For any type @c T, any pointer @c ptr and value of misalignment @c M, the
    call:

    @code
    aligned_load<T, M>(ptr);
    @endcode

    implies that

    @code
    is_aligned(ptr-M) == true
    @endcode

    In other case, when misalignment of pointer can't be known at compile-time,
    use unaligned_aligned_load.

    @usage{memory/aligned_load.cpp}

    @tparam Type          Type of data to aligned_load from memory
    @tparam Misalignment  Optional misalignment hints

    @param ptr    Memory location to aligned_load data from.
    @param offset Optional memory offset.

    @return A value of type @c Type aligned_loaded from target memory block
  **/
  template<typename Type,int Misalignment,typename Pointer,typename Offset>
  BOOST_FORCEINLINE Type aligned_load(Pointer const& ptr, Offset const& offset )
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_load_( Pointer const&
                                              , Offset const&
                                              , boost::dispatch::meta::as_<Type> const&
                                              , boost::mpl::int_<Misalignment> const&
                                              )>::type          callee;

    return callee ( ptr , offset
                  , boost::dispatch::meta::as_<Type>()
                  , boost::mpl::int_<Misalignment>()
                  );
  }

  /// @overload
  template<typename Type,int Misalignment,typename Pointer>
  BOOST_FORCEINLINE Type aligned_load(Pointer const& ptr)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_load_(Pointer const&
                                              , boost::dispatch::meta::as_<Type> const&
                                              , boost::mpl::int_<Misalignment> const&
                                              )>::type callee;

    return callee ( ptr
                  , boost::dispatch::meta::as_<Type>()
                  , boost::mpl::int_<Misalignment>()
                  );
  }

  /// @overload
  template<typename Type,typename Pointer,typename Offset>
  BOOST_FORCEINLINE Type aligned_load(Pointer const& ptr,Offset const& offset)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_load_( Pointer const&
                                              , Offset const&
                                              , boost::dispatch::meta::as_<Type> const&
                                              )>::type          callee;

    return callee(ptr,offset,boost::dispatch::meta::as_<Type>());
  }

  /// @overload
  template<typename Type,typename Pointer>
  BOOST_FORCEINLINE Type aligned_load(Pointer const& ptr)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_load_(Pointer const&
                                              , boost::dispatch::meta::as_<Type> const&
                                              )>::type callee;

    return callee(ptr,boost::dispatch::meta::as_<Type>());
  }
} }

#endif
