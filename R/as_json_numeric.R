#' @export
#' @useDynLib rspeed C_as_json_numeric_collapsed
as_json_numeric_collapsed <- function(x, digits = 5,
                        round = c("signif", "decimal"),
                        na = c("string", "null")) {

  round <- match.arg(round)
  na <- match.arg(na)

  .Call(C_as_json_numeric_collapsed, x, digits, round, na)
}
