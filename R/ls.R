#' @export
#' @useDynLib rspeed C_ls
R_ls <- function(x) .Call(C_ls, x)
