[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Bessel function of the first kind of order 0.'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified', 
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 16/02/2011',
             'included' : ['extern "C" {long double cephes_j0l(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 16/02/2011',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'r_t( 7.651976865579666e-01)','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
           },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::j0(a0)'],
                },
             'property_value' : {
                 'default' : ['cephes_j0l(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['64.0'],
                },
            },
        },
    },
]
