#' @export
#' @useDynLib rspeed C_escape_chars
escape_chars_ <- function(x) .Call(C_escape_chars, x)
