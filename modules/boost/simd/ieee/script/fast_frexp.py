[ ## this file was manually modified by jt
    {
     'functor' : {
          'description' :['Split a floating entry in signed mantissa m and exponent e',
                         '\\\\f$a = m\\\\times 2^e\\\\f$, with absolute value of m',
                         'between one half and one',
                         '\par',
                          "The fast prefix indicates that for speed sake",
                          "the result may be incorrect for limiting values:",
                          "inf, -inf nan and zero that deserve special treatment."
                          "If you are not sure use \c frexp at the expense",
                          "of some more machine cycles.",
                          '\par',
                          'As demonstrated in the synopsis this function can be called in various ways.'
                         ],
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::fast_frexp_(A0 const&)",
                "                                    >::type",
                "fast_frexp(A0 const& a0);",
                " "
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::fast_frexp_(A0 const&,A0&)",
                "                                     >::type",
                "fast_frexp(A0 const& a0,A1& a2);",
                " "
                "template<class A0,class A1> inline",
                "int fast_frexp(A0 const& a0,A0& a2,A1& a3);",
                 ],
         'max_arity' : '3',   
         'param_1' : ['if not present, the function return a boost::fusion sequence'],
         'param_2' : ['if present will contain the mantissa of a0'],
         'param_3' : ['if present will contain the exponent of a0'],
         'return'  : ['with one parameter the returned result is a fusion sequence of the two results, '
                      'with two parameters the returned result is the mantissa, '
                      'with three parameters the returned result is always 0'],
          'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'boost::fusion::vector<T,typename boost::dispatch::meta::as_integer<T,signed>::type>',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : 
                ['#include <boost/fusion/tuple.hpp>',
                 '#include <boost/simd/include/functions/mantissa.hpp>',
                 '#include <boost/simd/include/functions/exponent.hpp>'],
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
                 'default' : ['boost::simd::fast_frexp(a0)'],
                },
             'property_value' : {
                 'default' : [['boost::simd::mantissa(a0)/2', 'boost::simd::exponent(a0)+1']],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
