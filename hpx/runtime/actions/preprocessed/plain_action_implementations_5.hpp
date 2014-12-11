// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace actions
{
    
    
    template <
        typename R, typename T0,
        R (*F)(T0), typename Derived>
    class plain_base_action<R (*)(T0), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            R,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef R result_type;
        typedef typename detail::remote_action_result<R>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type> arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static R
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            return F(util::get< 0>(std::forward<Arguments>( args)));
        }
    };
    
    
    template <typename R, typename T0,
        R (*F)(T0), typename Derived>
    struct make_action<R (*)(T0), F, Derived, boost::mpl::false_>
      : plain_action<R (*)(T0), F, Derived>
    {
        typedef plain_action<
            R (*)(T0), F, Derived
        > type;
    };
    
    
    template <typename Result, typename T0,
        Result (*F)(T0), typename Derived>
    struct make_action<Result (*)(T0), F, Derived, boost::mpl::true_>
      : plain_direct_action<Result (*)(T0), F, Derived>
    {
        typedef plain_direct_action<
            Result (*)(T0), F, Derived
        > type;
    };
    
    
    template <
        typename T0,
        void (*F)(T0), typename Derived>
    class plain_base_action<void (*)(T0), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef void result_type;
        typedef util::unused_type remote_result_type;
        typedef
            hpx::util::tuple<typename util::decay<T0>::type>
        arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function_void(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            F(util::get< 0>(std::forward<Arguments>( args)));
            return util::unused;
        }
    };
}}
namespace hpx { namespace traits
{
    template <typename R, typename Arg0,
        R (*F)(Arg0), typename Derived,
        typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_action<
                    R (*)(Arg0), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
    template <typename R, typename Arg0,
        R (*F)(Arg0), typename Derived, typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_direct_action<
                    R (*)(Arg0), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename R, typename T0 , typename T1,
        R (*F)(T0 , T1), typename Derived>
    class plain_base_action<R (*)(T0 , T1), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            R,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef R result_type;
        typedef typename detail::remote_action_result<R>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type> arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static R
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            return F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)));
        }
    };
    
    
    template <typename R, typename T0 , typename T1,
        R (*F)(T0 , T1), typename Derived>
    struct make_action<R (*)(T0 , T1), F, Derived, boost::mpl::false_>
      : plain_action<R (*)(T0 , T1), F, Derived>
    {
        typedef plain_action<
            R (*)(T0 , T1), F, Derived
        > type;
    };
    
    
    template <typename Result, typename T0 , typename T1,
        Result (*F)(T0 , T1), typename Derived>
    struct make_action<Result (*)(T0 , T1), F, Derived, boost::mpl::true_>
      : plain_direct_action<Result (*)(T0 , T1), F, Derived>
    {
        typedef plain_direct_action<
            Result (*)(T0 , T1), F, Derived
        > type;
    };
    
    
    template <
        typename T0 , typename T1,
        void (*F)(T0 , T1), typename Derived>
    class plain_base_action<void (*)(T0 , T1), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef void result_type;
        typedef util::unused_type remote_result_type;
        typedef
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>
        arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function_void(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)));
            return util::unused;
        }
    };
}}
namespace hpx { namespace traits
{
    template <typename R, typename Arg0 , typename Arg1,
        R (*F)(Arg0 , Arg1), typename Derived,
        typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_action<
                    R (*)(Arg0 , Arg1), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
    template <typename R, typename Arg0 , typename Arg1,
        R (*F)(Arg0 , Arg1), typename Derived, typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_direct_action<
                    R (*)(Arg0 , Arg1), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename R, typename T0 , typename T1 , typename T2,
        R (*F)(T0 , T1 , T2), typename Derived>
    class plain_base_action<R (*)(T0 , T1 , T2), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            R,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef R result_type;
        typedef typename detail::remote_action_result<R>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static R
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            return F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)));
        }
    };
    
    
    template <typename R, typename T0 , typename T1 , typename T2,
        R (*F)(T0 , T1 , T2), typename Derived>
    struct make_action<R (*)(T0 , T1 , T2), F, Derived, boost::mpl::false_>
      : plain_action<R (*)(T0 , T1 , T2), F, Derived>
    {
        typedef plain_action<
            R (*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    
    template <typename Result, typename T0 , typename T1 , typename T2,
        Result (*F)(T0 , T1 , T2), typename Derived>
    struct make_action<Result (*)(T0 , T1 , T2), F, Derived, boost::mpl::true_>
      : plain_direct_action<Result (*)(T0 , T1 , T2), F, Derived>
    {
        typedef plain_direct_action<
            Result (*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    
    template <
        typename T0 , typename T1 , typename T2,
        void (*F)(T0 , T1 , T2), typename Derived>
    class plain_base_action<void (*)(T0 , T1 , T2), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef void result_type;
        typedef util::unused_type remote_result_type;
        typedef
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>
        arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function_void(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)));
            return util::unused;
        }
    };
}}
namespace hpx { namespace traits
{
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2,
        R (*F)(Arg0 , Arg1 , Arg2), typename Derived,
        typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_action<
                    R (*)(Arg0 , Arg1 , Arg2), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2,
        R (*F)(Arg0 , Arg1 , Arg2), typename Derived, typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_direct_action<
                    R (*)(Arg0 , Arg1 , Arg2), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename R, typename T0 , typename T1 , typename T2 , typename T3,
        R (*F)(T0 , T1 , T2 , T3), typename Derived>
    class plain_base_action<R (*)(T0 , T1 , T2 , T3), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            R,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef R result_type;
        typedef typename detail::remote_action_result<R>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static R
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            return F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)));
        }
    };
    
    
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3,
        R (*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<R (*)(T0 , T1 , T2 , T3), F, Derived, boost::mpl::false_>
      : plain_action<R (*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef plain_action<
            R (*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    
    template <typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<Result (*)(T0 , T1 , T2 , T3), F, Derived, boost::mpl::true_>
      : plain_direct_action<Result (*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef plain_direct_action<
            Result (*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    
    template <
        typename T0 , typename T1 , typename T2 , typename T3,
        void (*F)(T0 , T1 , T2 , T3), typename Derived>
    class plain_base_action<void (*)(T0 , T1 , T2 , T3), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef void result_type;
        typedef util::unused_type remote_result_type;
        typedef
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>
        arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function_void(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)));
            return util::unused;
        }
    };
}}
namespace hpx { namespace traits
{
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3,
        R (*F)(Arg0 , Arg1 , Arg2 , Arg3), typename Derived,
        typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_action<
                    R (*)(Arg0 , Arg1 , Arg2 , Arg3), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3,
        R (*F)(Arg0 , Arg1 , Arg2 , Arg3), typename Derived, typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_direct_action<
                    R (*)(Arg0 , Arg1 , Arg2 , Arg3), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        R (*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    class plain_base_action<R (*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            R,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef R result_type;
        typedef typename detail::remote_action_result<R>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static R
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            return F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)));
        }
    };
    
    
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        R (*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<R (*)(T0 , T1 , T2 , T3 , T4), F, Derived, boost::mpl::false_>
      : plain_action<R (*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef plain_action<
            R (*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    
    template <typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<Result (*)(T0 , T1 , T2 , T3 , T4), F, Derived, boost::mpl::true_>
      : plain_direct_action<Result (*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef plain_direct_action<
            Result (*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    
    template <
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    class plain_base_action<void (*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : public action<
            components::server::plain_function<Derived>,
            util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef void result_type;
        typedef util::unused_type remote_result_type;
        typedef
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>
        arguments_type;
        typedef action<
            components::server::plain_function<Derived>, result_type,
            arguments_type, Derived> base_type;
        
        static bool is_target_valid(naming::id_type const& id)
        {
            return naming::is_locality(id);
        }
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4) const
            {
                try {
                    LTM_(debug) << "Executing plain action("
                                << detail::get_action_name<Derived>()
                                << ").";
                    
                    F(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>()
                        << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing plain action("
                        << detail::get_action_name<Derived>() << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(naming::address::address_type lva,
            Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                util::bind(util::one_shot(typename Derived::thread_function()),
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args))));
        }
        
        
        
        
        template <typename Arguments>
        static threads::thread_function_type
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, Arguments && args)
        {
            return traits::action_decorate_function<Derived>::call(lva,
                base_type::construct_continuation_thread_function_void(
                    cont, F, std::forward<Arguments>(args)));
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            Arguments && args)
        {
            LTM_(debug)
                << "plain_base_action::execute_function name("
                << detail::get_action_name<Derived>() << ")";
            F(util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)));
            return util::unused;
        }
    };
}}
namespace hpx { namespace traits
{
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4,
        R (*F)(Arg0 , Arg1 , Arg2 , Arg3 , Arg4), typename Derived,
        typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_action<
                    R (*)(Arg0 , Arg1 , Arg2 , Arg3 , Arg4), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
    template <typename R, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4,
        R (*F)(Arg0 , Arg1 , Arg2 , Arg3 , Arg4), typename Derived, typename Enable>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::actions::plain_direct_action<
                    R (*)(Arg0 , Arg1 , Arg2 , Arg3 , Arg4), F, Derived> >, Enable>
      : boost::mpl::false_
    {};
}}
