// Functions for modifing lists by reference

#include <R.h>
#include <Rdefines.h>

// Set the value of an item in a list, in-place
SEXP C_set_list_item(SEXP x, SEXP idx, SEXP value) {
  if (!isNewList(x))
    error("x must be a list");
  if (!isNumeric(idx))
    error("idx must be a numeric");

  int i = asInteger(idx);
  if (i < 1 || i > length(x))
    error("i must a number between 1 and the length of the list");

  SET_VECTOR_ELT(x, i-1, value);
  return x;
}
