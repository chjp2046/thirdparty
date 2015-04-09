srcs_common = [
    'dwarf/Lexpr.c',
    'dwarf/Lfde.c',
    'dwarf/Lfind_proc_info-lsb.c',
    'dwarf/Lparser.c',
    'dwarf/Lpe.c',
    'dwarf/Lstep.c',
    'dwarf/global.c',
    'mi/Ldestroy_addr_space.c',
    'mi/Ldyn-extract.c',
    'mi/Lfind_dynamic_proc_info.c',
    'mi/Lget_accessors.c',
    'mi/Lget_fpreg.c',
    'mi/Lget_proc_info_by_ip.c',
    'mi/Lget_proc_name.c',
    'mi/Lget_reg.c',
    'mi/Lput_dynamic_unwind_info.c',
    'mi/Lset_caching_policy.c',
    'mi/Lset_fpreg.c',
    'mi/Lset_reg.c',
    'mi/_ReadSLEB.c',
    'mi/_ReadULEB.c',
    'mi/backtrace.c',
    'mi/dyn-cancel.c',
    'mi/dyn-info-list.c',
    'mi/dyn-register.c',
    'mi/flush_cache.c',
    'mi/init.c',
    'mi/mempool.c',
    'mi/strerror.c',
    'os-linux.c',
]

srcs_i386 = [
    'elf32.c',
    'x86/is_fpreg.c',
    'x86/regname.c',
    'x86/Lcreate_addr_space.c',
    'x86/Lget_save_loc.c',
    'x86/Lglobal.c',
    'x86/Linit.c',
    'x86/Linit_local.c',
    'x86/Linit_remote.c',
    'x86/Lis_signal_frame.c',
    'x86/Lget_proc_info.c',
    'x86/Lregs.c',
    'x86/Lresume.c',
    'x86/Lstep.c',
]

srcs_x86_64 = [
    'elf64.c',
    'x86_64/is_fpreg.c',
    'x86_64/regname.c',
    'x86_64/setcontext.S',
    'x86_64/Lcreate_addr_space.c',
    'x86_64/Lget_save_loc.c',
    'x86_64/Lglobal.c',
    'x86_64/Linit.c',
    'x86_64/Linit_local.c',
    'x86_64/Linit_remote.c',
    'x86_64/Lis_signal_frame.c',
    'x86_64/Lget_proc_info.c',
    'x86_64/Lregs.c',
    'x86_64/Lresume.c',
    'x86_64/Lstep.c',
    'x86_64/getcontext.S'
]

cc_library(
    name = 'unwind',
    srcs = srcs_common +
           enable_if(build_target.arch == 'i386', srcs_i386) +
           enable_if(build_target.arch == 'x86_64', srcs_x86_64),
    defs = [
        '_GNU_SOURCE',
        'HAVE_CONFIG_H',
    ],
    incs = ['../include', '../include/tdep', '.'],
    warning = 'no',
)

