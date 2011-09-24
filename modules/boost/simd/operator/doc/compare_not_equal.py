[ ## this file was manually modified by jt
    {
     'functor' : {
        'description' : ['return a bool that is the result of the lexicographic',
                          'test for != on elements of the entries',
                          'I.e. return true if and only if two corresponding entries',
                          'elements are not equal.','\par',
                          'It is probably not what you wish. Have a look to <tt>is_not_equal</tt>','\par',
                          "Infix notation can be used with operator '!='"],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'bool',
            },
         'special' : ["reduction"],
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <boost/simd/include/functions/any.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>(),boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::compare_not_equal(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::any(boost::simd::neq(a0,a1))'],
                },
             'simd' : {
                },
             'scalar_simul' :{
                    'default' : [
                        "        bool z = a0[0]!=a1[0];",
                        "        for(int i = 1; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          z |= !(a0[i]==a1[i]);",
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
