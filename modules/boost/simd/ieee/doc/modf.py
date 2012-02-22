[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Computes the integer part and the fractionnal part of the input',
                         '\par',
                         'As demonstrated in the synopsis this function can be called in various ways.'
                          ],
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::modf_(A0 const&)",
                "                                    >::type",
                "modf(A0 const& a0);",
                " "
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::modf_(A0 const&,A0&)",
                "                                     >::type",
                "modf(A0 const& a0,A1& a2);",
                " "
                "template<class A0> inline",
                "int modf(A0 const& a0,A0& a2,A0& a3);",
                 ],
         'return'  : ['with one parameter the returned result is a fusion sequence of the two results, '
                      'with two parameters the returned result is the intrger part, '
                      'with three parameters the returned result is always 0'],
          'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'boost::fusion::vector<T,T>',
            },
         'simd_types' : ['real_'],
         'type_defs' : ["typedef typename boost::dispatch::meta::as_floating<T>::type ftype;"],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/trunc.hpp>', '#include <boost/simd/include/functions/frac.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::modf(a0)'],
                },
             'property_value' : {
                 'default' : [['boost::simd::frac(a0)', 'boost::simd::trunc(a0)']],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
