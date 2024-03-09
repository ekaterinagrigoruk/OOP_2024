#include "circularbuffer.h"

template <class T>
CircularBuffer<T>::~CircularBuffer() {
    this->clear();
}

template <class T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer<T>& cb) {
    head_ = cb.head_;
    tail_ = cb.tail_;
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    buffer_ = new T[cb.capacity_];
    for(int i = 0; i < cb.size_; i++) {
        buffer_[i] = cb.buffer_[i];
    }
}

template <class T>
CircularBuffer<T>::CircularBuffer(int capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
    buffer_ = new T[capacity_];
}

template <class T>
CircularBuffer<T>::CircularBuffer(int capacity, const T& elem) : capacity_(capacity), size_(capacity), head_(0), tail_(capacity - 1) {
    buffer_ = new T[capacity_];
    for (int i = 0; i < capacity_; i++) {
        buffer_[i] = elem;
    }
}

template <class T>
T& CircularBuffer<T>::operator[](int i) {
    return buffer_[(head_ + i) % capacity_];
}

template <class T>
const T& CircularBuffer<T>::operator[](int i) const {
    return buffer_[(head_ + i) % capacity_];
}

template <class T>
T& CircularBuffer<T>::at(int i) {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[(head_ + i) % capacity_];
}

template <class T>
const T& CircularBuffer<T>::at(int i) const {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[(head_ + i) % capacity_];
}

template <class T>
T& CircularBuffer<T>::front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

template <class T>
T& CircularBuffer<T>::back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_];
}

template <class T>
const T& CircularBuffer<T>::front() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

template <class T>
const T& CircularBuffer<T>::back() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_];
}

template <class T>
T* CircularBuffer<T>::linearize() {
    if (head_ == 0 && tail_ == size_ - 1) {
        return buffer_;
    }
    if (this->empty()) {
        return nullptr;
    }
    T* linearized_buffer = new T[capacity_];
    int index = head_;
    for (int i = 0; i < size_; ++i) {
        linearized_buffer[i] = buffer_[index];
        index = (index + 1) % capacity_;
    }
    return linearized_buffer;
}

template <class T>
bool CircularBuffer<T>::is_linearized() const {
    return head_ == 0 && tail_ == size_ - 1;
}

template <class T>
void CircularBuffer<T>::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= size_) {
        throw CircularBufferError("Invalid new_begin value");
    }
    head_ = (head_ + new_begin) % capacity_;
    tail_ = (tail_ + new_begin) % capacity_;
}

template <class T>
int CircularBuffer<T>::size() const {
    return size_;
}

template <class T>
bool CircularBuffer<T>::empty() const {
    return size_ == 0;
}

template <class T>
bool CircularBuffer<T>::full() const {
    return size_ == capacity_;
}

template <class T>
int CircularBuffer<T>::reserve() const {
    return capacity_ - size_;
}

template <class T>
int CircularBuffer<T>::capacity() const {
    return capacity_;
}

template <class T>
void CircularBuffer<T>::set_capacity(int new_capacity) {
    if (new_capacity < size_) {
        throw CircularBufferError("New capacity is smaller than current size");
    }
    T* new_buffer = new T[new_capacity];
    for (int i = 0; i < size_; i++) {
        new_buffer[i] = buffer_[(head_ + i) % capacity_];
    }
    this->clear();
    buffer_ = new_buffer;
    capacity_ = new_capacity;
    head_ = 0;
    tail_ = size_ - 1;
}

template <class T>
void CircularBuffer<T>::resize(int new_size, const T& item) {
    if (new_size < 0 || new_size > capacity_) {
        throw CircularBufferError("Wrong size");
    }
    if (new_size > size_) {
        for (int i = size_; i < new_size; i++) {
            this->push_back(item);
        }
    } else if (new_size < size_) {
        size_ = new_size;
        tail_ = (head_ + new_size - 1) % capacity_;
    }
}

template <class T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer<T>& cb) {
    if (this != &cb) {
        head_ = cb.head_;
        tail_ = cb.tail_;
        capacity_ = cb.capacity_;
        size_ = cb.size_;
        delete[] buffer_;
        buffer_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            buffer_[i] = cb.buffer_[i];
        }
    }
    return *this;
}

template <class T>
void CircularBuffer<T>::swap(CircularBuffer<T>& cb) {
    std::swap(buffer_, cb.buffer_);
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    head_ = cb.head_;
    tail_ = cb.tail_;
}

template <class T>
void CircularBuffer<T>::push_back(const T& item) {
    if (size_ < capacity_) {
        buffer_[(tail_++) % capacity_] = item;
        size_++;
    } else {
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        tail_ = (tail_ + 1) % capacity_;
    }
}

template <class T>
void CircularBuffer<T>::push_front(const T& item) {
    if (size_ < capacity_) {
        head_ = (head_ - 1 + capacity_) % capacity_;
        buffer_[head_] = item;
        size_++;
    } else {
        head_ = (head_ - 1 + capacity_) % capacity_;
        buffer_[head_] = item;
        tail_ = (tail_ - 1 + capacity_) % capacity_;
    }
}

template <class T>
void CircularBuffer<T>::pop_back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    tail_ = (tail_ + capacity_ - 1) % capacity_;
    size_--;
}

template <class T>
void CircularBuffer<T>::pop_front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    head_ = (head_ + 1) % capacity_;
    size_--;
}

template <class T>
void CircularBuffer<T>::insert(int pos, const T& item) {
    if (this->full()) {
        throw CircularBufferError("Buffer is full");
    }
    if (pos < 0 || pos > size_) {
        throw CircularBufferError("Index out of range");
    }
    int index = (head_ + pos) % capacity_;
    for (int i = size_; i > pos; --i) {
        buffer_[(index + i) % capacity_] = buffer_[(index + i - 1) % capacity_];
    }
    buffer_[index] = item;
    tail_ = (tail_ + 1) % capacity_;
    size_++;
}

template <class T>
void CircularBuffer<T>::erase(int first, int last) {
    if (first < 0 || first >= size_ || last < first || last >= size_) {
        throw CircularBufferError("Invalid range");
    }
    int num_elements = last - first + 1;
    int index = (head_ + first) % capacity_;
    for (int i = 0; i < size_ - last - 1; ++i) {
        buffer_[(index + i) % capacity_] = buffer_[(index + i + num_elements) % capacity_];
    }
    tail_ = (tail_ - num_elements + capacity_) % capacity_;
    size_ -= num_elements;
}

template <class T>
void CircularBuffer<T>::clear() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}
