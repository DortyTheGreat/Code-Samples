class Prerunner
{
public:
    template<typename T, typename... Args>
    Prerunner(T (*func)(Args... args),Args... args ){
        func(args...);
    }

    template<typename T>
    Prerunner(T (*func)()){
        func();
    }
};

