[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'special' : ['ieee'],
         'tpl'   : '<boost::simd::tag::Pi>',   
         'type_defs' : [],
         'types' : ['real_','signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/03/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 20/03/2011',
            },
         'ranges' : {
             'default' : [['-boost::simd::Ten<T>()', 'boost::simd::Ten<T>()']],
            },
         'specific_values' : {
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Pi<r_t>()',
                 'boost::simd::Minf<T>()' : '-boost::simd::Pi<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Pi<r_t>()',
                 'boost::simd::Valmin<T>()' : '-boost::simd::Pi<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Pi<r_t>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['saturate_at<boost::simd::tag::Pi>(a0)'],
                },
             'property_value' : {
                 'real_' : ['a0>boost::simd::Pi<T>() ? boost::simd::Pi<T>() : (a0<-boost::simd::Pi<T>() ? -boost::simd::Pi<T>() :a0)'],
                 'signed_int_' : ['a0>boost::simd::Pi<T>() ? boost::simd::Pi<T>() : (a0<-boost::simd::Pi<T>() ? -boost::simd::Pi<T>() :a0)'],
                 'unsigned_int_' : ['a0>boost::simd::Pi<T>() ? boost::simd::Pi<T>() :a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
