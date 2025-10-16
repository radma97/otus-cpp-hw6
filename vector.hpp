#pragma once
#include <ostream>

template <typename T>
class Vector
{
  T * m_data;
  size_t m_size;
  size_t m_capacity;

public:
  Vector() : m_data( nullptr ), m_size( 0 ), m_capacity( 0 ) {}

  Vector( const Vector & other ) : m_size( other.m_size ), m_capacity( other.m_capacity )
  {
    m_data = new T[m_capacity];
    std::copy( other.m_data, other.m_data + m_size, m_data );
  }

  Vector & operator = ( const Vector & other )
  {
    if ( this != &other )
    {
      delete[] m_data;
      T * m_data = new T[other.m_capacity];
      std::copy( other.m_data, other.m_data + other.m_size, m_data );
      m_size = other.m_size;
      m_capacity = other.m_capacity;
    }
    return *this;
  }

  ~Vector() { delete[] m_data; }

  void reserve( size_t capacity )
  {
    if ( capacity <= m_capacity )
      return;

    T * data = new T[capacity];
    for ( size_t i = 0; i < m_size; ++i )
      data[i] = m_data[i];
    std::copy( m_data, m_data + m_size, data );

    delete[] m_data;
    m_data = data;
    m_capacity = capacity;
  }

  void push_back( T val )
  {
    if ( m_size == m_capacity )
      reserve( ( m_capacity == 0 ) ? 1 : 2 * m_capacity );

    m_data[m_size] = val;
    ++m_size;
  }

  void insert( size_t index, T val )
  {
    if ( index > m_size )
      return;

    if ( m_size == m_capacity )
      reserve( ( m_capacity == 0 ) ? 1 : 2 * m_capacity );

    for ( size_t i = m_size; i > index; --i )
      m_data[i] = m_data[i - 1];

    m_data[index] = val;
    ++m_size;
  }

  void erase( size_t index )
  {
    if ( index >= m_size )
      return;

    for ( size_t i = index; i < m_size - 1; ++i ) {
      m_data[i] = m_data[i + 1];
    }
    --m_size;
  }

  size_t size() const { return m_size; }

  T & operator[]( size_t index ) { return m_data[index]; }

  const T & operator[]( size_t index ) const { return m_data[index]; }
};

template <typename T>
std::ostream & operator<<( std::ostream & out, Vector<T> & vector ) 
{
  size_t count = vector.size();
  for ( size_t i = 0; i < count - 1; ++i )
    out << vector[i] << ", ";
  out << vector[count - 1];
  
  return out; 
} 
