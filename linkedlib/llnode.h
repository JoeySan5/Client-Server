namespace linkedlist{


    struct 
template <class T>
class Node {
  public:
    T item;
    size_t length;
    linkedlist::Node<T>* next;
    Node();
    Node(T item);
    ~Node();
};

    template <class T>
    Node<T>::Node()
    {
        this->item = 0;
        this->next = NULL;
    }
    template <class T>
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
