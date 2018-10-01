//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


/// First experiments for ffwd scheduler -> TODO: implement scheduler_base

#include "scheduler_base.hpp"

namespace hpx { namespace threads { namespace policies
{

    class HPX_EXPORT ffwd_scheduler : public scheduler_base {


        ffwd_scheduler() {
            std::cout << "constructor" << std::endl;
        }
        ~ffwd_scheduler() {
            std::cout << "destructor" << std::endl;
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
            std::cout << "cleanup_terminated not implemented yet" << std::endl;
            return true;
        }

        bool cleanup_terminated(std::size_t num_thread, bool delete_all) {
            std::cout << "cleanup_terminated not implemented yet" << std::endl;
            return true;
        }

        void create_thread(thread_init_data& data, thread_id_type* id,
                                   thread_state_enum initial_state, bool run_now, error_code& ec) {
            std::cout << "create_thread not implemented yet" << std::endl;
        }

        bool get_next_thread(std::size_t num_thread, bool running,
            std::int64_t& idle_loop_count, threads::thread_data*& thrd){
            std::cout << "get_next_thread not implemented yet" << std::endl;
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
            std::cout << "schedule_thread_last not implemented yet" << std::endl;
        }

        void destroy_thread(threads::thread_data* thrd,
                            std::int64_t& busy_count) {
            std::cout << "destroy_thread not implemented yet" << std::endl;
        }

        bool wait_or_add_new(std::size_t num_thread, bool running,
                             std::int64_t& idle_loop_count) {
            std::cout << "wait_or_add_new not implemented yet" << std::endl;
            return false;
        }

        void on_start_thread(std::size_t num_thread) {
            std::cout << "wait_or_add_new not implemented yet" << std::endl;
        }
        void on_stop_thread(std::size_t num_thread) {
            std::cout << "on_stop_thread not implemented yet" << std::endl;
        }
        void on_error(std::size_t num_thread,
            std::exception_ptr const& e) {
            std::cout << "on_error not implemented yet" << std::endl;
        }

#ifdef HPX_HAVE_THREAD_QUEUE_WAITTIME
        virtual std::int64_t get_average_thread_wait_time(
            std::size_t num_thread = std::size_t(-1)) const = 0;
        virtual std::int64_t get_average_task_wait_time(
            std::size_t num_thread = std::size_t(-1)) const = 0;
#endif

        void start_periodic_maintenance(
            std::atomic<hpx::state>& /*global_state*/)
        {
            std::cout << "start_periodic_maintenance not implemented yet" << std::endl;
        }

        void reset_thread_distribution() {
            std::cout << "reset_thread_distribution not implemented yet" << std::endl;
        }

    }

}
