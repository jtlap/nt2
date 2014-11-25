#!/bin/bash

function perl-sed() {
  perl -p -0777 -i -e "$@"
}

if [ "$#" -lt 1 ]
then
  # files that define functions
  functions=$(find . -regextype posix-egrep -regex '.*/(functions|constants)/[^/]+\.hpp' | grep -Ev 'include/(functions|constants|nt2/cuda)')

  # files that can add specializations to functions
  specializations=$(find . -not -regex '.*/preprocessor/.*' -name '*.hpp' -o -name '*.cpp')
else
  functions=$(for i in "$@"; do echo "$i"; done)
  specializations=$(for i in "$@"; do echo "$i"; done)
fi

echo "function definitions"
echo "$functions" | while read i
do
  echo "$i"

  if ! grep -q -F 'static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)' "$i"
  then
    #tag = \7
    #parent = $10
    #contenu = $14
    perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)(template\s*<[^>]+>\s*)struct(\s*)(?!apply)([a-zA-Z0-9_]+)(\s*):(\s*)([^\n\}]+)(\s*)({(\s*)((?:[^{}]|(?12))*?)(\s*)});/namespace tag\1\{\2\3\4\5struct\6\7\8:\9$10$11\{$13$14$15  template<class... Args>$15  static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)$15  BOOST_AUTO_DECLTYPE_BODY( dispatching( ext::adl_helper(), \7(), static_cast<Args&&>(args)... ) )$15\};/gs' "$i"
  fi
  if ! grep -q -F 'static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)' "$i"
  then
    #tag = \6
    #parent = \9
    #contenu = $12
    perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)struct(\s*)(?!apply)([a-zA-Z0-9_]+)(\s*):(\s*)([^\n{}]+)(\s*)({(\s*)((?:[^{}]|(?11))*?)(\s*)});((?:[^{}]|{(?15)})*?)}/namespace tag\1\{\2\3\4struct\5\6\7:\8\9$10\{$12$13$14  template<class... Args>$14  static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)$14  BOOST_AUTO_DECLTYPE_BODY( dispatching_\6( ext::adl_helper(), static_cast<Args&&>(args)... ) )$14\};$15}\1namespace ext\1\{\2template<class Site, class... H>\2BOOST_FORCEINLINE generic_dispatcher<tag::\6, Site> dispatching_\6(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<H>...)\2\{\2  return generic_dispatcher<tag::\6, Site>();\2\}\2template<class... Args>\2struct impl_\6;\1\}/gs' "$i"
  fi
  if ! grep -q -F generic_dispatcher "$i"
  then
    #tag = \6
    perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)BOOST_SIMD_CONSTANT_REGISTER\((\s*)([a-zA-Z0-9_]+)(\s*),([^)]+)\)((?:[^{}]|{(?9)})*?)}/namespace tag\1\{\2\3\4BOOST_SIMD_CONSTANT_REGISTER(\5\6\7,\8)\9}\1namespace ext\1\{\2template<class Site, class... H>\2BOOST_FORCEINLINE generic_dispatcher<tag::\6, Site> dispatching_\6(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<H>...)\2\{\2  return generic_dispatcher<tag::\6, Site>();\2\}\2template<class... Args>\2struct impl_\6;\1\}/gs' "$i"
  fi

  # replace tag::formal_ by ext::abstract_<X>
  perl-sed 's/namespace tag(\s*){(\s*)(.*?)?(\s*)(template\s*<[^>]+>\s*)?struct(\s*)(?!apply)([a-zA-Z0-9_]+)(\s*):(\s*)(?:boost::)?(?:dispatch::)?(?:tag::)?formal_(\s*){(.*?)typedef (.*?) parent;/namespace tag\1\{\2\3\4\5struct\6\7\8:\9ext::abstract_<\7>$10\{$11typedef ext::abstract_<\7> parent;/gs' "$i"

  # default-constructing tags causes incompleteness problems with clang
  perl-sed 's/\n( *)BOOST_AUTO_DECLTYPE_BODY\( dispatching\( ext::adl_helper\(\), ([^,()]+)\(\), static_cast<Args&&>\(args\)... \) \)/\n\1BOOST_AUTO_DECLTYPE_HEADER( dispatching( ext::adl_helper(), *(\2*)0, static_cast<Args&&>(args)... ) )\n\1\{\n\1  return dispatching( ext::adl_helper(), \2(), static_cast<Args&&>(args)... );\n\1\}/g' "$i"

  # MSVC is just plain weird, so we avoid template variadics in dispatching functions
  perl-sed 's/template<class Site, class\.\.\. H>(\s*)BOOST_FORCEINLINE generic_dispatcher<tag::([a-zA-Z0-9_]+), Site> dispatching_\2\(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<H>...\)/template<class Site>\1BOOST_FORCEINLINE generic_dispatcher<tag::\2, Site> dispatching_\2(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)/gs' "$i"

done

echo "function specializations"
echo "$specializations" | while read i
do
  echo "$i"

  # remove nt2::tag:: / boost::simd::tag::
  perl-sed 's/(NT2|BOOST_SIMD)_(FUNCTOR_IMPLEMENTATION|REGISTER_DISPATCH)(_TO)?(_TPL)?(_IF)?(\s*)\((\s*)([:a-zA-Z0-9_]+?)::tag::([a-zA-Z0-9#_]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_@{[ $2 eq "FUNCTOR_IMPLEMENTATION" ? "IMPLEMENT" : "REGISTER" ]}\3\4\5@{[ " " x (length($1) - ($2 eq "FUNCTOR_IMPLEMENTATION" ? 1 : 5)) ]}\6(\7\9$10$11/g' "$i"

  # for cases that include template arguments, use the _G variant
  perl-sed 's/(NT2|BOOST_SIMD)_(FUNCTOR_IMPLEMENTATION|REGISTER_DISPATCH)(_TO)?(_TPL)?(_IF)?(\s*)\((\s*)([:a-zA-Z0-9#_<>\s]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_@{[ $2 eq "FUNCTOR_IMPLEMENTATION" ? "IMPLEMENT" : "REGISTER" ]}_G\3\4\5@{[ " " x (length($1) - ($2 eq "FUNCTOR_IMPLEMENTATION" ? 3 : 7)) ]}\6(\7\8\9$10/g' "$i"

  # existing uses of BOOST_DISPATCH_REGISTER with explicit tag, just remove namespace
  perl-sed 's/BOOST_DISPATCH_REGISTER(_TO)?(_IF)?(\s*)\((\s*)\(.+?\)\s*,\s*[:a-zA-Z0-9_]+?::tag::([a-zA-Z0-9#_]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_REGISTER\1\2\3(\4\5\6\7/gs' "$i"

  # existing uses of BOOST_DISPATCH_REGISTER with template tag, use the _G variant
  perl-sed 's/BOOST_DISPATCH_REGISTER(_TO)?(_IF)?(\s*)\((\s*)\(.+?\)\s*,\s*([:a-zA-Z0-9#_<>\s]+)(\s*)(,|\n|\\)/BOOST_DISPATCH_REGISTER_G\1\2\3(\4\5\6\7/gs' "$i"

  if echo "$i" | grep -q -F 'include/nt2'
  then
    # unqualified dispatch::, mpl:: or is_same
    perl-sed 's@(?<![:/])\b(mpl::|dispatch::|is_same\b)@boost::\1@g' "$i"

    if ! echo "$i" | grep -q -E '(protocol|run.hpp)'
    then
      # unqualified run
      perl-sed 's@(?<![:/.])\brun\b(\s*\()@nt2::run\1@g' "$i"
    fi
  fi
done

echo "complex numbers for Boost.SIMD"
complex_specializations=$(find . -regextype posix-egrep -regex './modules/type/complex/base/include/.*\.hpp' -o -regex './modules/type/complex/sdk/include/nt2/memory/.*\.hpp' -not -name assign.hpp)

echo "$complex_specializations" | while read i
do
  echo "$i"
  if ! grep -q -F 'namespace boost { namespace simd { namespace ext' "$i"
  then
    perl-sed 's@namespace\s+nt2\s*{\s*namespace\s+ext@namespace boost { namespace simd { namespace ext@g' "$i"
    perl-sed 's@}\s*}(\s*)#endif@} } }\1#endif@gs' "$i"
  fi
  perl-sed 's@(?<!:)\bmeta::(as_complex|as_real|as_dry)@nt2::meta::\1@g' "$i"
  perl-sed 's@(?<!:)\bmeta::(as_integer|as_(?:un)?signed|as_floating|call)@boost::dispatch::meta::\1@g' "$i"
  perl-sed 's@(?<![:/])\b(real|imag|mul_i|pure|complexiy|frompolar|proj|tocomplex|c_real|mul_minus_i)\b@nt2::\1@g' "$i"
done
