#include "circularbuffer.h"

CircularBuffer::~CircularBuffer() {
    this->clear();
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb) {
    head_ = cb.head_;
    tail_ = cb.tail_;
    capacity_ = cb.capacity_;
    size_ = cb.size_;
    buffer_ = new value_type[cb.capacity_];
    for(int i = 0; i < cb.size_; i++) {
        buffer_[i] = cb.buffer_[i];
    }
}

CircularBuffer::CircularBuffer(int capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
    buffer_ = new value_type[capacity_];
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem) : capacity_(capacity), size_(capacity), head_(0), tail_(capacity - 1) {
    buffer_ = new value_type[capacity_];
    for (int i = 0; i < capacity_; i++) {
        buffer_[i] = elem;
    }
}

value_type& CircularBuffer::operator[](int i) {
    return buffer_[(head_ + i) % capacity_];
}

const value_type& CircularBuffer::operator[](int i) const {
    return buffer_[(head_ + i) % capacity_];
}

value_type& CircularBuffer::at(int i) {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[(head_ + i) % capacity_];
}

const value_type& CircularBuffer::at(int i) const {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[(head_ + i) % capacity_];
}

value_type& CircularBuffer::front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

value_type& CircularBuffer::back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_ - 1];
}

const value_type& CircularBuffer::front() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

const value_type& CircularBuffer::back() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_ - 1];
}

value_type* CircularBuffer::linearize() {
    if (head_ == 0 && tail_ == size_ - 1) {
        return buffer_;
    }
    if (this->empty()) {
        return nullptr;
    }
    auto* linearized_buffer = new value_type[capacity_];
    int index = head_;
    for (int i = 0; i < size_; ++i) {
        linearized_buffer[i] = buffer_[index];
        index = (index + 1) % capacity_;
    }
    return linearized_buffer;
}

bool CircularBuffer::is_linearized() const {
    return head_ == 0 && tail_ == size_ - 1;
}

void CircularBuffer::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= size_) {
        throw CircularBufferError("Invalid new_begin value");
    }
    head_ = (head_ + new_begin) % capacity_;
    tail_ = (tail_ + new_begin) % capacity_;
}

int CircularBuffer::size() const {
    return size_;
}

bool CircularBuffer::empty() const {
    return size_ == 0;
}

bool CircularBuffer::full() const {
    return size_ == capacity_;
}

int CircularBuffer::reserve() const {
    return capacity_ - size_;
}

int CircularBuffer::capacity() const {
    return capacity_;
}

void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity < size_) {
        throw CircularBufferError("New capacity is smaller than current size");
    }
    auto* new_buffer = new value_type[new_capacity];
    for (int i = 0; i < size_; i++) {
        new_buffer[i] = buffer_[(head_ + i) % capacity_];
    }
    this->clear();
    buffer_ = new_buffer;
    capacity_ = new_capacity;
    head_ = 0;
    tail_ = size_ - 1;
}

void CircularBuffer::resize(int new_size, const value_type& item) {
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

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
    if (this != &cb) {
        head_ = cb.head_;
        tail_ = cb.tail_;
        capacity_ = cb.capacity_;
        size_ = cb.size_;
        delete[] buffer_;
        buffer_ = new value_type[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            buffer_[i] = cb.buffer_[i];
        }
    }
    return *this;
}

void CircularBuffer::swap(CircularBuffer& cb) {
    std::swap(buffer_, cb.buffer_);
    std::swap(capacity_, cb.capacity_);
    std::swap(size_, cb.size_);
    std::swap(head_, cb.head_);
    std::swap(tail_, cb.tail_);
}

void CircularBuffer::push_back(const value_type& item) {
    if (size_ < capacity_) {
        buffer_[(tail_++) % capacity_] = item;
        size_++;
    } else {
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        tail_ = (tail_ + 1) % capacity_;
    }
}

void CircularBuffer::push_front(const value_type& item) {
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

void CircularBuffer::pop_back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    tail_ = (tail_ + capacity_ - 1) % capacity_;
    size_--;
}

void CircularBuffer::pop_front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    head_ = (head_ + 1) % capacity_;
    size_--;
}

void CircularBuffer::insert(int pos, const value_type& item) {
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

void CircularBuffer::erase(int first, int last) {
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

void CircularBuffer::clear() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
    return !(a == b);
}