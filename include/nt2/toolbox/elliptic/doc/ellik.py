[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_ellikl(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/include/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0.1)', 'nt2::Pio_2<T>()'], ['T(0)', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>(),0' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Pio_2<T>(),0' : {'result' : 'nt2::Pio_2<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),0' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::ellik(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['::cephes_ellikl(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['2.0'],
                },
            },
        },
    },
]
