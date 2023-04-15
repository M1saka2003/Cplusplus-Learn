#include <iostream>
#include <functional>

//���ܻ��ɻ�,Ϊʲôд��һ��void(void)����ǩ��,ȴ���Դ���lambda,��ͨ����,�º�����Щ��ͬ����?
//std::function���������Ͳ����ķ�������ʵ��,���Ͳ�����һ�ֽ�����̬����ɵļ���,function��
//����base��,���ݽ����Ķ���Ϊderived��,ͨ����derived���ݸ�base�ķ�ʽʵ����std::function
//���Թ���ͬ���͵�"����"
//��ʵ������

template<typename func>
struct function;//function������funcΪfuncΪ����ǩ��

template<typename Rtype, typename...Args>//RtypeΪ������������, �βΰ�Ϊ���ݸ������Ĳ���
struct function<Rtype(Args...)> {//����ǩ��,Ҳ����function<void(void)>,function<int(int,double)>������ʽ

    template<typename T>
    function(T f):ptr(new eraseDerived<T>(f)) {}//ע��,ptrָ����eraseBase����,������������Ҫ����һ��Derived��������ɶ�̬
    //T ��ʶ������������Ǻ���ָ�뻹��lambda,�����Ƿº���...,

    Rtype operator()(Args...args) {//����º����Ǵ�function�Ƕ�������,���紴����function<void(void)> a,��ʱa()���õľ��Ǹú���
        if (ptr)
            return ptr->invoke(std::forward<Args>(args)...);//invoke�ǵ��ö������Լ��ĺ���,ͨ������ת�����ݲ���.
        else throw std::bad_function_call();//��ָ���׳��쳣
    }

    function(const function &other) {
        if (other.ptr)
            ptr = other.ptr->copy();//����ʹ��copy��ֹǳ����
        else ptr = nullptr;
    }

    function(function &&other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    function &operator=(const function &other) {
        if (this == &other) {
            return *this;
        }
        delete ptr;
        ptr = nullptr;

        if (other.ptr) {
            ptr = other.ptr->copy();//��ֹǳ����
        }
        return *this;
    }

    function &operator=(function &&other) noexcept {
        if (this == other) {
            return *this;
        }

        delete ptr;
        ptr = nullptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    ~function() {
        delete ptr;
    }

private:
    //ʵ�����Ͳ���,
    //��Ҫ����Ķ�����Ҫʵ��invoke����,��copy����������Ҫ����Ϊ�麯��
    struct eraseBase {
        virtual ~eraseBase() = default;
        virtual Rtype invoke(Args...args) const noexcept = 0;
        virtual eraseBase *copy() = 0;
    };

    template<typename T>
    struct eraseDerived : eraseBase {

        explicit eraseDerived(T f) : func(std::move(f)) {}

        Rtype invoke(Args...args) const noexcept override {//�����Լ�
            return func(std::forward<Args>(args)...);
        }

        eraseBase *copy() override {
            return new eraseDerived(func);
        }

    private:
        T func;
    };

public:

    eraseBase *ptr;
};

void foo() {
    std::cout << __func__ << std::endl;
}

void test(const function<void(void)> x) {
    std::cout << "YES" << std::endl;
}

int main() {
    //demo:
    function<int(int, int)> a = [](int x, int y) { return x + y; };
    std::cout << a(1, 2) << std::endl;//OK

    function<void(void)> b = foo;
    b();//OK

    struct A {
        void operator()() const {//const��Ա�������ܵ��÷�const����
            std::cout << "operator" << std::endl;
        }
    };

    function<void(void)> func = A{};
    func();

}
