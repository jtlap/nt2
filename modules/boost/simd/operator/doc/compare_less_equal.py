[ ## this file was manually modified by jt
    {
     'functor' : {
        'description' : ['return a bool that is the result of the lexicographic',
                          'test for <= on all elements of the entries','\par',
                          'It is probably not what you wish. Have a look to is_less_equal','\par',
                          "Infix notation can be used with operator '<='"],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'bool',
            },
         'special' : ["reduction"],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <boost/simd/include/functions/all.hpp>'],
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
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>(),boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::compare_less_equal(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['boost::simd::le(a0,a1)'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        bool z = true;",
                        "        for(int i = 0; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          if (!(a0[i]>a1[i])) {z=true;break;}",
                        "          else if (a0[i]>a1[i]){z=false; break;}",
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
