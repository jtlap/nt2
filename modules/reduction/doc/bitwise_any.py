[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_logical<T>::type',
            },
         'simd_types' : ['real_','signed_int_','unsigned_int_'],
         'special' : ['reduction'],  
         'type_defs' : [],
         'types' : ['real_','signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : ['#include <boost/simd/sdk/simd/logical.hpp>',
                           '#include <nt2/include/functions/is_nez.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
            },
         'specific_values' : {
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                },
             'unsigned_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::bitwise_any(nt2::is_nez(a0))'],
                },
             'property_value' : {
                 'default' : ['a0!=0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        bool z = false;",
                        "        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          z = z||a0[i];",
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
            },
        },
    },
]
