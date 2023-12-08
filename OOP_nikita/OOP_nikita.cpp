
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

void all_point(POINT*);

class RECT_
{
private:
    //координаты центра
    POINT pt;
    //Ширина
    double a;
    //Высота
    double h;
    //Точки прямоугольника
    POINT all_points[4];
public:
    //конструктор
    ~RECT_() {

    }
    //установка свойств прямоугольника и вычисление точек
    void Set(double x_, double y_, double a_, double h_) {
        pt.x = x_;
        pt.y = y_;
        a = a_;
        h = h_;

        

        all_points[0].x = pt.x - (a / 2);
        all_points[0].y = pt.x - (h / 2);

        all_points[1].x = pt.x - (a / 2);
        all_points[1].y = pt.x + (h / 2);

        all_points[2].x = pt.x + (a / 2);
        all_points[2].y = pt.x + (h / 2);

        all_points[3].x = pt.x + (a / 2);
        all_points[3].y = pt.x - (h / 2);
    }
    //Проверка попадания точки
    bool chek (int x,int y ) {
        HRGN ch = CreateRectRgn(all_points[1].x, all_points[1].y, all_points[3].x, all_points[3].y);
        if (PtInRegion(ch, x, y)==1) {
            return true;
        }
        return false;
       
    }
    //Оператор сравнения
    bool operator ==(RECT_ rect) {
        int count = 0;
        if (pt.x == rect.pt.x) {
            count++;
        }
        if (pt.y == rect.pt.y) {
            count++;
        }
        if (a == rect.a) {
            count++;
        }
        if (h == rect.h) {
            count++;
        }
        if (count == 4) {
            return true;
        }
        return false;
    }
    //Вычисление площади пересечения двух прямоугольников
    double operator&(RECT_ rect) {
       
       

        double cx1 = max(all_points[0].x, rect.all_points[0].x);
        double cy1 = max(all_points[0].y, rect.all_points[0].y);
        double cx2 = min(all_points[2].x, rect.all_points[2].x);
        double cy2 = min(all_points[2].y, rect.all_points[2].y);

        return (cx2 > cx1 && cy2 > cy1 ? (cx2 - cx1) * (cy2 - cy1) : 0)-1;
            
        
    }
    void operator <<(string str) {
        cout << str << endl;
        cout << "Точки центра" << endl << "X: " << pt.x << "  Y: " << pt.y << endl;
        cout << "Ширина: " << a << "  Высота: " << h<<endl;
    }
    string file(string str) {
        string n = "\n", result;
        if (str == "read") {

            ifstream ifs("file.txt", ios::in | ios::binary | ios::ate);

            ifstream::pos_type fileSize = ifs.tellg();
            ifs.seekg(0, ios::beg);

            vector<char> bytes(fileSize);
            ifs.read(bytes.data(), fileSize);

            return string(bytes.data(), fileSize);
        }
        if (str == "record"){
            ofstream    file_record;
                file_record.open("file.txt", std::ios::app);
                if (!file_record.is_open()) {
                    cout << "Файл не может быть открыт!\n";

                }
                file_record <<"X:" << pt.x << " Y:" << pt.y << "\n";
                file_record << "a=" << a << endl;
                file_record << "h=" << h << endl;
                file_record << "Точки вершин\n";
                for (int i = 0; i < 4; i++) {
                    file_record << "X:" << all_points[i].x << " Y:" << all_points[i].y << "\n";
                }
                file_record << "////////////////////////////////////////////////////////\n";
                file_record.close();
                return "";
        }
    }
    //деструктор 
   
};

int main()
{
    setlocale(LC_ALL, "rus");
    RECT_ rect1, rect2;
    int x, y;
    rect1.Set(2, 2, 4, 4);
    rect2.Set(3, 4, 4, 4);
    
    rect1 << "Первый многоугольник\n";
    rect2 << "\nВторой многоугольник\n";

    cout << "Введите точки (ч/з пробел): ";
    cin >> x>>y;

    if (rect1.chek(x, y)) {
        cout << "\nТочка попала!" << endl;
    }
    else {
        cout << "\nТочка не попала!" << endl;
    }

    if (rect1 == rect2) {
        cout << "\nПрямоугольники идентичны!" << endl;
    }
    else {
        cout << "\nПрямоугольники разные!" << endl;
    }
    double s = rect1 & rect2;
    cout << "\nПлощадь пересечения двух прямоугольников: " << s << endl;

    rect1.file("record");
    rect2.file("record");
    string str=rect2.file("read");
    cout << str;
}

