#' @export
#' @useDynLib rspeed C_null
R_null <- function() .Call(C_null)

#' @export
#' @useDynLib rspeed C_identity
R_identity <- function(x) .Call(C_identity, x)

# FIXME: roxygen adds quotes around .registration=TRUE in NAMESPACE, but they
#        shouldn't be there.
#' @export
#' @useDynLib rspeed .registration=TRUE
R_identity_reg <- function(x) .Call(C_identity_reg, x)
