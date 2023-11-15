#include <iostream>
#include <memory>
#include <utility>
#include "spdlog/spdlog.h"

/**
 * The Command interface declares a method for executing a command.
 */
class Command {
public:
    Command() = default;

    Command(const Command &other) = default;

    Command(Command &&other) = default;

    Command &operator=(const Command &other) = default;

    Command &operator=(Command &&other) = default;

    virtual ~Command() = default;

    virtual void execute() const = 0;
};

/**
 * Some commands can implement simple operations on their own.
 */
class SimpleCommand : public Command {
private:
    std::string_view cmd_;

public:
    explicit SimpleCommand(std::string_view cmd) : cmd_(cmd) {
    }

    void execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->cmd_ << ")\n";
    }
};

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may serve as a Receiver.
 */
class Receiver {
private:
    std::string_view receiver_name_;

public:
    explicit Receiver(std::string_view receiver_name) : receiver_name_(receiver_name) {
    }

    void ExecuteCmd1(std::string_view a) {
        std::cout << receiver_name_ << ": Working on (" << a << ".)\n";
    }

    void ExecuteCmd2(std::string_view b) {
        std::cout << receiver_name_ << ": Also working on (" << b << ".)\n";
    }
};


/**
 * However, some commands can delegate more complex operations to other objects,
 * called "receivers."
 */
class ComplexCommand : public Command {
    using ReceiverPtr = std::shared_ptr<Receiver>;

private:
    /**
     * Receiver to delegate your operations.
     */
    ReceiverPtr receiver_;
    /**
     * Context data, required for launching the receiver's methods.
     */
    std::string_view cmd1_;
    std::string_view cmd2_;
    /**
     * Complex commands can accept one or several receiver objects along with any
     * context data via the constructor.
     */
public:
    ComplexCommand(ReceiverPtr receiver, std::string_view cmd1, std::string_view cmd2) : receiver_(std::move(receiver)),
                                                                                           cmd1_(cmd1), cmd2_(cmd2) {
    }

    ComplexCommand() = default;

    ComplexCommand(const ComplexCommand &other) = default;

    ComplexCommand(ComplexCommand &&other) = default;

    ComplexCommand &operator=(const ComplexCommand &other) = default;

    ComplexCommand &operator=(ComplexCommand &&other) = default;

    ~ComplexCommand() override = default;

    /**
     * Commands can delegate to any methods of a receiver.
     */
    void execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->ExecuteCmd1(this->cmd1_);
        this->receiver_->ExecuteCmd2(this->cmd2_);
    }
};

/**
 * The Invoker is associated with one or several commands. It sends a request to
 * the command.
 */
class Invoker {
    using CommandPtr = std::shared_ptr<Command>;
private:
    CommandPtr on_start_;
    CommandPtr on_finish_;

    std::string_view invoker_name_;
public:
    explicit Invoker(std::string_view invoker_name) : invoker_name_(invoker_name) {
    }

    void SetOnStart(CommandPtr command) {
        this->on_start_ = std::move(command);
    }

    void SetOnFinish(CommandPtr command) {
        this->on_finish_ = std::move(command);
    }

    /**
     * The Invoker does not depend on concrete command or receiver classes. The
     * Invoker passes a request to a receiver indirectly, by executing a command.
     */
    void DoSomethingImportant() {
        if (this->on_start_ != nullptr) {
            std::cout << invoker_name_ << ": on start: execute: enter\n";
            this->on_start_->execute();
            std::cout << invoker_name_ << ": on start: execute: done\n";
        }
        if (this->on_finish_ != nullptr) {
            std::cout << invoker_name_ << ": on finish: execute: enter\n";
            this->on_finish_->execute();
            std::cout << invoker_name_ << ": on finish: execute: done\n";
        }
    }
};

/**
 * The client code can parameterize an invoker with any commands.
 */
int main() {
    spdlog::info("Welcome to spdlog!");

    auto invoker = std::make_shared<Invoker>("MyInvoker");
    invoker->SetOnStart(std::make_shared<SimpleCommand>("Say Hi!"));

    auto receiver = std::make_shared<Receiver>("MyFinishReceiver");
    invoker->SetOnFinish(std::make_shared<ComplexCommand>(receiver, "Send email", "Save report"));

    invoker->DoSomethingImportant();

    return 0;
}