#include "list.hpp"
#include "vector.hpp"
#include <iostream>

int main()
{
  std::cout << "Vector:" << std::endl;
  Vector<int> vector;
  for (size_t i = 0; i < 10; ++i) {
    vector.push_back( static_cast<int>( i ) );
  }
  std::cout << vector << std::endl;
  std::cout << vector.size() << std::endl;
  
  vector.erase( 6 );
  vector.erase( 4 );
  vector.erase( 2 );
  std::cout << vector << std::endl;

  vector.insert( 0, 10 );
  std::cout << vector << std::endl;

  vector.insert( 4, 20 );
  std::cout << vector << std::endl;
  
  vector.insert( 9, 30 );
  std::cout << vector << std::endl;

  std::cout << std::endl << "List:" << std::endl;

  List<int> list;
  for (size_t i = 0; i < 10; ++i) {
    list.push_back( static_cast<int>( i ) );
  }
  std::cout << list << std::endl;
  std::cout << list.size() << std::endl;
  
  list.erase( 6 );
  list.erase( 4 );
  list.erase( 2 );
  std::cout << list << std::endl;

  list.insert( 0, 10 );
  std::cout << list << std::endl;

  list.insert( 4, 20 );
  std::cout << list << std::endl;
  
  list.insert( 9, 30 );
  std::cout << list << std::endl;

  return 0;
}
