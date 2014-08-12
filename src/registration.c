// A set of very simple functions that are used for testing function call
// overhead
#include <R.h>
#include <Rdefines.h>
#include <R_ext/Rdynload.h>


SEXP C_null() {
  return R_NilValue;
}

SEXP C_identity(SEXP x) {
  return x;
}

// Like C_identity, but this one will be a registered routine
SEXP C_identity_reg(SEXP x) {
  return x;
}

// Register the routines
static const R_CallMethodDef callMethods[] = {
  {"C_identity_reg", (DL_FUNC) &C_identity_reg, 1},
  {NULL, NULL, 0}
};

void R_init_rspeed(DllInfo *info) {
   R_registerRoutines(info, NULL, callMethods, NULL, NULL);
}


// In NAMESPACE:
// useDynLib(qstack,C_identity)
// useDynLib(qstack, .registration = TRUE)

// Testing:
//
// library(microbenchmark)
// microbenchmark(
//   .Call("C_identity", 1, TRUE),
//   .Call("C_identity", 1, TRUE, package = "qstack"),
//   .Call(C_identity, 1, TRUE),
//   .Call(C_identity_reg, 1, TRUE)
// )
