// Penn Parallel Primitives Library
// Author: Prof. Milo Martin
// University of Pennsylvania
// Spring 2010
// Modified by Graeme Smith and Alysha van Duynhoven
// Fall 2015


#include "ppp.h"
#include "TaskGroup.h"

namespace ppp {

  namespace internal {
    // Task-based scheduling variables
    TaskQueue* g_queues_ptr = NULL;
    atomic<int> g_stop_counter;  
  }

  using namespace internal;

  void TaskGroup::spawn(Task& t) {
    assert(g_queues_ptr != NULL);
    TaskQueue& queue = g_queues_ptr[get_thread_id()];  // ASSIGNMENT: use per-thread task queue with "get_thread_id()"

    m_wait_counter.fetch_and_inc();
    t.setCounter(&m_wait_counter);
    queue.enqueue(&t);
  }
  
  void process_tasks(const atomic<int>* counter)
  {
    TaskQueue& queue = g_queues_ptr[get_thread_id()];  // ASSIGNMENT: use per-thread task queue with "get_thread_id()"

    while (counter->get() != 0) {
      PPP_DEBUG_EXPR(queue.size());
       
      Task* task;

      if (queue.size() > 0) {
        //Dequeue from local queue
        task = queue.dequeue();
      } else {
        // ASSIGNMENT: add task stealing
        int value = rand() % get_thread_count();
        TaskQueue& stolenQueue = g_queues_ptr[value];
        task = stolenQueue.steal();
      }

      if (task != NULL) {
        task->execute(); // overloaded method
        task->post_execute(); // cleanup, method of base class
      }
    }
  }
}

