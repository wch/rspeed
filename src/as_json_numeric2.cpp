#include <Rcpp.h>
using namespace Rcpp;

int strip_trailing_zeros(char* str, int len) {
  int len_tmp = len; // Tentative end of string, while trying to remove trailing 0's
  char tmp;

  while(1) {
    if (len_tmp == 0) {
      // We've backed all the way to the beginning and there was no decimal.
      break;
    }

    tmp = str[len_tmp-1];
    if (tmp == '0') {
      len_tmp--;
    } else if (tmp == '.') {
      len = len_tmp - 1;
      break;
    } else {
      len = len_tmp;
      break;
    }
  }

  // If the output was "-0", replace it with "0"
  if (len == 2 && str[0] == '-' && str[1] == '0') {
    str[0] = '0';
    len = 1;
  }

  str[len] = '\0';
  return len;
}


//' @export
// [[Rcpp::export]]
CharacterVector asJSONNumeric(NumericVector x, int digits = 3, int precision = 0) {
  int n = x.size();

  std::string out = "[";

  char format_str[20];
  if (digits > 0)
    snprintf(format_str, 20, "%%.%d%s", digits, "f");
  else if (precision > 0)
    snprintf(format_str, 20, "%%.%d%s", precision, "g");
 
  char buf[100];
  int inc;
  for (int i = 0; i < n; i++) {
    inc = snprintf(buf, 100, format_str, x[i]);
    strip_trailing_zeros(buf, inc);
    out += buf;
    out += ",";
  }

  // Replace last ',' with ']'
  out.replace(out.size()-1, 1, "]");

  return out;
}
