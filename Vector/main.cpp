#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector (100);
  std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.at(-1);
  std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';
  myvector.shrink_to_fit();

  std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';

  return 0;
}