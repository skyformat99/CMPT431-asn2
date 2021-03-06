// Penn Parallel Primitives Library
// Author: Prof. Milo Martin
// University of Pennsylvania
// Spring 2010
// Modified by Graeme Smith and Alysha van Duynhoven
// Fall 2015

#ifndef PPP_REDUCE_H
#define PPP_REDUCE_H

#include "ppp.h"
#include "Task.h"
#include "TaskGroup.h"

/* 
  Implement parallel_reduce() analogously to the above parallel_sort() function. 
  Use it to sum an array of numbers (rather than sort them). 
  Use a large enough dataset and multiple trials so that it runs for at least a few seconds. 
  Perform the same analysis as in Part 4 (and answer the same questions).
*/

namespace ppp {

  namespace internal {
    
      template <typename T>
      class ParallelReduceTask: public ppp::Task {
      public:

        ParallelReduceTask(T* array, int64_t start, int64_t end, int64_t grainsize) { 
	  m_sum = 0;
          m_array = array;
          m_start = start;
          m_end = end;
          m_grainsize = grainsize;
        }

	T getSum() {
		return m_sum;
	} 
        
        void execute() {



          PPP_DEBUG_MSG("Execute: [" + to_string(m_start) + ", " + to_string(m_end) + "]");
          assert(m_start < m_end);

          if (m_end-m_start <= 1) {
            return;
          }
          
          if (m_end-m_start < m_grainsize) {
            PPP_DEBUG_MSG("std::array: [" + to_string(m_start) + ", " + to_string(m_end) + "]");
            PPP_DEBUG_MSG("std::array: [" + to_string(&m_array[m_start]) + ", " + to_string(&m_array[m_end]) + "]");

            // Sequential code
            // T sum;
            // sum = T(0);
            for (int i=m_start; i<m_end; i++) {
              m_sum = m_sum + m_array[i];
            }
            return;
          }

          int64_t pivot = (m_start+m_end)/2;
          assert(pivot < m_end);
          
          ppp::TaskGroup tg;
          ParallelReduceTask t1(m_array, m_start, pivot, m_grainsize);
          ParallelReduceTask t2(m_array, pivot, m_end, m_grainsize);
          tg.spawn(t1);
          tg.spawn(t2);
          tg.wait();

          m_sum = m_sum + t1.m_sum + t2.m_sum;
        }
      private:
        T m_sum;
        T* m_array;
        int64_t m_start;
        int64_t m_end;
        int64_t m_grainsize;
      };
    }


  
  template <typename T>
  extern inline
  T parallel_reduce(T* array, int64_t start, int64_t end, int64_t grainsize=0)
  {
    // ASSIGNMENT: make this parallel via recursive divide and conquer
    if (grainsize == 0) {
      grainsize = (end-start+1) / (get_thread_count()*4);
    }
    PPP_DEBUG_MSG("parallel_reduce grainsize: " + to_string(grainsize));

    internal::ParallelReduceTask<T> t(array, start, end, grainsize);
    t.execute();
    PPP_DEBUG_MSG("parallel_reduce done");

    return t.getSum();
  }
}

#endif
