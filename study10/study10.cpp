/*
* 名称：类测试
* 
* 收获：
* 1、类的外部不允许调用受保护和私有的成员(函数和变量)
* 2、但是可以通过：外部调用公有函数，公有函数调用内部函数或直接修改变量
*/

#include <iostream>
#define DEBUG
#ifdef DEBUG
std::string  debug_info;
#endif // DEBUG


class Box_class
{
public:             //公有成员
    double length;
    double breadth;
    double height;

    double get_info(void);
    void set_size(double x, double y, double z);
    double get_volume(void)                     //内联函数
    {
#ifdef DEBUG
        debug_info = "get_volume";
        std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG
        return length * breadth * height;
    }
    void set_last_api_protected(double x, double y, double z);
    void set_last_api_private(double x, double y, double z);
    void get_last_info(void);
    double set_last_volume(double v);
protected:          //受保护成员
    void set_last_data_protected(double x , double y, double z);
    double last_volume;
private:            //私有成员
    double last_length;
    double last_breadth;
    double last_height;
    void set_last_data_private(double x, double y, double z);
};

void class_creat_test(void);
void class_modifier_test(void);

int main()
{
    //class_creat_test();
    //class_modifier_test();


    std::cout << "\n测试完成\n";
    return 0;
}

double Box_class::get_info(void)
{
#ifdef DEBUG
    debug_info = "get_info";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG

    std::cout << "长:" << length << "\t宽:" << breadth << "\t高:" << height;
    return length * breadth * height;
}

void Box_class::set_size(double x, double y, double z)
{   
#ifdef DEBUG
    debug_info = "set_size";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG

    //历史记录
    last_length = length;
    last_breadth = breadth;
    last_height = height;

    length = x;
    breadth = y;
    height = z;
}

void Box_class::set_last_data_protected(double x, double y, double z)
{
#ifdef DEBUG
    debug_info = "set_last_data_protected";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG

    last_length = x;
    last_breadth = y;
    last_height = z;
}

void Box_class::set_last_data_private(double x, double y, double z)
{
#ifdef DEBUG
    debug_info = "set_last_data_private";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG

    last_length = x;
    last_breadth = y;
    last_height = z;
}

void Box_class::set_last_api_protected(double x, double y, double z)
{
#ifdef DEBUG
    debug_info = "set_last_api_protected";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG
    set_last_data_protected(x, y, z);
}

void Box_class::set_last_api_private(double x, double y, double z)
{
#ifdef DEBUG
    debug_info = "set_last_api_private";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG
    set_last_data_private(x, y, z);
}

void Box_class::get_last_info(void)
{
#ifdef DEBUG
    debug_info = "get_last_info";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG
    std::cout << "last\t长: " << last_length << "\t宽: " << last_breadth << "\t高: " << last_height << std::endl;
}

double Box_class::set_last_volume(double v)
{
#ifdef DEBUG
    debug_info = "set_last_volume";
    std::clog << "---LOG: running " << debug_info << "()" << std::endl;
#endif // DEBUG
    last_volume = v;
    return last_volume;
}

void class_creat_test(void)
{
    std::cout << "创建两个Box对象并赋值:" << std::endl;

    Box_class box_test_1, box_test_2;
    box_test_1.length = 1;
    box_test_1.breadth = 2;
    box_test_1.height = 3;
    box_test_2.set_size(6, 7, 8);

    std::cout << "Box1:" << std::endl;
    std::cout << "\t体积:" << box_test_1.get_info() << std::endl;

    std::cout << "Box2:" << std::endl;
    std::cout << "\t体积:" << box_test_2.get_info() << std::endl;

}

void class_modifier_test(void)
{
    std::cout << "修饰符测试" << std::endl;

    Box_class box_test;
    box_test.set_size(2, 3, 4);
    box_test.set_size(3, 4, 5);

    box_test.get_last_info();

    //以下语句编译器报错，说明类的外部不允许访问受保护和私有的函数
 //   box_test.set_last_data_private(1, 1, 1);
 //   box_test.set_last_data_protected(1, 1, 1);
    
 //以下语句编译器报错，说明类的外部也不能访问受保护和私有的变量
//    box_test.last_volume = 10.0;
//    box_test.last_length = 2;

    std::cout << "尝试通过公有函数来调用受保护函数：" << std::endl;
    box_test.set_last_api_protected(1, 1, 1);
    box_test.get_last_info();

    std::cout << "尝试通过公有函数来调用私有函数：" << std::endl;
    box_test.set_last_api_private(2, 2, 2);
    box_test.get_last_info();

    std::cout << "尝试通过公有函数直接修改受保护变量：" << std::endl;
    double v = box_test.set_last_volume(1112.0);
    std::cout << "volume = " << v << std::endl;

    box_test.get_info();                //说明最新数据没有被更改
}