#include <gtest/gtest.h>
#include "circularbuffer.h"

using namespace CircularBufferSpace;

TEST(CircularBufferTest, Constructor) {
    CircularBuffer cb;
    EXPECT_EQ(0, cb.size());
    EXPECT_EQ(0, cb.capacity());
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, CapacityConstructor) {
    CircularBuffer cb(5);
    EXPECT_EQ(0, cb.size());
    EXPECT_EQ(5, cb.capacity());
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, ConstructorWithCapacityAndElement) {
    CircularBuffer cb(5, 'A');
    EXPECT_EQ(cb.size(), 5);
    for (int i = 0; i < cb.size(); ++i) {
        EXPECT_EQ(cb[i], 'A');
    }
}

TEST(CircularBufferTest, PushBackAndPopBack) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_EQ(3, cb.size());
    EXPECT_FALSE(cb.empty());

    cb.pop_back();
    EXPECT_EQ(2, cb.size());
    cb.pop_back();
    cb.pop_back();
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, AccessOperator) {
    CircularBuffer cb(3);
    cb.push_back('a');
    cb.push_back('b');
    cb.push_back('c');
    EXPECT_EQ('a', cb[0]);
    EXPECT_EQ('b', cb[1]);
    EXPECT_EQ('c', cb[2]);
}

TEST(CircularBufferTest, PushBack) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    EXPECT_EQ(3, cb.size());
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
}

TEST(CircularBufferTest, PopBack) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.pop_back();
    EXPECT_EQ(2, cb.size());
    EXPECT_FALSE(cb.full());
    EXPECT_FALSE(cb.empty());
}

TEST(CircularBufferTest, PushFront) {
    CircularBuffer cb(3);
    cb.push_front('C');
    cb.push_front('B');
    cb.push_front('A');
    EXPECT_EQ(3, cb.size());
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
}

TEST(CircularBufferTest, PopFront) {
    CircularBuffer cb(3);
    cb.push_front('C');
    cb.push_front('B');
    cb.push_front('A');
    cb.pop_front();
    EXPECT_EQ(2, cb.size());
    EXPECT_FALSE(cb.full());
    EXPECT_FALSE(cb.empty());
}

TEST(CircularBufferTest, CopyConstructor) {
    CircularBuffer cb1(3);
    cb1.push_back('A');
    cb1.push_back('B');
    cb1.push_back('C');

    CircularBuffer cb2(cb1);

    EXPECT_EQ(cb1.size(), cb2.size());
    for (int i = 0; i < cb1.size(); ++i) {
        EXPECT_EQ(cb1[i], cb2[i]);
    }
}

TEST(CircularBufferTest, AssignmentOperator) {
    CircularBuffer cb1(3);
    cb1.push_back('A');
    cb1.push_back('B');
    cb1.push_back('C');

    CircularBuffer cb2;
    cb2 = cb1;

    EXPECT_EQ(cb1.size(), cb2.size());
    for (int i = 0; i < cb1.size(); ++i) {
        EXPECT_EQ(cb1[i], cb2[i]);
    }
}

TEST(CircularBufferTest, Swap) {
    CircularBuffer cb1(3);
    cb1.push_back('A');
    cb1.push_back('B');
    cb1.push_back('C');

    CircularBuffer cb2(2);
    cb2.push_back('D');
    cb2.push_back('E');

    cb1.swap(cb2);

    EXPECT_EQ(2, cb1.size());
    EXPECT_EQ(3, cb2.size());
    EXPECT_EQ('D', cb1[0]);
    EXPECT_EQ('E', cb1[1]);
    EXPECT_EQ('A', cb2[0]);
    EXPECT_EQ('B', cb2[1]);
    EXPECT_EQ('C', cb2[2]);
}

TEST(CircularBufferTest, IsLinearized) {
    CircularBuffer cb(3, 'A');
    EXPECT_TRUE(cb.is_linearized());
}

TEST(CircularBufferTest, RotateTest1) {
    CircularBuffer cb(5);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.push_back('D');
    cb.push_back('E');
    cb.rotate(2);

    EXPECT_EQ(cb[0], 'C');
    EXPECT_EQ(cb[1], 'D');
    EXPECT_EQ(cb[2], 'E');
    EXPECT_EQ(cb[3], 'A');
    EXPECT_EQ(cb[4], 'B');
}

TEST(CircularBufferTest, SetCapacity) {
    CircularBuffer cb(3, 'A');
    cb.set_capacity(5);
    EXPECT_EQ(cb.capacity(), 5);
}

TEST(CircularBufferTest, Erase) {
    CircularBuffer cb(5);
    cb.push_back('A');
    cb.push_back('A');
    cb.push_back('A');
    cb.push_back('A');
    cb.push_back('D');
    cb.erase(1, 3);
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 'A');
    EXPECT_EQ(cb[1], 'D');
}

TEST(CircularBufferTest, Clear) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    cb.clear();
    EXPECT_EQ(0, cb.size());
    EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, OperatorIndex) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    EXPECT_EQ('B', cb[1]);
}

TEST(CircularBufferTest, At) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    EXPECT_EQ('A', cb.at(0));
    EXPECT_EQ('B', cb.at(1));
    EXPECT_EQ('C', cb.at(2));
}

TEST(CircularBufferTest, Front) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    EXPECT_EQ('A', cb.front());
}

TEST(CircularBufferTest, Back) {
    CircularBuffer cb(3);
    cb.push_back('A');
    cb.push_back('B');
    cb.push_back('C');
    EXPECT_EQ('C', cb.back());
}

TEST(CircularBufferTest, EraseValidRange) {
    CircularBuffer buffer(5);
    buffer.insert(0,'A');
    buffer.insert(1,'B');
    buffer.insert(2,'C');
    buffer.insert(3,'D');
    buffer.insert(4,'E');

    buffer.erase(1, 3);

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer.at(0), 'A');
    EXPECT_EQ(buffer.at(1), 'E');
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}