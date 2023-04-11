#include <iostream>

int main() {

    //���ó�Ա�����ķ�ʽ�ȼ�����
    //demo:
    struct demo1 {
        void print() {
            std::cout << a << " " << b << " " << c << std::endl;
        }
        int a, b, c;
    };

    demo1 a{1, 2, 3};//�ۺϳ�ʼ��
    a.print();//123
    //�ȼ�
    //print(demo1* this)
    //print(&a) �����thisָ��

    //���ڳ�Ա�����޶������ù���

    struct demo2 {
        void print() const {
            std::cout << "demo2 const\n";
        }
    };

    demo2 b;
    b.print();//demo2 const  ����ֻ��const�޶�ʱ�����const����

    struct demo3 {
        void print() const {
            std::cout << "demo3 const\n";
        }
        void print() {
            std::cout << "demo3\n";
        }
    };

    demo3 c;
    c.print();//"demo3" ��ͬʱ�������ֺ���ʱ,��const������÷�const��Ա����

    const demo3 d;
    d.print();//"demo3 const" const�������const��Ա����

    struct demo4 {
        void print() &{
            std::cout << "demo4 &\n";
        }

        void print() &&{
            std::cout << "demo4 &&\n";
        }
    };

    demo4 e;
    e.print();//"demo4 &"��ͨ�������&�汾��Ա����
    demo4 &f = e;
    f.print();//"demo4 &"��ֵ���ö������&��Ա����

    std::move(e).print();//"demo4 &&"��ֵ����&&��Ա����
}
