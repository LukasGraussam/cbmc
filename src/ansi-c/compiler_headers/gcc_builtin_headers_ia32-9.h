// clang-format off
// mmx
void __builtin_ia32_emms(void);
void __builtin_ia32_maskmovq(__gcc_v8qi, __gcc_v8qi, char *);
void __builtin_ia32_movntq(__gcc_v1di *, __gcc_v1di);
__gcc_v4hi __builtin_ia32_packssdw(__gcc_v2si, __gcc_v2si);
__gcc_v8qi __builtin_ia32_packsswb(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_packuswb(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_paddb(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_paddd(__gcc_v2si, __gcc_v2si);
__gcc_v8qi __builtin_ia32_paddsb(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_paddsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_paddusb(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_paddusw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_paddw(__gcc_v4hi, __gcc_v4hi);
__gcc_v1di __builtin_ia32_pand(__gcc_v1di, __gcc_v1di);
__gcc_v1di __builtin_ia32_pandn(__gcc_v1di, __gcc_v1di);
__gcc_v8qi __builtin_ia32_pcmpeqb(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_pcmpeqd(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_pcmpeqw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_pcmpgtb(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_pcmpgtd(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_pcmpgtw(__gcc_v4hi, __gcc_v4hi);
__gcc_v2si __builtin_ia32_pmaddwd(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_pmulhw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_pmullw(__gcc_v4hi, __gcc_v4hi);
__gcc_v1di __builtin_ia32_por(__gcc_v1di, __gcc_v1di);
__gcc_v2si __builtin_ia32_pslld(__gcc_v2si, __gcc_v1di);
__gcc_v2si __builtin_ia32_pslldi(__gcc_v2si, int);
__gcc_v1di __builtin_ia32_psllq(__gcc_v1di, __gcc_v1di);
__gcc_v1di __builtin_ia32_psllqi(__gcc_v1di, int);
__gcc_v4hi __builtin_ia32_psllw(__gcc_v4hi, __gcc_v1di);
__gcc_v4hi __builtin_ia32_psllwi(__gcc_v4hi, int);
__gcc_v2si __builtin_ia32_psrad(__gcc_v2si, __gcc_v1di);
__gcc_v2si __builtin_ia32_psradi(__gcc_v2si, int);
__gcc_v4hi __builtin_ia32_psraw(__gcc_v4hi, __gcc_v1di);
__gcc_v4hi __builtin_ia32_psrawi(__gcc_v4hi, int);
__gcc_v2si __builtin_ia32_psrld(__gcc_v2si, __gcc_v1di);
__gcc_v2si __builtin_ia32_psrldi(__gcc_v2si, int);
__gcc_v1di __builtin_ia32_psrlq(__gcc_v1di, __gcc_v1di);
__gcc_v1di __builtin_ia32_psrlqi(__gcc_v1di, int);
__gcc_v4hi __builtin_ia32_psrlw(__gcc_v4hi, __gcc_v1di);
__gcc_v4hi __builtin_ia32_psrlwi(__gcc_v4hi, int);
__gcc_v8qi __builtin_ia32_psubb(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_psubd(__gcc_v2si, __gcc_v2si);
__gcc_v8qi __builtin_ia32_psubsb(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_psubsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_psubusb(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_psubusw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_psubw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_punpckhbw(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_punpckhdq(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_punpckhwd(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_punpcklbw(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_punpckldq(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_punpcklwd(__gcc_v4hi, __gcc_v4hi);
__gcc_v1di __builtin_ia32_pxor(__gcc_v1di, __gcc_v1di);
int __builtin_ia32_vec_ext_v2si(__gcc_v2si, int);
__gcc_v2si __builtin_ia32_vec_init_v2si(int, int);
__gcc_v4hi __builtin_ia32_vec_init_v4hi(short, short, short, short);
__gcc_v8qi __builtin_ia32_vec_init_v8qi(char, char, char, char, char, char, char, char);
void _mm_prefetch(const char *, int);
// mmx,sse
__gcc_v4sf __builtin_ia32_cvtpi2ps(__gcc_v4sf, __gcc_v2si);
__gcc_v2si __builtin_ia32_cvtps2pi(__gcc_v4sf);
__gcc_v2si __builtin_ia32_cvttps2pi(__gcc_v4sf);
__gcc_v8qi __builtin_ia32_pavgb(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_pavgw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_pmaxsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_pmaxub(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_pminsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_pminub(__gcc_v8qi, __gcc_v8qi);
int __builtin_ia32_pmovmskb(__gcc_v8qi);
__gcc_v4hi __builtin_ia32_pmulhuw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_psadbw(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_pshufw(__gcc_v4hi, char);
int __builtin_ia32_vec_ext_v4hi(__gcc_v4hi, int);
__gcc_v4hi __builtin_ia32_vec_set_v4hi(__gcc_v4hi, int, int);
// mmx,sse2
__gcc_v2si __builtin_ia32_cvtpd2pi(__gcc_v2df);
__gcc_v2df __builtin_ia32_cvtpi2pd(__gcc_v2si);
__gcc_v2si __builtin_ia32_cvttpd2pi(__gcc_v2df);
__gcc_v1di __builtin_ia32_paddq(__gcc_v1di, __gcc_v1di);
__gcc_v1di __builtin_ia32_pmuludq(__gcc_v2si, __gcc_v2si);
__gcc_v1di __builtin_ia32_psubq(__gcc_v1di, __gcc_v1di);
// mmx,ssse3
__gcc_v8qi __builtin_ia32_pabsb(__gcc_v8qi);
__gcc_v2si __builtin_ia32_pabsd(__gcc_v2si);
__gcc_v4hi __builtin_ia32_pabsw(__gcc_v4hi);
__gcc_v8qi __builtin_ia32_palignr(__gcc_v8qi, __gcc_v8qi, char);
__gcc_v2si __builtin_ia32_phaddd(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_phaddsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_phaddw(__gcc_v4hi, __gcc_v4hi);
__gcc_v2si __builtin_ia32_phsubd(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_phsubsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v4hi __builtin_ia32_phsubw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_pmaddubsw(__gcc_v8qi, __gcc_v8qi);
__gcc_v4hi __builtin_ia32_pmulhrsw(__gcc_v4hi, __gcc_v4hi);
__gcc_v8qi __builtin_ia32_pshufb(__gcc_v8qi, __gcc_v8qi);
__gcc_v8qi __builtin_ia32_psignb(__gcc_v8qi, __gcc_v8qi);
__gcc_v2si __builtin_ia32_psignd(__gcc_v2si, __gcc_v2si);
__gcc_v4hi __builtin_ia32_psignw(__gcc_v4hi, __gcc_v4hi);
// movdir64b
void __builtin_ia32_movdir64b(void *, const void *);
// movdiri
void __builtin_ia32_directstore_u32(unsigned int *, unsigned int);
void __builtin_ia32_directstore_u64(unsigned long int *, unsigned long int);
// mwaitx
void __builtin_ia32_monitorx(const void *, unsigned int, unsigned int);
void __builtin_ia32_mwaitx(unsigned int, unsigned int, unsigned int);
// pclmul
__gcc_v2di __builtin_ia32_pclmulqdq128(__gcc_v2di, __gcc_v2di, char);
// pku
unsigned int __builtin_ia32_rdpkru(void);
void __builtin_ia32_wrpkru(unsigned int);
// prefetchi
void __builtin_ia32_prefetchi(const void *, unsigned int);
// ptwrite
void __builtin_ia32_ptwrite32(unsigned int);
void __builtin_ia32_ptwrite64(unsigned long long int);
// raoint
void __builtin_ia32_aadd32(void *, signed int);
void __builtin_ia32_aadd64(void *, signed long long int);
void __builtin_ia32_aand32(void *, signed int);
void __builtin_ia32_aand64(void *, signed long long int);
void __builtin_ia32_aor32(void *, signed int);
void __builtin_ia32_aor64(void *, signed long long int);
void __builtin_ia32_axor32(void *, signed int);
void __builtin_ia32_axor64(void *, signed long long int);
// rdpid
unsigned int __builtin_ia32_rdpid(void);
// rdpru
unsigned long long int __builtin_ia32_rdpru(int);
// rdrnd
unsigned int __builtin_ia32_rdrand16_step(unsigned short *);
unsigned int __builtin_ia32_rdrand32_step(unsigned int *);
unsigned int __builtin_ia32_rdrand64_step(unsigned long long int *);
// rdseed
unsigned int __builtin_ia32_rdseed16_step(unsigned short *);
unsigned int __builtin_ia32_rdseed32_step(unsigned int *);
unsigned int __builtin_ia32_rdseed64_step(unsigned long long int *);
// rtm
void __builtin_ia32_xabort(char);
int __builtin_ia32_xbegin(void);
void __builtin_ia32_xend(void);
int __builtin_ia32_xtest(void);
// serialize
void __builtin_ia32_serialize(void);
// sha
__gcc_v4si __builtin_ia32_sha1msg1(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_sha1msg2(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_sha1nexte(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_sha1rnds4(__gcc_v4si, __gcc_v4si, char);
__gcc_v4si __builtin_ia32_sha256msg1(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_sha256msg2(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_sha256rnds2(__gcc_v4si, __gcc_v4si, __gcc_v4si);
// sha512
__gcc_v4udi __builtin_ia32_vsha512msg1(__gcc_v4udi, __gcc_v2udi);
__gcc_v4udi __builtin_ia32_vsha512msg2(__gcc_v4udi, __gcc_v4udi);
__gcc_v4udi __builtin_ia32_vsha512rnds2(__gcc_v4udi, __gcc_v4udi, __gcc_v2udi);
// shstk
void __builtin_ia32_clrssbsy(void *);
void __builtin_ia32_incsspd(unsigned int);
void __builtin_ia32_incsspq(unsigned long long int);
unsigned int __builtin_ia32_rdsspd(unsigned int);
unsigned long long int __builtin_ia32_rdsspq(unsigned long long int);
void __builtin_ia32_rstorssp(void *);
void __builtin_ia32_saveprevssp(void);
void __builtin_ia32_setssbsy(void);
void __builtin_ia32_wrssd(unsigned int, void *);
void __builtin_ia32_wrssq(unsigned long long int, void *);
void __builtin_ia32_wrussd(unsigned int, void *);
void __builtin_ia32_wrussq(unsigned long long int, void *);
// sm3
__gcc_v4usi __builtin_ia32_vsm3msg1(__gcc_v4usi, __gcc_v4usi, __gcc_v4usi);
__gcc_v4usi __builtin_ia32_vsm3msg2(__gcc_v4usi, __gcc_v4usi, __gcc_v4usi);
__gcc_v4usi __builtin_ia32_vsm3rnds2(__gcc_v4usi, __gcc_v4usi, __gcc_v4usi, unsigned int);
// sm4
__gcc_v4usi __builtin_ia32_vsm4key4128(__gcc_v4usi, __gcc_v4usi);
__gcc_v8usi __builtin_ia32_vsm4key4256(__gcc_v8usi, __gcc_v8usi);
__gcc_v4usi __builtin_ia32_vsm4rnds4128(__gcc_v4usi, __gcc_v4usi);
__gcc_v8usi __builtin_ia32_vsm4rnds4256(__gcc_v8usi, __gcc_v8usi);
// sse
__gcc_v4sf __builtin_ia32_cmpeqps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpeqss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpleps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpless(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpltps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpltss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpneqps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpneqss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpnleps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpnless(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpnltps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpnltss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpordps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpordss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpps(__gcc_v4sf, __gcc_v4sf, char);
__gcc_v4sf __builtin_ia32_cmpss(__gcc_v4sf, __gcc_v4sf, char);
__gcc_v4sf __builtin_ia32_cmpunordps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_cmpunordss(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comieq(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comige(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comigt(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comile(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comilt(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_comineq(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_cvtss2si(__gcc_v4sf);
long long int __builtin_ia32_cvtss2si64(__gcc_v4sf);
int __builtin_ia32_cvttss2si(__gcc_v4sf);
long long int __builtin_ia32_cvttss2si64(__gcc_v4sf);
void __builtin_ia32_ldmxcsr(unsigned int);
__gcc_v4sf __builtin_ia32_maxps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_maxss(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_minps(__gcc_v4sf, __gcc_v4sf);
__gcc_v4sf __builtin_ia32_minss(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_movmskps(__gcc_v4sf);
__gcc_v4sf __builtin_ia32_rcpps(__gcc_v4sf);
__gcc_v4sf __builtin_ia32_rcpss(__gcc_v4sf);
__gcc_v4sf __builtin_ia32_rsqrtps(__gcc_v4sf);
__gcc_v4sf __builtin_ia32_rsqrtss(__gcc_v4sf);
void __builtin_ia32_sfence(void);
__gcc_v4sf __builtin_ia32_shufps(__gcc_v4sf, __gcc_v4sf, int);
__gcc_v4sf __builtin_ia32_sqrtps(__gcc_v4sf);
__gcc_v4sf __builtin_ia32_sqrtss(__gcc_v4sf);
unsigned int __builtin_ia32_stmxcsr(void);
int __builtin_ia32_ucomieq(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_ucomige(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_ucomigt(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_ucomile(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_ucomilt(__gcc_v4sf, __gcc_v4sf);
int __builtin_ia32_ucomineq(__gcc_v4sf, __gcc_v4sf);
// sse2
void __builtin_ia32_clflush(const void *);
__gcc_v2df __builtin_ia32_cmpeqpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpeqsd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmplepd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmplesd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpltpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpltsd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpneqpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpneqsd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpnlepd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpnlesd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpnltpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpnltsd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpordpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpordsd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmppd(__gcc_v2df, __gcc_v2df, char);
__gcc_v2df __builtin_ia32_cmpsd(__gcc_v2df, __gcc_v2df, char);
__gcc_v2df __builtin_ia32_cmpunordpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_cmpunordsd(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdeq(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdge(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdgt(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdle(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdlt(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_comisdneq(__gcc_v2df, __gcc_v2df);
__gcc_v2di __builtin_ia32_cvtpd2dq(__gcc_v2df);
__gcc_v4sf __builtin_ia32_cvtpd2ps(__gcc_v2df);
__gcc_v4si __builtin_ia32_cvtps2dq(__gcc_v4sf);
int __builtin_ia32_cvtsd2si(__gcc_v2df);
long long int __builtin_ia32_cvtsd2si64(__gcc_v2df);
__gcc_v4sf __builtin_ia32_cvtsd2ss(__gcc_v4sf, __gcc_v2df);
__gcc_v4si __builtin_ia32_cvttpd2dq(__gcc_v2df);
__gcc_v4si __builtin_ia32_cvttps2dq(__gcc_v4sf);
int __builtin_ia32_cvttsd2si(__gcc_v2df);
long long int __builtin_ia32_cvttsd2si64(__gcc_v2df);
void __builtin_ia32_lfence(void);
void __builtin_ia32_maskmovdqu(__gcc_v16qi, __gcc_v16qi, char *);
__gcc_v2df __builtin_ia32_maxpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_maxsd(__gcc_v2df, __gcc_v2df);
void __builtin_ia32_mfence(void);
__gcc_v2df __builtin_ia32_minpd(__gcc_v2df, __gcc_v2df);
__gcc_v2df __builtin_ia32_minsd(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_movmskpd(__gcc_v2df);
void __builtin_ia32_movnti(int *, int);
void __builtin_ia32_movnti64(long long int *, long long int);
__gcc_v8hi __builtin_ia32_packssdw128(__gcc_v4si, __gcc_v4si);
__gcc_v16qi __builtin_ia32_packsswb128(__gcc_v8hi, __gcc_v8hi);
__gcc_v16qi __builtin_ia32_packuswb128(__gcc_v8hi, __gcc_v8hi);
__gcc_v16qi __builtin_ia32_pavgb128(__gcc_v16qi, __gcc_v16qi);
__gcc_v8hi __builtin_ia32_pavgw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v4si __builtin_ia32_pmaddwd128(__gcc_v8hi, __gcc_v8hi);
int __builtin_ia32_pmovmskb128(__gcc_v16qi);
__gcc_v8hi __builtin_ia32_pmulhuw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_pmulhw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v2di __builtin_ia32_pmuludq128(__gcc_v4si, __gcc_v4si);
__gcc_v2di __builtin_ia32_psadbw128(__gcc_v16qi, __gcc_v16qi);
__gcc_v4si __builtin_ia32_pshufd(__gcc_v4si, int);
__gcc_v8hi __builtin_ia32_pshufhw(__gcc_v8hi, int);
__gcc_v8hi __builtin_ia32_pshuflw(__gcc_v8hi, int);
__gcc_v4si __builtin_ia32_pslld128(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_pslldi128(__gcc_v4si, int);
__gcc_v2di __builtin_ia32_pslldqi128_byteshift(__gcc_v2di, int);
__gcc_v2di __builtin_ia32_psllq128(__gcc_v2di, __gcc_v2di);
__gcc_v2di __builtin_ia32_psllqi128(__gcc_v2di, int);
__gcc_v8hi __builtin_ia32_psllw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_psllwi128(__gcc_v8hi, int);
__gcc_v4si __builtin_ia32_psrad128(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_psradi128(__gcc_v4si, int);
__gcc_v8hi __builtin_ia32_psraw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_psrawi128(__gcc_v8hi, int);
__gcc_v4si __builtin_ia32_psrld128(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_psrldi128(__gcc_v4si, int);
__gcc_v2di __builtin_ia32_psrldqi128_byteshift(__gcc_v2di, int);
__gcc_v2di __builtin_ia32_psrlq128(__gcc_v2di, __gcc_v2di);
__gcc_v2di __builtin_ia32_psrlqi128(__gcc_v2di, int);
__gcc_v8hi __builtin_ia32_psrlw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_psrlwi128(__gcc_v8hi, int);
__gcc_v2df __builtin_ia32_shufpd(__gcc_v2df, __gcc_v2df, int);
__gcc_v2df __builtin_ia32_sqrtpd(__gcc_v2df);
__gcc_v2df __builtin_ia32_sqrtsd(__gcc_v2df);
int __builtin_ia32_ucomisdeq(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_ucomisdge(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_ucomisdgt(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_ucomisdle(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_ucomisdlt(__gcc_v2df, __gcc_v2df);
int __builtin_ia32_ucomisdneq(__gcc_v2df, __gcc_v2df);
long long int __builtin_ia32_vec_ext_v2di(__gcc_v2di, int);
float __builtin_ia32_vec_ext_v4sf(__gcc_v4sf, int);
int __builtin_ia32_vec_ext_v4si(__gcc_v4si, int);
short __builtin_ia32_vec_ext_v8hi(__gcc_v8hi, int);
__gcc_v8hi __builtin_ia32_vec_set_v8hi(__gcc_v8hi, short, int);
// sse3
__gcc_v2df __builtin_ia32_addsubpd(__gcc_v2df, __gcc_v2df);
__gcc_v4sf __builtin_ia32_addsubps(__gcc_v4sf, __gcc_v4sf);
__gcc_v2df __builtin_ia32_haddpd(__gcc_v2df, __gcc_v2df);
__gcc_v4sf __builtin_ia32_haddps(__gcc_v4sf, __gcc_v4sf);
__gcc_v2df __builtin_ia32_hsubpd(__gcc_v2df, __gcc_v2df);
__gcc_v4sf __builtin_ia32_hsubps(__gcc_v4sf, __gcc_v4sf);
__gcc_v16qi __builtin_ia32_lddqu(const char *);
void __builtin_ia32_monitor(const void *, unsigned int, unsigned int);
void __builtin_ia32_mwait(unsigned int, unsigned int);
// sse4.1
__gcc_v2df __builtin_ia32_blendpd(__gcc_v2df, __gcc_v2df, int);
__gcc_v4sf __builtin_ia32_blendps(__gcc_v4sf, __gcc_v4sf, int);
__gcc_v2df __builtin_ia32_blendvpd(__gcc_v2df, __gcc_v2df, __gcc_v2df);
__gcc_v4sf __builtin_ia32_blendvps(__gcc_v4sf, __gcc_v4sf, __gcc_v4sf);
__gcc_v2df __builtin_ia32_dppd(__gcc_v2df, __gcc_v2df, char);
__gcc_v4sf __builtin_ia32_dpps(__gcc_v4sf, __gcc_v4sf, char);
__gcc_v4sf __builtin_ia32_insertps128(__gcc_v4sf, __gcc_v4sf, char);
__gcc_v16qi __builtin_ia32_mpsadbw128(__gcc_v16qi, __gcc_v16qi, char);
__gcc_v8hi __builtin_ia32_packusdw128(__gcc_v4si, __gcc_v4si);
__gcc_v16qi __builtin_ia32_pblendvb128(__gcc_v16qi, __gcc_v16qi, __gcc_v16qi);
__gcc_v8hi __builtin_ia32_pblendw128(__gcc_v8hi, __gcc_v8hi, int);
__gcc_v8hi __builtin_ia32_phminposuw128(__gcc_v8hi);
__gcc_v2di __builtin_ia32_pmuldq128(__gcc_v4si, __gcc_v4si);
int __builtin_ia32_ptestc128(__gcc_v2di, __gcc_v2di);
int __builtin_ia32_ptestnzc128(__gcc_v2di, __gcc_v2di);
int __builtin_ia32_ptestz128(__gcc_v2di, __gcc_v2di);
__gcc_v2df __builtin_ia32_roundpd(__gcc_v2df, int);
__gcc_v4sf __builtin_ia32_roundps(__gcc_v4sf, int);
__gcc_v2df __builtin_ia32_roundsd(__gcc_v2df, __gcc_v2df, int);
__gcc_v4sf __builtin_ia32_roundss(__gcc_v4sf, __gcc_v4sf, int);
char __builtin_ia32_vec_ext_v16qi(__gcc_v16qi, int);
__gcc_v16qi __builtin_ia32_vec_set_v16qi(__gcc_v16qi, char, int);
__gcc_v2di __builtin_ia32_vec_set_v2di(__gcc_v2di, long long int, int);
__gcc_v4si __builtin_ia32_vec_set_v4si(__gcc_v4si, int, int);
// sse4.2
int __builtin_ia32_pcmpestri128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpestria128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpestric128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpestrio128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpestris128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpestriz128(__gcc_v16qi, int, __gcc_v16qi, int, char);
__gcc_v16qi __builtin_ia32_pcmpestrm128(__gcc_v16qi, int, __gcc_v16qi, int, char);
int __builtin_ia32_pcmpistri128(__gcc_v16qi, __gcc_v16qi, char);
int __builtin_ia32_pcmpistria128(__gcc_v16qi, __gcc_v16qi, char);
int __builtin_ia32_pcmpistric128(__gcc_v16qi, __gcc_v16qi, char);
int __builtin_ia32_pcmpistrio128(__gcc_v16qi, __gcc_v16qi, char);
int __builtin_ia32_pcmpistris128(__gcc_v16qi, __gcc_v16qi, char);
int __builtin_ia32_pcmpistriz128(__gcc_v16qi, __gcc_v16qi, char);
__gcc_v16qi __builtin_ia32_pcmpistrm128(__gcc_v16qi, __gcc_v16qi, char);
// sse4a
__gcc_v2di __builtin_ia32_extrq(__gcc_v2di, __gcc_v16qi);
__gcc_v2di __builtin_ia32_extrqi(__gcc_v2di, char, char);
__gcc_v2di __builtin_ia32_insertq(__gcc_v2di, __gcc_v2di);
__gcc_v2di __builtin_ia32_insertqi(__gcc_v2di, __gcc_v2di, char, char);
void __builtin_ia32_movntsd(double *, __gcc_v2df);
void __builtin_ia32_movntss(float *, __gcc_v4sf);
// ssse3
__gcc_v16qi __builtin_ia32_palignr128(__gcc_v16qi, __gcc_v16qi, int);
__gcc_v4si __builtin_ia32_phaddd128(__gcc_v4si, __gcc_v4si);
__gcc_v8hi __builtin_ia32_phaddsw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_phaddw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v4si __builtin_ia32_phsubd128(__gcc_v4si, __gcc_v4si);
__gcc_v8hi __builtin_ia32_phsubsw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_phsubw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_pmaddubsw128(__gcc_v16qi, __gcc_v16qi);
__gcc_v8hi __builtin_ia32_pmulhrsw128(__gcc_v8hi, __gcc_v8hi);
__gcc_v16qi __builtin_ia32_pshufb128(__gcc_v16qi, __gcc_v16qi);
__gcc_v16qi __builtin_ia32_psignb128(__gcc_v16qi, __gcc_v16qi);
__gcc_v4si __builtin_ia32_psignd128(__gcc_v4si, __gcc_v4si);
__gcc_v8hi __builtin_ia32_psignw128(__gcc_v8hi, __gcc_v8hi);
// tbm
unsigned int __builtin_ia32_bextri_u32(unsigned int, unsigned int);
unsigned long long int __builtin_ia32_bextri_u64(unsigned long long int, unsigned long long int);
// tsxldtrk
void __builtin_ia32_xresldtrk(void);
void __builtin_ia32_xsusldtrk(void);
// uintr
void __builtin_ia32_clui(void);
void __builtin_ia32_senduipi(unsigned int64_t);
void __builtin_ia32_stui(void);
unsigned char __builtin_ia32_testui(void);
// usermsr
unsigned long long int __builtin_ia32_urdmsr(unsigned long long int);
void __builtin_ia32_uwrmsr(unsigned long long int, unsigned long long int);
// vaes
__gcc_v4di __builtin_ia32_aesdec256(__gcc_v4di, __gcc_v4di);
__gcc_v4di __builtin_ia32_aesdeclast256(__gcc_v4di, __gcc_v4di);
__gcc_v4di __builtin_ia32_aesenc256(__gcc_v4di, __gcc_v4di);
__gcc_v4di __builtin_ia32_aesenclast256(__gcc_v4di, __gcc_v4di);
// vpclmulqdq
__gcc_v4di __builtin_ia32_pclmulqdq256(__gcc_v4di, __gcc_v4di, char);
// waitpkg
unsigned char __builtin_ia32_tpause(unsigned int, unsigned int, unsigned int);
void __builtin_ia32_umonitor(const void *);
unsigned char __builtin_ia32_umwait(unsigned int, unsigned int, unsigned int);
// wbnoinvd
void __builtin_ia32_wbnoinvd(void);
// xop
__gcc_v2df __builtin_ia32_vfrczpd(__gcc_v2df);
__gcc_v4df __builtin_ia32_vfrczpd256(__gcc_v4df);
__gcc_v4sf __builtin_ia32_vfrczps(__gcc_v4sf);
__gcc_v8sf __builtin_ia32_vfrczps256(__gcc_v8sf);
__gcc_v2df __builtin_ia32_vfrczsd(__gcc_v2df);
__gcc_v4sf __builtin_ia32_vfrczss(__gcc_v4sf);
__gcc_v16qi __builtin_ia32_vpcomb(__gcc_v16qi, __gcc_v16qi, char);
__gcc_v4si __builtin_ia32_vpcomd(__gcc_v4si, __gcc_v4si, char);
__gcc_v2di __builtin_ia32_vpcomq(__gcc_v2di, __gcc_v2di, char);
__gcc_v16qi __builtin_ia32_vpcomub(__gcc_v16qi, __gcc_v16qi, char);
__gcc_v4si __builtin_ia32_vpcomud(__gcc_v4si, __gcc_v4si, char);
__gcc_v2di __builtin_ia32_vpcomuq(__gcc_v2di, __gcc_v2di, char);
__gcc_v8hi __builtin_ia32_vpcomuw(__gcc_v8hi, __gcc_v8hi, char);
__gcc_v8hi __builtin_ia32_vpcomw(__gcc_v8hi, __gcc_v8hi, char);
__gcc_v2df __builtin_ia32_vpermil2pd(__gcc_v2df, __gcc_v2df, __gcc_v2di, char);
__gcc_v4df __builtin_ia32_vpermil2pd256(__gcc_v4df, __gcc_v4df, __gcc_v4di, char);
__gcc_v4sf __builtin_ia32_vpermil2ps(__gcc_v4sf, __gcc_v4sf, __gcc_v4si, char);
__gcc_v8sf __builtin_ia32_vpermil2ps256(__gcc_v8sf, __gcc_v8sf, __gcc_v8si, char);
__gcc_v4si __builtin_ia32_vphaddbd(__gcc_v16qi);
__gcc_v2di __builtin_ia32_vphaddbq(__gcc_v16qi);
__gcc_v8hi __builtin_ia32_vphaddbw(__gcc_v16qi);
__gcc_v2di __builtin_ia32_vphadddq(__gcc_v4si);
__gcc_v4si __builtin_ia32_vphaddubd(__gcc_v16qi);
__gcc_v2di __builtin_ia32_vphaddubq(__gcc_v16qi);
__gcc_v8hi __builtin_ia32_vphaddubw(__gcc_v16qi);
__gcc_v2di __builtin_ia32_vphaddudq(__gcc_v4si);
__gcc_v4si __builtin_ia32_vphadduwd(__gcc_v8hi);
__gcc_v2di __builtin_ia32_vphadduwq(__gcc_v8hi);
__gcc_v4si __builtin_ia32_vphaddwd(__gcc_v8hi);
__gcc_v2di __builtin_ia32_vphaddwq(__gcc_v8hi);
__gcc_v8hi __builtin_ia32_vphsubbw(__gcc_v16qi);
__gcc_v2di __builtin_ia32_vphsubdq(__gcc_v4si);
__gcc_v4si __builtin_ia32_vphsubwd(__gcc_v8hi);
__gcc_v4si __builtin_ia32_vpmacsdd(__gcc_v4si, __gcc_v4si, __gcc_v4si);
__gcc_v2di __builtin_ia32_vpmacsdqh(__gcc_v4si, __gcc_v4si, __gcc_v2di);
__gcc_v2di __builtin_ia32_vpmacsdql(__gcc_v4si, __gcc_v4si, __gcc_v2di);
__gcc_v4si __builtin_ia32_vpmacssdd(__gcc_v4si, __gcc_v4si, __gcc_v4si);
__gcc_v2di __builtin_ia32_vpmacssdqh(__gcc_v4si, __gcc_v4si, __gcc_v2di);
__gcc_v2di __builtin_ia32_vpmacssdql(__gcc_v4si, __gcc_v4si, __gcc_v2di);
__gcc_v4si __builtin_ia32_vpmacsswd(__gcc_v8hi, __gcc_v8hi, __gcc_v4si);
__gcc_v8hi __builtin_ia32_vpmacssww(__gcc_v8hi, __gcc_v8hi, __gcc_v8hi);
__gcc_v4si __builtin_ia32_vpmacswd(__gcc_v8hi, __gcc_v8hi, __gcc_v4si);
__gcc_v8hi __builtin_ia32_vpmacsww(__gcc_v8hi, __gcc_v8hi, __gcc_v8hi);
__gcc_v4si __builtin_ia32_vpmadcsswd(__gcc_v8hi, __gcc_v8hi, __gcc_v4si);
__gcc_v4si __builtin_ia32_vpmadcswd(__gcc_v8hi, __gcc_v8hi, __gcc_v4si);
__gcc_v16qi __builtin_ia32_vpperm(__gcc_v16qi, __gcc_v16qi, __gcc_v16qi);
__gcc_v16qi __builtin_ia32_vprotb(__gcc_v16qi, __gcc_v16qi);
__gcc_v16qi __builtin_ia32_vprotbi(__gcc_v16qi, char);
__gcc_v4si __builtin_ia32_vprotd(__gcc_v4si, __gcc_v4si);
__gcc_v4si __builtin_ia32_vprotdi(__gcc_v4si, char);
__gcc_v2di __builtin_ia32_vprotq(__gcc_v2di, __gcc_v2di);
__gcc_v2di __builtin_ia32_vprotqi(__gcc_v2di, char);
__gcc_v8hi __builtin_ia32_vprotw(__gcc_v8hi, __gcc_v8hi);
__gcc_v8hi __builtin_ia32_vprotwi(__gcc_v8hi, char);
__gcc_v16qi __builtin_ia32_vpshab(__gcc_v16qi, __gcc_v16qi);
__gcc_v4si __builtin_ia32_vpshad(__gcc_v4si, __gcc_v4si);
__gcc_v2di __builtin_ia32_vpshaq(__gcc_v2di, __gcc_v2di);
__gcc_v8hi __builtin_ia32_vpshaw(__gcc_v8hi, __gcc_v8hi);
__gcc_v16qi __builtin_ia32_vpshlb(__gcc_v16qi, __gcc_v16qi);
__gcc_v4si __builtin_ia32_vpshld(__gcc_v4si, __gcc_v4si);
__gcc_v2di __builtin_ia32_vpshlq(__gcc_v2di, __gcc_v2di);
__gcc_v8hi __builtin_ia32_vpshlw(__gcc_v8hi, __gcc_v8hi);
// xsave
unsigned long long int __builtin_ia32_xgetbv(unsigned int);
void __builtin_ia32_xrstor(void *, unsigned long long int);
void __builtin_ia32_xrstor64(void *, unsigned long long int);
void __builtin_ia32_xsave(void *, unsigned long long int);
void __builtin_ia32_xsave64(void *, unsigned long long int);
void __builtin_ia32_xsetbv(unsigned int, unsigned long long int);
// xsavec
void __builtin_ia32_xsavec(void *, unsigned long long int);
void __builtin_ia32_xsavec64(void *, unsigned long long int);
// xsaveopt
void __builtin_ia32_xsaveopt(void *, unsigned long long int);
void __builtin_ia32_xsaveopt64(void *, unsigned long long int);
// xsaves
void __builtin_ia32_xrstors(void *, unsigned long long int);
void __builtin_ia32_xrstors64(void *, unsigned long long int);
void __builtin_ia32_xsaves(void *, unsigned long long int);
void __builtin_ia32_xsaves64(void *, unsigned long long int);
// clang-format on
