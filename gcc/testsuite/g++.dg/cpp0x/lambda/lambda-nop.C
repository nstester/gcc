// { dg-do run { target c++11 } }
// { dg-skip-if "requires hosted libstdc++ for cassert" { ! hostedlib } }
#include <cassert>

int main() {
  int i = 1, j = 2;
  [i, j] () -> void {} ();
  assert(i == 1);
  assert(j == 2);
  [&i, &j] () -> void {} ();
  assert(i == 1);
  assert(j == 2);
  [] (int x) -> void {} (1);
  [] (int& x) -> void {} (i);
  [] (int x, int y) -> void {} (i, j);

  return 0;
}

