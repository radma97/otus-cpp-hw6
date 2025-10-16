#pragma once
#include <ostream>

template <typename T>
struct Node
{
  T m_data;
  Node * m_prev;
  Node * m_next;

  Node( T value ) : m_data( value ), m_prev( nullptr ), m_next( nullptr ) {}
};

template <typename T>
class List
{
  Node<T> * m_first;
  Node<T> * m_last;
  size_t m_size;

public:
  List() : m_first( nullptr ), m_last( nullptr ), m_size( 0 ) {}

  void push_back( T value )
  {
    Node<T> * newNode = new Node<T>( value );
    if ( m_first == nullptr )
    {
      m_first = newNode;
      m_last = newNode;
    }
    else
    {
      m_last->m_next = newNode;
      newNode->m_prev = m_last;
      m_last = newNode;
    }
    ++m_size;
  }

  List( const List & other ) : m_first( nullptr ), m_last( nullptr ), m_size( 0 )
  {
    Node<T> * node = other.m_first;
    while ( node != nullptr )
    {
      push_back( node->m_data );
      node = node->m_next;
    }
  }

  void clear()
  {
    Node<T> * node = m_first;
    while ( node != nullptr )
    {
      Node<T> * nextNode = node->m_next;
      delete node;
      node = nextNode;
    }
    m_first = nullptr;
    m_last = nullptr;
    m_size = 0;
  }

  List & operator=( const List & other )
  {
    if ( this != &other ) 
    {
      clear();

      Node<T> * node = other.m_first;
      while ( node != nullptr ) 
      {
        push_back( node->m_data );
        node = node->m_next;
      }
    }
    return *this;
  }

  ~List()
  {
    clear();
  }

  void insert( size_t index, T value )
  {
    if ( index > m_size )
      return;

    if ( index == m_size )
    {
      push_back( value );
      return;
    }

    Node<T> * newNode = new Node<T>( value );
    if ( index == 0 )
    {
      newNode->m_next = m_first;
      m_first->m_prev = newNode;
      m_first = newNode;
    }
    else
    {
      Node<T> * node = m_first;
      for ( size_t i = 0; i < index; ++i )
        node = node->m_next;

      newNode->m_next = node;
      newNode->m_prev = node->m_prev;
      node->m_prev->m_next = newNode;
      node->m_prev = newNode;
    }
    ++m_size;
  }

  void erase( size_t index )
  {
    if ( index >= m_size || m_size == 0 )
      return;

    Node<T> * node = m_first;
    if ( index == 0 )
    {
      m_first = m_first->m_next;
      if ( m_first != nullptr )
        m_first->m_prev = nullptr;
      else
        m_last = nullptr;
    }
    else if ( index == m_size - 1 )
    {
      node = m_last;
      m_last = m_last->m_prev;
      m_last->m_next = nullptr;
    }
    else
    {
      node = m_first;
      for ( size_t i = 0; i < index; ++i )
        node = node->m_next;

      node->m_prev->m_next = node->m_next;
      node->m_next->m_prev = node->m_prev;
    }

    delete node;
    --m_size;
  }

  size_t size() const { return m_size; }

  T & operator[]( size_t index )
  {
    Node<T> * node = m_first;
    for ( size_t i = 0; i < index; ++i )
      node = node->m_next;
    return node->m_data;
  }

  const T & operator[]( size_t index ) const
  {
    Node<T> * node = m_first;
    for ( size_t i = 0; i < index; ++i )
      node = node->m_next;
    return node->m_data;
  }

  template <typename T>
  friend std::ostream & operator<<( std::ostream & out, List<T> & list );
};

template <typename T>
std::ostream & operator<<( std::ostream & out, List<T> & list )
{
  Node<T> * node = list.m_first;
  for ( size_t i = 0, iCount = list.size(); i < iCount - 1; ++i ) {
    out << node->m_data << ", ";
    node = node->m_next;
  }
  out << node->m_data;
  
  return out; 
} 
