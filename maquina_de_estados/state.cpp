//contexto
class TerminalMachine{
    public:
        TerminalMachine();
        ~TerminalMachine();
        void listen();
        void speak();
        void sleep();
        TerminalState changeState(bool nextState);
};

//interface
class TerminalState: TerminalMachine{};
    public:
        void listen();
        void speak();
        void sleep();

//Concrete states

class SleepState: State{
    public:
        void listen();
        void speak();
        void sleep();

};

int main(){
    tm = TerminalMachine();
}