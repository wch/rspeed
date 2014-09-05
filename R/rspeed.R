#' @importFrom Rcpp cppFunction
NULL


.onUnload <- function (libpath) {
  library.dynam.unload("rspeed", libpath)
}
