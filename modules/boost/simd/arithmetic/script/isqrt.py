[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' : ["return the integer truncation of the squre root of  the entry.",
                             "The value returned in the same type as the entry.",
                             "/par",
                             "Negative entry leads to zero for integer entry and nan for floating one."],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'it',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10000)']],
             'signed_int_' : [['0', '100']],
             'default' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Four<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Two<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Four<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Four<T>()' : 'boost::simd::Two<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Four<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Four<T>()' : 'boost::simd::Two<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::isqrt(a0)'],
                },
             'property_value' : {
                 'default' : ['r_t(::sqrt(double(a0)))'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
     'version' : '0.1',
    },
]
