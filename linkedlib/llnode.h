#include <utility>


namespace linkedlist{


template <class K, class V>
class Node {
  public:
    std::pair<K,V> pair;
    size_t length;
    linkedlist::Node<K,V>* next;
    Node();
    Node(K key, V value);
    ~Node();
};

    template <class K, class V>
    Node<T>::Node()
    {
        this->item;
        this->next = NULL;
    }
    template <class K, class V>
    Node<T>::Node(T item)
    {
        this->item = item;
        this->next = NULL;
    }
    template <class T>
    Node<T>::~Node()
    {

    }
}
