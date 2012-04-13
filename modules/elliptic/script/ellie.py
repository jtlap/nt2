[ ## this file was manually modified by jt
    {
     'functor' : {
         'description':['Incomplete elliptic integral of the second kind','\par Formula',
                       '\\\\f[E(a_0,a_1) = \int_0^{a0} \sqrt{1-a_1\sin^2 t} dt\\\\f]'],
         'param0' :  ['amplitude in radians'], 
         'param1' :  ['modulus between 0 and 1'], 
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_elliel(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-10)', 'T(10)'], ['T(0)', 'T(1)']],
             'signed_int_' : [],
             'unsigned_int_' : [],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>(),T(0)' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Pio_2<T>(),T(0)' : {'result' : 'nt2::Pio_2<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),T(0)' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::ellie(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['::cephes_elliel(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['2.0'],
                },
            },
        },
    },
]
