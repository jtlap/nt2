{
"abs" : {
    "tcall" : "nt2::libc::abs(a0)",
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': 'Inf<T>()', 'Mone<T>()': 'One<T>()',
               'Zero<T>()': 'Zero<T>()', 'Nan<T>()':  'Nan<T>()',
               'Inf<T>()': 'Inf<T>()', 'One<T>()': None}
    },
"amul" : {
    "tcall" : "a0+a1*a2",
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': 'Nan<T>()', 'Mone<T>()': 'Zero<T>()',
               'Zero<T>()': 'Zero<T>()', 'Nan<T>()': 'Nan<T>()',
               'Inf<T>()': 'Inf<T>()', 'One<T>()': 'Two<T>()}
    },
"arg" : {
    "tcall" : "a0>0 ? Pi<T>() : Zero<T>()",
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': 'Pi<T>()', 'Mone<T>()': 'Pi<T>()',
               'Zero<T>()': 'Zero<T>()', 'Nan<T>()': ''Nan<T>()',
               'Inf<T>()': 'Zero<T>()', 'One<T>()': 'Zero<T>()'}
    },
"average" : {
    "tcall" : "T((a0=a1)/Two<T>())",
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': 'Minf<T>()', 'Mone<T>()': 'Mone<T>()',
               'Zero<T>()': 'Zero<T>()', 'Nan<T>()': ''Nan<T>()',
               'Inf<T>()': 'Inf<T>()', 'One<T>()': 'One<T>()'}
    },
"ceil" : {
    "tcall" : nt2::libc::ceil(a0),
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"correct_fma" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"dist" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"fam" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"fast_hypot" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"floor" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"fma" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"hypot" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"iceil" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"idivceil" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"idivfix" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"idivfloor" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"idivround" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"ifloor" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"iround" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"iround2even" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"ldiv" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"ldivide" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"logical_xor" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"madd" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"max" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"min" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"minmod" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"minusone" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"mod" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"oneminus" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"oneplus" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"random" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"rdivide" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"rec" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"rem" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"remainder" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"remquo" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"round" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"rsqrt" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"sqr" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"sqrt" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"sqrt1pm1" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"trunc" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"two_add" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"two_prod" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf'], ['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
"two_split" : {
    "tcall" : None,
    "rnges" : [[['-inf', 'inf']]],
    "specv" : {'Minf<T>()': None, 'Mone<T>()': None, 'Zero<T>()': None, 'Nan<T>()': ''Nan<T>()', 'Inf<T>()': None, 'One<T>()': None}
    },
}
