#include <list>
#include <string>
#include <utility>

template <class T>
class CircularBuffer final {
private:
    T* buffer_;
    int head_{};
    int tail_{};
    int capacity_{};
    int size_{};
public:
    CircularBuffer() = default;
    ~CircularBuffer();
    CircularBuffer(const CircularBuffer<T>& cb);

    explicit CircularBuffer(int capacity);
    CircularBuffer(int capacity, const T& elem);

    T& operator[](int i);
    const T& operator[](int i) const;

    T& at(int i);
    const T& at(int i) const;

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;

    T* linearize();
    [[nodiscard]] bool is_linearized() const;
    void rotate(int new_begin);
    [[nodiscard]] int size() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool full() const;
    [[nodiscard]] int reserve() const;
    [[nodiscard]] int capacity() const;

    void set_capacity(int new_capacity);
    void resize(int new_size, const T& item = T());
    CircularBuffer& operator=(const CircularBuffer& cb) ;
    void swap(CircularBuffer& cb);

    void push_back(const T& item = T());
    void push_front(const T& item = T());
    void pop_back();
    void pop_front();

    void insert(int pos, const T & item = T());
    void erase(int first, int last);
    void clear();
};

template <class T>
bool operator==(const CircularBuffer<T>& a, const CircularBuffer<T>& b) {
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

template <class T>
bool operator!=(const CircularBuffer<T>& a, const CircularBuffer<T>& b) {
    return !(a == b);
}


class CircularBufferError: public std::exception {
public:
    explicit CircularBufferError(std::string  message): message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};