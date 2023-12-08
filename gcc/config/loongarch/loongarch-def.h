/* LoongArch definitions.
   Copyright (C) 2021-2023 Free Software Foundation, Inc.
   Contributed by Loongson Ltd.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* Definition of standard codes for:
    - base architecture types	(isa_base),
    - ISA extensions		(isa_ext),
    - base ABI types		(abi_base),
    - ABI extension types	(abi_ext).

    - code models		      (cmodel)
    - other command-line switches     (switch)

   These values are primarily used for implementing option handling
   logic in "loongarch.opt", "loongarch-driver.c" and "loongarch-opt.c".

   As for the result of this option handling process, the following
   scheme is adopted to represent the final configuration:

    - The target ABI is encoded with a tuple (abi_base, abi_ext)
      using the code defined below.

    - The target ISA is encoded with a "struct loongarch_isa" defined
      in loongarch-cpu.h.

    - The target microarchitecture is represented with a cpu model
      index defined in loongarch-cpu.h.
*/

#ifndef LOONGARCH_DEF_H
#define LOONGARCH_DEF_H

#if !defined(IN_LIBGCC2) && !defined(IN_TARGET_LIBS) && !defined(IN_RTS)
#include <stdint.h>
#endif

#include "loongarch-def-array.h"
#include "loongarch-tune.h"

/* enum isa_base */

/* LoongArch V1.00.  */
#define ISA_BASE_LA64V100	0
#define N_ISA_BASE_TYPES	1
extern loongarch_def_array<const char *, N_ISA_BASE_TYPES>
  loongarch_isa_base_strings;

/* enum isa_ext_* */
#define ISA_EXT_NONE	      0
#define ISA_EXT_FPU32	      1
#define ISA_EXT_FPU64	      2
#define N_ISA_EXT_FPU_TYPES   3
#define ISA_EXT_SIMD_LSX      3
#define ISA_EXT_SIMD_LASX     4
#define N_ISA_EXT_TYPES	      5
extern loongarch_def_array<const char *, N_ISA_EXT_TYPES>
  loongarch_isa_ext_strings;

/* enum abi_base */
#define ABI_BASE_LP64D	      0
#define ABI_BASE_LP64F	      1
#define ABI_BASE_LP64S	      2
#define N_ABI_BASE_TYPES      3
extern loongarch_def_array<const char *, N_ABI_BASE_TYPES>
  loongarch_abi_base_strings;

#define TO_LP64_ABI_BASE(C) (C)

#define ABI_FPU_64(abi_base) \
  (abi_base == ABI_BASE_LP64D)
#define ABI_FPU_32(abi_base) \
  (abi_base == ABI_BASE_LP64F)
#define ABI_FPU_NONE(abi_base) \
  (abi_base == ABI_BASE_LP64S)


/* enum abi_ext */
#define ABI_EXT_BASE	      0
#define N_ABI_EXT_TYPES	      1
extern loongarch_def_array<const char *, N_ABI_EXT_TYPES>
  loongarch_abi_ext_strings;

/* enum cmodel */
#define CMODEL_NORMAL	      0
#define CMODEL_TINY	      1
#define CMODEL_TINY_STATIC    2
#define CMODEL_MEDIUM	      3
#define CMODEL_LARGE	      4
#define CMODEL_EXTREME	      5
#define N_CMODEL_TYPES	      6
extern loongarch_def_array<const char *, N_CMODEL_TYPES>
  loongarch_cmodel_strings;

/* enum explicit_relocs */
#define EXPLICIT_RELOCS_AUTO	0
#define EXPLICIT_RELOCS_NONE	1
#define EXPLICIT_RELOCS_ALWAYS	2
#define N_EXPLICIT_RELOCS_TYPES	3

/* The common default value for variables whose assignments
   are triggered by command-line options.  */

#define M_OPT_UNSET -1
#define M_OPT_ABSENT(opt_enum)  ((opt_enum) == M_OPT_UNSET)


/* Internal representation of the target.  */
struct loongarch_isa
{
  int base;	    /* ISA_BASE_ */
  int fpu;	    /* ISA_EXT_FPU_ */
  int simd;	    /* ISA_EXT_SIMD_ */

  /* ISA evolution features implied by -march=, for -march=native probed
     via CPUCFG.  The features implied by base may be not included here.

     Using int64_t instead of HOST_WIDE_INT for C compatibility.  */
  int64_t evolution;

  loongarch_isa () : base (0), fpu (0), simd (0), evolution (0) {}
  loongarch_isa base_ (int _base) { base = _base; return *this; }
  loongarch_isa fpu_ (int _fpu) { fpu = _fpu; return *this; }
  loongarch_isa simd_ (int _simd) { simd = _simd; return *this; }
  loongarch_isa evolution_ (int64_t _evolution)
    { evolution = _evolution; return *this; }
};

struct loongarch_abi
{
  int base;	    /* ABI_BASE_ */
  int ext;	    /* ABI_EXT_ */
};

struct loongarch_target
{
  struct loongarch_isa isa;
  struct loongarch_abi abi;
  int cpu_arch;	    /* CPU_ */
  int cpu_tune;	    /* same */
  int cmodel;	    /* CMODEL_ */
};

/* CPU properties.  */
/* index */
#define CPU_NATIVE	  0
#define CPU_ABI_DEFAULT   1
#define CPU_LOONGARCH64	  2
#define CPU_LA464	  3
#define CPU_LA664	  4
#define N_ARCH_TYPES	  5
#define N_TUNE_TYPES	  5

/* parallel tables.  */
extern loongarch_def_array<const char *, N_ARCH_TYPES>
  loongarch_cpu_strings;
extern loongarch_def_array<loongarch_isa, N_ARCH_TYPES>
  loongarch_cpu_default_isa;
extern loongarch_def_array<int, N_TUNE_TYPES>
  loongarch_cpu_issue_rate;
extern loongarch_def_array<int, N_TUNE_TYPES>
  loongarch_cpu_multipass_dfa_lookahead;
extern loongarch_def_array<loongarch_cache, N_TUNE_TYPES>
  loongarch_cpu_cache;
extern loongarch_def_array<loongarch_align, N_TUNE_TYPES>
  loongarch_cpu_align;
extern loongarch_def_array<loongarch_rtx_cost_data, N_TUNE_TYPES>
  loongarch_cpu_rtx_cost_data;

#endif /* LOONGARCH_DEF_H */
