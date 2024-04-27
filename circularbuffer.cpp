#include <cstring>
#include "circularbuffer.h"

CircularBufferSpace::CircularBuffer::~CircularBuffer() {
    this->clear();
}

CircularBufferSpace::CircularBuffer::CircularBuffer(const CircularBuffer& cb) : head_(cb.head_), tail_(cb.tail_), capacity_(cb.capacity_), size_(cb.size_) {
    buffer_ = new value_type[cb.capacity_];
    copy_buffer(cb);
}

CircularBufferSpace::CircularBuffer::CircularBuffer(int capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
    buffer_ = new value_type[capacity_];
}

CircularBufferSpace::CircularBuffer::CircularBuffer(int capacity, const value_type& elem) : capacity_(capacity), size_(capacity), head_(0), tail_(capacity - 1) {
    buffer_ = new value_type[capacity_];
    for (int i = 0; i < capacity_; i++) {
        buffer_[i] = elem;
    }
}

CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::operator[](int i) {
    return buffer_[(head_ + i) % capacity_];
}

const CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::operator[](int i) const {
    return buffer_[(head_ + i) % capacity_];
}

CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::at(int i) {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[head_ + i];
}

const CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::at(int i) const {
    if (i < 0 || i >= size_) {
        throw CircularBufferError("Index out of range");
    }
    return buffer_[head_ + i];
}

CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_ - 1];
}

const CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::front() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[head_];
}

const CircularBufferSpace::value_type& CircularBufferSpace::CircularBuffer::back() const {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    return buffer_[tail_ - 1];
}

CircularBufferSpace::value_type* CircularBufferSpace::CircularBuffer::linearize() {
    this->rotate(0);
    return buffer_;
}

bool CircularBufferSpace::CircularBuffer::is_linearized() const {
    return head_ == 0 && tail_ == size_ - 1;
}

void CircularBufferSpace::CircularBuffer::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= size_) {
        throw CircularBufferError("Invalid new_begin value");
    }
    for(int i = size_ - 1; i >= size_ - new_begin - 1; i--){
        char tmp = buffer_[size_ - 1];
        for (int j = size_ - 1; j > 0; j--){
            buffer_[j] = buffer_[j-1];
        }
        buffer_[0] = tmp;
    }
}

int CircularBufferSpace::CircularBuffer::size() const {
    return size_;
}

bool CircularBufferSpace::CircularBuffer::empty() const {
    return !size_;
}

bool CircularBufferSpace::CircularBuffer::full() const {
    return size_ == capacity_;
}

int CircularBufferSpace::CircularBuffer::reserve() const {
    return capacity_ - size_;
}

int CircularBufferSpace::CircularBuffer::capacity() const {
    return capacity_;
}

void CircularBufferSpace::CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity < capacity_) {
        this->clear();
        buffer_ = new value_type[new_capacity];
        capacity_ = new_capacity;
    }
    else {
        auto* new_buffer = new value_type[new_capacity];
        for (int i = 0; i < size_; i++) {
            new_buffer[i] = buffer_[(head_ + i) % capacity_];
        }
        delete[] buffer_;
        buffer_ = new_buffer;
        head_ = 0;
        tail_ = size_ - 1;
        capacity_ = new_capacity;
    }
}

void CircularBufferSpace::CircularBuffer::resize(int new_size, const value_type& item) {
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

CircularBufferSpace::CircularBuffer& CircularBufferSpace::CircularBuffer::operator=(const CircularBuffer& cb) {
    if (this != &cb) {
        head_ = cb.head_;
        tail_ = cb.tail_;
        capacity_ = cb.capacity_;
        size_ = cb.size_;
        delete[] buffer_;
        buffer_ = new value_type[capacity_];
        copy_buffer(cb);
    }
    return *this;
}

void CircularBufferSpace::CircularBuffer::swap(CircularBuffer& cb) {
    std::swap(buffer_, cb.buffer_);
    std::swap(capacity_, cb.capacity_);
    std::swap(size_, cb.size_);
    std::swap(head_, cb.head_);
    std::swap(tail_, cb.tail_);
}

void CircularBufferSpace::CircularBuffer::push_back(const value_type& item) {
    if(capacity_ == 0){
        throw CircularBufferError("Buffer hasn't capacity");
    }
    if (size_ < capacity_) {
        buffer_[tail_++] = item;
        size_++;
    } else {
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        tail_ = (tail_ + 1) % capacity_;
    }
}

void CircularBufferSpace::CircularBuffer::push_front(const value_type& item) {
    if(capacity_ == 0){
        throw CircularBufferError("Buffer hasn't capacity");
    }
    if (size_ < capacity_) {
        head_--;
        buffer_[head_] = item;
        size_++;
    } else {
        head_ = (head_ - 1 + capacity_) % capacity_;
        buffer_[head_] = item;
        tail_ = (tail_ - 1 + capacity_) % capacity_;
    }
}

void CircularBufferSpace::CircularBuffer::pop_back() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    tail_ = (tail_ - 1) % capacity_;
    size_--;
}

void CircularBufferSpace::CircularBuffer::pop_front() {
    if (this->empty()) {
        throw CircularBufferError("Buffer is empty");
    }
    head_ = (head_ + 1) % capacity_;
    size_--;
}

void CircularBufferSpace::CircularBuffer::insert(int pos, const value_type& item) {
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

void CircularBufferSpace::CircularBuffer::erase(int first, int last) {
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

void CircularBufferSpace::CircularBuffer::clear() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

bool CircularBufferSpace::operator==(const CircularBufferSpace::CircularBuffer& a, const CircularBufferSpace::CircularBuffer& b) {
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

bool CircularBufferSpace::operator!=(const CircularBufferSpace::CircularBuffer& a, const CircularBufferSpace::CircularBuffer& b) {
    return !(a == b);
}