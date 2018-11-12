//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


/// First experiments for ffwd scheduler -> TODO: implement scheduler_base
#include "scheduler_base.hpp"

#include <hpx/config/warnings_prefix.hpp>
#include <hpx/compat/mutex.hpp>
#include <hpx/runtime/threads/policies/thread_queue.hpp>

#include <vector>

#if !defined(HPX_THREADMANAGER_SCHEDULING_FFWD_SCHEDULER)
#define HPX_THREADMANAGER_SCHEDULING_FFWD_SCHEDULER

namespace hpx { namespace threads { namespace policies
{
    // somehow they used a bunch of typenames that don't make that much sense to me :|
    template <typename Mutex = compat::mutex,
    typename PendingQueuing = lockfree_fifo,
    typename StagedQueuing = lockfree_fifo,
    typename TerminatedQueuing = lockfree_lifo>
    class HPX_EXPORT ffwd_scheduler : public scheduler_base
    {
    protected:
        // The maximum number of active threads this thread manager should
        // create. This number will be a constraint only as long as the work
        // items queue is not empty. Otherwise the number of active threads
        // will be incremented in steps equal to the \a min_add_new_count
        // specified above.
        // FIXME: this is specified both here, and in thread_queue.
        enum { max_thread_count = 1000 };
    public:

        //this is copied
        typedef thread_queue<
            Mutex, PendingQueuing, StagedQueuing, TerminatedQueuing
        > thread_queue_type;

        struct init_parameter
        {
            init_parameter()
              : num_queues_(1),
                num_high_priority_queues_(1),
                max_queue_thread_count_(max_thread_count),
                numa_sensitive_(0),
                description_("ffwd_scheduler")
            {}

            init_parameter(std::size_t num_queues,
                    std::size_t num_high_priority_queues = std::size_t(-1),
                    std::size_t max_queue_thread_count = max_thread_count,
                    std::size_t numa_sensitive = 0,
                    char const* description = "ffwd_scheduler")
              : num_queues_(num_queues),
                num_high_priority_queues_(
                    num_high_priority_queues == std::size_t(-1) ?
                        num_queues : num_high_priority_queues),
                max_queue_thread_count_(max_queue_thread_count),
                numa_sensitive_(numa_sensitive),
                description_(description)
            {}

            init_parameter(std::size_t num_queues, char const* description)
              : num_queues_(num_queues),
                num_high_priority_queues_(num_queues),
                max_queue_thread_count_(max_thread_count),
                numa_sensitive_(false),
                description_(description)
            {}

            std::size_t num_queues_;
            std::size_t num_high_priority_queues_;
            std::size_t max_queue_thread_count_;
            std::size_t numa_sensitive_;
            char const* description_;
        };
        typedef init_parameter init_parameter_type;

        ///////////////////////////////////////////////////////////////////////
        ffwd_scheduler(init_parameter_type const& init) : scheduler_base(init.num_queues_, init.description_)
        {
//            if (!deferred_initialization)
//            {
#if defined(HPX_MSVC)
#pragma warning(push)
#pragma warning(disable: 4316) // object allocated on the heap may not be aligned 16
#endif
                // for now we only have standard queue
                HPX_ASSERT(init.num_queues_ != 0);
                for (std::size_t i = 0; i < init.num_queues_; ++i) {
                    queues_.push_back(new thread_queue_type(init.max_queue_thread_count_));
                }
#if defined(HPX_MSVC)
#pragma warning(pop)
#endif
//            }
        }

        ~ffwd_scheduler() {
            queues_.clear();
            std::cout << "ffwd_scheduler desctructor" << std::endl;
        }

        /////////////////////////////////////////////////////////////////////

        std::string get_scheduler_name() {
            return "ffwd_scheduler";
        }

        void suspend(std::size_t num_thread)
        {
            std::cout << "suspend called" << std::endl;
            HPX_ASSERT(num_thread < suspend_conds_.size());

            states_[num_thread].store(state_sleeping);
            std::unique_lock<pu_mutex_type> l(suspend_mtxs_[num_thread]);
            suspend_conds_[num_thread].wait(l);

            // Only set running if still in state_sleeping. Can be set with
            // non-blocking/locking functions to stopping or terminating, in
            // which case the state is left untouched.
            hpx::state expected = state_sleeping;
            states_[num_thread].compare_exchange_strong(expected, state_running);

            HPX_ASSERT(expected == state_sleeping ||
                expected == state_stopping || expected == state_terminating);
        }

        void resume(std::size_t num_thread)
        {
            std::cout << "resume called" << std::endl;
            if (num_thread == std::size_t(-1))
            {
                for (compat::condition_variable& c : suspend_conds_)
                {
                    c.notify_one();
                }
            }
            else
            {
                HPX_ASSERT(num_thread < suspend_conds_.size());
                suspend_conds_[num_thread].notify_one();
            }
        }

        ////////////////////////////////////////////////////////////////
        bool numa_sensitive() const { return false; }
        bool has_thread_stealing() const { return false; }


        ///////////////////////////////////////////////////////////////
#ifdef HPX_HAVE_THREAD_CREATION_AND_CLEANUP_RATES
        std::uint64_t get_creation_time(bool reset) {return 0;}
        std::uint64_t get_cleanup_time(bool reset) {return 0;}
#endif

#ifdef HPX_HAVE_THREAD_STEALING_COUNTS
        std::int64_t get_num_pending_misses(std::size_t num_thread,
            bool reset) {return 0;}
        std::int64_t get_num_pending_accesses(std::size_t num_thread,
            bool reset) {return 0;}

        std::int64_t get_num_stolen_from_pending(std::size_t num_thread,
            bool reset) {return 0;}
        std::int64_t get_num_stolen_to_pending(std::size_t num_thread,
            bool reset) {return 0;}
        std::int64_t get_num_stolen_from_staged(std::size_t num_thread,
            bool reset) {return 0;}
        std::int64_t get_num_stolen_to_staged(std::size_t num_thread,
            bool reset) {return 0;}
#endif

        std::int64_t get_queue_length(
            std::size_t num_thread = std::size_t(-1)) const {
            std::cout << "get_queue_length called" << std::endl;
            return 1;
        }

        std::int64_t get_thread_count(
            thread_state_enum state = unknown,
            thread_priority priority = thread_priority_default,
            std::size_t num_thread = std::size_t(-1),
            bool reset = false) const {
            std::cout << "get_thread_count called" << std::endl;
            return 1;
        }

        // Enumerate all matching threads
        bool enumerate_threads(
            util::function_nonser<bool(thread_id_type)> const& f,
                thread_state_enum state = unknown) const {
            std::cout << "enumerate threads not implemented yet" << std::endl;
            return true;
        }

        void abort_all_suspended_threads() {
            std::cout << "abort_all_suspended_threads not implemented yet" << std::endl;
        }

        bool cleanup_terminated(bool delete_all) {
            if(!doneit4) {
                std::cout << "cleanup_terminated not implemented yet" << std::endl;
                doneit4 = true;
            }
            return true;
        }

        bool cleanup_terminated(std::size_t num_thread, bool delete_all) {
            if(!doneit4) {
                std::cout << "cleanup_terminated not implemented yet" << std::endl;
                doneit4 = true;
            }
            return true;
        }

        void create_thread(thread_init_data& data, thread_id_type* id,
                                   thread_state_enum initial_state, bool run_now, error_code& ec)
        {
            std::size_t num_thread =
                data.schedulehint.mode == thread_schedule_hint_mode_thread ?
                data.schedulehint.hint : std::size_t(-1);

            HPX_ASSERT(num_thread < queues_.size());
            queues_[num_thread]->create_thread(data, id, initial_state,
                run_now, ec);
        }

        bool get_next_thread(std::size_t num_thread, bool running,
            std::int64_t& idle_loop_count, threads::thread_data*& thrd){
            if(!doneit3) {
                std::cout << "get_next_thread not implemented yet" << std::endl;
                doneit3 = false;
            }
            return false;
        }

        void schedule_thread(threads::thread_data* thrd,
            threads::thread_schedule_hint schedulehint,
            bool allow_fallback = false,
                             thread_priority priority = thread_priority_normal){
            std::cout << "schedule_thread not implemented yet" << std::endl;
        }

        void schedule_thread_last(threads::thread_data* thrd,
            threads::thread_schedule_hint schedulehint,
            bool allow_fallback = false,
                                  thread_priority priority = thread_priority_normal) {
            if(!doneit) {
                std::cout << "schedule_thread_last not implemented yet" << std::endl;
                doneit = true;
            }
        }

        void destroy_thread(threads::thread_data* thrd,
                            std::int64_t& busy_count) {
            std::cout << "destroy_thread not implemented yet" << std::endl;
        }

        bool wait_or_add_new(std::size_t num_thread, bool running,
                             std::int64_t& idle_loop_count) {
            if(!doneit2) {
                std::cout << "wait_or_add_new not implemented yet" << std::endl;
                doneit2 = true;
            }
            return false;
        }

        void on_start_thread(std::size_t num_thread)
        {
            // on_start_thread: Calls callback and steals work if it can (local)
            if (nullptr == queues_[num_thread])
            {
                queues_[num_thread] =
                    new thread_queue_type(max_queue_thread_count_);
            }
            queues_[num_thread]->on_start_thread(num_thread);

            // TODO add work-stealing here

        }
        void on_stop_thread(std::size_t num_thread) {
            std::cout << "on_stop_thread not implemented yet" << std::endl;
        }

        void on_error(std::size_t num_thread,
            std::exception_ptr const& e)
        {
            std::cout << "on_error not implemented yet" << std::endl;
        }

#ifdef HPX_HAVE_THREAD_QUEUE_WAITTIME
        virtual std::int64_t get_average_thread_wait_time(
            std::size_t num_thread = std::size_t(-1)) const = 0;
        virtual std::int64_t get_average_task_wait_time(
            std::size_t num_thread = std::size_t(-1)) const = 0;
#endif

//        void start_periodic_maintenance(
//            std::atomic<hpx::state>& /*global_state*/)
//        {
//            std::cout << "start_periodic_maintenance not implemented yet" << std::endl;
//        }

        void reset_thread_distribution() {
            std::cout << "reset_thread_distribution not implemented yet" << std::endl;
        }


    protected:
        std::vector<thread_queue_type*> queues_;
        std::size_t max_queue_thread_count_;
        bool doneit = false;
        bool doneit2 = false;
        bool doneit3 = false;
        bool doneit4 = false;
    };

}}}
#endif
