#include <iostream>

int main()
{ 
    int x = 1, y = 1;

    //lambdaʵ�ֽ����º���Ҳ����operator(),����

    auto foo1 = [=](int z) {
        std::cout << x << " " << y << " " << z << std::endl;
    };

    //foo1ʵ�ֵȼ�����

    class foo1_
    {

    public:
        foo1_(int _x, int _y) : x(_x), y(_y) {}
        void operator()(int z) const//const����,���Ա�֤��Ա�����޸�Ҳ����ֵ����,���lambda����mutable����,��ô�˴���û��const
        {
            std::cout << x << " " << y << " " << z << std::endl;
        }

    private:
        int x, y;
        //���񵽵Ĳ���,���Ϊ���ò���˴�Ϊint &x,&y;
    };

    foo1(3);//���1 1 3
    //�ȼ�����
    foo1_{x, y}(3);//���1 1 3
}
