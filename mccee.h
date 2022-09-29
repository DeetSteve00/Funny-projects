#ifndef MCCEE_H
#define MCCEE_H

/**
 *  McCee by DeetSteve00
 *      Redefined C's syntax using Macros 
 *      Completely useless and stupid
 *      In GCC use flag -E to see preprossesor output (Actual C code)
**/

#define PRICAT(a, ...) a ## __VA_ARGS__
#define CAT(a, ...) PRICAT(a, __VA_ARGS__)

#define COMMENT(...)                                                /* Just don't forget to follow string/char syntax rules and you'll be more than fine */
#define ARGS(...) __VA_ARGS__                                       /* Make more understandable syntax, probably less readable */
#define NOB ;                                                       /* No body */
#define NON
#define BEGIN {

#define END(A) END_ ## A                                            /* Weird indentation practice in macros */
#   define END_M
#   define END_S }
#   define END_R(X) return X NOB
END(M)


#define DECL(A) CAT(DECL_, A)
#   define DECL_TYPE(T) T
#   define DECL_FUN(T, N, ...) DECL(TYPE)(T) N (__VA_ARGS__)
#   define DECL_VAR(T, N, ...) DECL(TYPE)(T) N __VA_ARGS__ NOB
#   define DECL_STRCT(N, ...) DECL(TYPE)(struct N) __VA_ARGS__ NOB
#   ifdef _cplusplus
#       define DECL_CLSS(N, ...) DECL(TYPE)(class N) __VA_ARGS__ NOB
#   endif
END(M)

#define V(A) CAT(V_, A)
#   define V_SET(V, A) V = A NOB
#   define V_OP(V, O, A) V O A
#   define V_CAST(T, X) (T) X
END(M)

#define CALL(A) CAT(CALL_, A)
#   define CALL_F(F, ...) F (ARGS(__VA_ARGS__)) NOB                 /* Call function (Doesn't get return) */
#   define CALL_R(F, ...) F (ARGS(__VA_ARGS__))                     /* Gets return statement only (Is treated as a variable) */
#   define CALL_M(M) M
END(M)

#define OBJ(A) CAT(OBJ_, A)
#   define OBJ_E(E, O) O.E
#   ifdef _cplusplus
#      define OBJ_C(C, O, ...) C O __VA_ARGS__;
#      define OBJ_S(S, O, ...) struct S O __VA_ARGS__ NOB
#   else
#       define OBJ_D(S, O, ...) struct S O __VA_ARGS__ NOB
#   endif
END(M)

#define P(A) CAT(P_, A)                                          /* Pointer syntax */
#   define P_ADDR(X) &X
#   define P_DERF(X) *X
END(M)

#define GLOBL(...) DECL(FUN)(int, main, ARGS(__VA_ARGS__)) BEGIN    /* Main function */

#endif