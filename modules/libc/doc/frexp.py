[ ## this file was manually modified by jt
    {
     'functor' : {
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::frexp_(A0 const&)",
                "                                    >::type",
                "frexp(A0 const& a0);",
                " ",
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::frexp_(A0 const&,A0&)",
                "                                     >::type",
                "frexp(A0 const& a0,A1& a2);",
                " ",
                "template<class A0,class A1> inline",
                "int frexp(A0 const& a0,A0& a2,A1& a3);",
                 ],
         'max_arity' : '3',
         'return' : ['depends of the number of arguments: see nt2::frexp for details'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
              'default' : 'boost::fusion::vector<T,nt2::int32_t>',
            },
         'simd_types' : [],
         'special' : ['libc'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 05/03/2011',
             'included' :
                ['#include <boost/fusion/tuple.hpp>',
                 '#include <nt2/include/functions/mantissa.hpp>',
                 '#include <nt2/include/functions/exponent.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 05/03/2011',
            },
         'ranges' : {
             'real_' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::libc::frexp(a0)'],
                },
             'property_value' : {
                 'real_' : ['nt2::mantissa(a0)/2', 'nt2::exponent(a0)+1'],
                },
             'ulp_thresh' : {
                 'real_' : ['1'],
                },
            },
        },
    },
]
