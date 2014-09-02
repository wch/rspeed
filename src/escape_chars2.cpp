#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::string escape_one(std::string x) {
  std::string out = "\"";

  int n = x.size();
  for (int i = 0; i < n; ++i) {
    char cur = x[i];

    switch(cur) {
      case '\\': out += "\\\\"; break;
      case '"':  out += "\\\""; break;
      case '\n': out += "\\n";  break;
      case '\r': out += "\\r";  break;
      case '\t': out += "\\t";  break;
      case '\b': out += "\\b";  break;
      case '\f': out += "\\f";  break;
      default:     out += cur;
    }
  }

  out += '"';

  return out;
}

//' @export
// [[Rcpp::export]]
CharacterVector escape_chars_cpp(CharacterVector x) {
  int n = x.size();
  CharacterVector out(n);

  for (int i = 0; i < n; ++i) {
    String cur = x[i];
    out[i] = escape_one(cur);
  }

  return out;
}
