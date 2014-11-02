#!/bin/bash

function perl-sed() {
  perl -p -0777 -i -e "$@"
}

# files that define functions
functions=$(find . -regextype posix-egrep -regex '.*/(functions|constants)/[^/]+\.hpp' | grep -Ev 'include/(functions|constants)')

# files that can add specializations to functions
specializations=$(find . -not -regex '.*/preprocessor/.*' -name '*.hpp' -o -name '*.cpp')


echo "$functions" | while read i
do
  #tag = \7
  #parent = $10
  #contenu = $13

  #perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)(template\s*<[^>]+>\s*)?struct(\s*)([a-zA-Z0-9_]+)(\s*):(\s*)([^\n\}]+)(\s*){(\s*)(.*?)(\s*)};(\s*)}(\s*)/foo/gs' "$i"
  #namespace tag\1\{\2\3\4\5struct\6\7\8:\9$10$11\{$12$13$14\};$15\}$16

  #tag = \6

  #perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)BOOST_SIMD_CONSTANT_REGISTER\((\s*)([a-zA-Z0-9_]+)(\s*),([^)]+)\)(\s*)}(\s*)/foo/gs' "$i"
  #namespace tag\1\{\2\3\4BOOST_SIMD_CONSTANT_REGISTER(\5\6\7,\8)\9\}$10

: '
si non template :

namespace tag
{
  struct thetag;
}

namespace ext
{
  template<class... H>
  BOOST_FORCEINLINE generic_dispatcher<tag::thetag> dispatching_thetag(adl_helper, boost::dispatch::meta::unspecified_<H>...);

  template<class... Args>
  struct thetag_impl;
}

// ou BOOST_SIMD_CONSTANT_REGISTER
namespace tag
{
  struct thetag : parent_tag
  {
    typedef parent_tag parent;

    template<class... Args>
    static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatching(Args&&... args)
    BOOST_AUTO_DECLTYPE_BODY( dispatch_thetag( ext::adl_helper(), static_cast<Args&&>(args)... ) )
  };
}

namespace ext
{
  template<class... H>
  BOOST_FORCEINLINE generic_dispatcher<tag::thetag> dispatching_thetag(adl_helper, boost::dispatch::meta::unspecified_<H>...)
  {
    return generic_dispatcher<tag::thetag>();
  }
}

// autre option
BOOST_DISPATCH_DECLARE(thetag, parent)
Quid de BOOST_SIMD_CONSTANT_REGISTER ?

si template :

namespace tag
{
  struct thetag : parent_tag
  {
    typedef parent_tag parent;

    template<class... Args>
    static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatching(Args&&... args)
    BOOST_AUTO_DECLTYPE_BODY( dispatching( ext::adl_helper(), thetag(), static_cast<Args&&>(args)... ) )
  };
}
'

done

# works, disabled until functions are ready
if false
then
echo "$specializations" | while read i
do
  # remove nt2::tag:: / boost::simd::tag::
  perl-sed 's/(NT2|BOOST_SIMD)_(FUNCTOR_IMPLEMENTATION|REGISTER_DISPATCH)(_TO)?(_TPL)?(_IF)?(\s*)\((\s*)([:a-zA-Z0-9_]+?)::tag::([a-zA-Z0-9#_]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_@{[ $2 eq "FUNCTOR_IMPLEMENTATION" ? "IMPLEMENT" : "REGISTER" ]}\3\4\5@{[ " " x (length($1) - ($2 eq "FUNCTOR_IMPLEMENTATION" ? 1 : 5)) ]}\6(\7\9$10$11/g' "$i"

  # for cases that include template arguments, use the _G variant
  perl-sed 's/(NT2|BOOST_SIMD)_(FUNCTOR_IMPLEMENTATION|REGISTER_DISPATCH)(_TO)?(_TPL)?(_IF)?(\s*)\((\s*)([:a-zA-Z0-9#_<>\s]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_@{[ $2 eq "FUNCTOR_IMPLEMENTATION" ? "IMPLEMENT" : "REGISTER" ]}_G\3\4\5@{[ " " x (length($1) - ($2 eq "FUNCTOR_IMPLEMENTATION" ? 3 : 7)) ]}\6(\7\8\9$10/g' "$i"
done
fi
