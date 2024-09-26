#include "gtest/gtest.h"
#include "queue.h"


class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
    dq = Queue();
  }
  void TearDown() {

  }
 protected:
  Queue dq;
};

TEST_F(QueueTest, QueueConstructorTest) {
  Queue q = Queue(12);

  EXPECT_EQ(q.size(), 0);
  EXPECT_EQ(q.isEmpty(), true);
  EXPECT_EQ(q.isFull(), false);
  EXPECT_EQ(q.getCapacity(), 12);

  q.enqueue(1);

  EXPECT_EQ(sizeof(q), 24);
}

TEST_F(QueueTest, DefaultQueue) {
  EXPECT_EQ(dq.size(), 0);
  EXPECT_EQ(dq.isEmpty(), true);
  EXPECT_EQ(dq.isFull(), false);
  EXPECT_EQ(dq.getCapacity(), 1000);

  dq.enqueue(1);

  EXPECT_EQ(dq.peek(), 1);
  EXPECT_EQ(dq.size(), 1);
  EXPECT_EQ(dq.isEmpty(), false);
  EXPECT_EQ(dq.isFull(), false);
  EXPECT_EQ(dq.getCapacity(), 1000);

  dq.enqueue(2);
  
  EXPECT_EQ(dq.peek(), 1);
  EXPECT_EQ(dq.size(), 2);
  EXPECT_EQ(dq.isEmpty(), false);
  EXPECT_EQ(dq.isFull(), false);
  EXPECT_EQ(dq.getCapacity(), 1000);

  dq.dequeue();

  EXPECT_EQ(dq.peek(), 2);
  EXPECT_EQ(dq.size(), 1);
  EXPECT_EQ(dq.isEmpty(), false);
  EXPECT_EQ(dq.isFull(), false);
  EXPECT_EQ(dq.getCapacity(), 1000);

  dq.clear();

  EXPECT_EQ(dq.size(), 0);
  EXPECT_EQ(dq.isEmpty(), true);
  EXPECT_EQ(dq.isFull(), false);
  EXPECT_EQ(dq.getCapacity(), 1000);
}

TEST_F(QueueTest, QueueAssignmentOperator) {
  Queue q1 = Queue(12);

  q1.enqueue(1);
  q1.enqueue(2);
  q1.enqueue(3);
  
  Queue q2 = Queue(0);
  q2 = q1;

  EXPECT_EQ(q1.indexOf(2), q2.indexOf(2));
  EXPECT_EQ(q1.peek(), q2.peek());
  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.isEmpty(), q2.isEmpty());
  EXPECT_EQ(q1.isFull(), q2.isFull());
  EXPECT_EQ(q1.getCapacity(), q2.getCapacity());
}

TEST_F(QueueTest, Dequeue) {
  Queue q = Queue(12);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  std::string expected_output = "Removing 1\n";

  testing::internal::CaptureStdout();
  q.dequeue();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, expected_output );
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.isEmpty(), false);
  EXPECT_EQ(q.isFull(), false);
  EXPECT_EQ(q.getCapacity(), 12);
  EXPECT_EQ(q.peek(), 2);
}

TEST_F(QueueTest, QueueCopyConstructor) {
  Queue q1(3);

  q1.enqueue(1); 
  q1.enqueue(2);
  q1.enqueue(3);

  Queue q2 = q1;

  EXPECT_EQ(q1.indexOf(0), q2.indexOf(0));
  EXPECT_EQ(0, q2.indexOf(1));
  EXPECT_EQ(q2.indexOf(4), -1);
  EXPECT_EQ(q1.peek(), q2.peek());
  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q2.size(), q2.size());
  EXPECT_EQ(q1.isEmpty(), q2.isEmpty());
  EXPECT_EQ(q1.isFull(), q2.isFull());
  EXPECT_EQ(q1.getCapacity(), q2.getCapacity());
}

TEST_F(QueueTest, IndexOf) {
  Queue q = Queue(12);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(3);
  
  EXPECT_EQ(q.indexOf(1), 0);
  EXPECT_EQ(q.indexOf(2), 1);
  EXPECT_EQ(q.indexOf(3), 2);

  q.dequeue();

  EXPECT_EQ(q.indexOf(2), 0);
  EXPECT_EQ(q.indexOf(3), 1);

  q.dequeue();

  EXPECT_EQ(q.peek(), 3);
  EXPECT_EQ(q.indexOf(3), 0);
  EXPECT_EQ(q.indexOf(4), -1);
  EXPECT_EQ(q.size(), 2);
}

TEST_F(QueueTest, QueueFull) {
  Queue q = Queue(3);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  EXPECT_EQ(q.isFull(), true);
}

TEST_F(QueueTest, QueueEmpty) {
  Queue q = Queue(3);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.dequeue();
  q.dequeue();
  q.dequeue();

  EXPECT_EQ(q.isEmpty(), true);
}

TEST_F(QueueTest, QueueClear) {
  Queue q = Queue(3);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.clear();

  EXPECT_EQ(q.isEmpty(), true);
  EXPECT_EQ(q.getCapacity(), 3);
  EXPECT_EQ(q.size(), 0);
}

TEST_F(QueueTest, PeekQueue) {
  Queue q = Queue(12);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  
  EXPECT_EQ(q.peek(), 1);

  q.dequeue();

  EXPECT_EQ(q.peek(), 2);

  q.dequeue();

  EXPECT_EQ(q.peek(), 3);
  EXPECT_EQ(q.isEmpty(), false);
  EXPECT_EQ(q.getCapacity(), 12);
  EXPECT_EQ(q.size(), 1);
}

TEST_F(QueueTest, BubbleSort) {
  Queue q(4);

  q.enqueue(2147483647);
  q.enqueue(3); 
  q.enqueue(2);
  q.enqueue(1);
  q.bubbleSort();

  EXPECT_EQ(q.indexOf(1), 0);
  EXPECT_EQ(q.indexOf(2147483647), 3);
  EXPECT_EQ(q.indexOf(5), -1);
  EXPECT_EQ(q.size(), 4);
}

TEST_F(QueueTest, MergeSort) {
  Queue q(2);

  q.enqueue(2);
  q.enqueue(1);
  q.mergeSort();

  EXPECT_EQ(q.indexOf(1), 0);
  EXPECT_EQ(q.indexOf(2), 1);
  EXPECT_EQ(q.size(), 2);
}

TEST_F(QueueTest, QueueOverflow) {
  Queue q = Queue(1);

  q.enqueue(1);
  EXPECT_EXIT(q.enqueue(2), ::testing::ExitedWithCode(1), "");
}

TEST_F(QueueTest, PointerCopy) {
  Queue *q1 = new Queue(3);

  q1->enqueue(1);
  q1->enqueue(2);
  Queue *q2 = q1;

  EXPECT_EQ(q1->getCapacity(), q2->getCapacity());
  EXPECT_EQ(q1->size(), q2->size());
  EXPECT_EQ(0, q2->indexOf(1));
  EXPECT_EQ(1, q2->indexOf(2));
  EXPECT_EQ(-1, q2->indexOf(3));
  EXPECT_EQ(q1->size(), 2);
  EXPECT_EQ(q2->size(), 2);
}