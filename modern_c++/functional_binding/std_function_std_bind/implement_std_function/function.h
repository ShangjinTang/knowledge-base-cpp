#pragma once
#include <functional>
#include <memory>

template <typename T>
class Function;

template <typename TReturn, typename... TParam>
class Function<TReturn(TParam...)> {
    using FunctionPtr = TReturn (*)(TParam...);

public:
    explicit Function(FunctionPtr function_ptr)
            : callable_ptr_{std::make_unique<CallableImpl<FunctionPtr>>(function_ptr)} {};

    TReturn operator()(TParam... param) const {
        return callable_ptr_->invoke(param...);
    }

    class CallableInterface {
    public:
        [[nodiscard]] virtual TReturn invoke(TParam... param) const = 0;
        virtual ~CallableInterface() = default;
        CallableInterface() = default;
        CallableInterface(const CallableInterface& other) = default;
        CallableInterface(CallableInterface&& other) noexcept = default;
        CallableInterface& operator=(const CallableInterface& other) = default;
        CallableInterface& operator=(CallableInterface&& other) noexcept = default;
    };

    template <typename Callable>
    class CallableImpl final : public CallableInterface {
    public:
        explicit CallableImpl(Callable callable) : callable_{callable} {};
        [[nodiscard]] TReturn invoke(TParam... param) const override {
            return std::invoke(callable_, param...);
        };

    private:
        Callable callable_;
    };

private:
    std::unique_ptr<CallableInterface> callable_ptr_;
};
