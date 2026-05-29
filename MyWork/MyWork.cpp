#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <windows.h> 

const double PI = 3.14159265358979323846;

// ЗАВДАННЯ 1: ВІРТУАЛЬНЕ УСПАДКУВАННЯ
namespace SpaceTask1 {

    class A {
    protected:
        int dat;
        double arr[5] = { 10, 1, 7, 1, 9 };
    public:
        A() : dat(1) {}
        A(int d) : dat(d) {}
    };

    // БЕЗ ВІРТУАЛЬНОГО УСПАДКУВАННЯ
    class B : protected A {
    protected:
        int b;
    public:
        B() : b(1) {}
        B(int d, int dt) : A(dt), b(d) {}
    };

    class C : protected A {
    protected:
        double c;
    public:
        C() : c(1.0) {}
        C(int d, double dt) : A(d), c(dt) {}
    };

    class D : protected A {
    protected:
        int d;
    public:
        D() : d(1) {}
        D(int val, int dt) : A(dt), d(val) {}
    };

    class E : protected B, protected C {
    protected:
        double e;
    public:
        E() : e(1.0) {}
        E(int a1, int b1, int c1, double d1, int e1) : B(a1, b1), C(c1, d1), e(e1) {}
    };

    class F : protected D {
    protected:
        double f;
    public:
        F() : f(1.0) {}
        F(int val, int dt, double f_val) : D(val, dt), f(f_val) {}
    };

    class G : protected E, protected D, protected F {
    protected:
        double gt;
    public:
        G() : gt(1.0) {}
        G(int a1, int b1, int c1, double d1, int e1, int d_val, int d_dt, int f_val, int f_dt, double f_d, double g_val)
            : E(a1, b1, c1, d1, e1), D(d_val, d_dt), F(f_val, f_dt, f_d), gt(g_val) {
        }

        void showDat() {
            std::cout << "  [Без virtual] dat =? Error C2385 ambiguous access (дубльовано у кожній гілці)\n";
            std::cout << "  Доступ через E::B::A::dat = " << E::B::A::dat << std::endl;
            std::cout << "  Доступ через E::C::A::dat = " << E::C::A::dat << std::endl;
            std::cout << "  Доступ через D::A::dat    = " << D::A::dat << std::endl;
        }
    };

    // З ВІРТУАЛЬНИМ УСПАДКУВАННЯМ
    class BV : virtual protected A {
    protected:
        int b;
    public:
        BV() : b(1) {}
        BV(int d, int dt) : A(dt), b(d) {}
    };

    class CV : virtual protected A {
    protected:
        double c;
    public:
        CV() : c(1.0) {}
        CV(int d, double dt) : A(d), c(dt) {}
    };

    class DV : virtual protected A {
    protected:
        int d;
    public:
        DV() : d(1) {}
        DV(int val, int dt) : A(dt), d(val) {}
    };

    class EV : virtual protected BV, virtual protected CV {
    protected:
        double e;
    public:
        EV() : e(1.0) {}
        EV(int a1, int b1, int c1, double d1, int e1) : BV(a1, b1), CV(c1, d1), e(e1) {}
    };

    class FV : virtual protected DV {
    protected:
        double f;
    public:
        FV() : f(1.0) {}
        FV(int val, int dt, double f_val) : DV(val, dt), f(f_val) {}
    };

    class GV : virtual protected EV, virtual protected DV, virtual protected FV {
    protected:
        double gt;
    public:
        GV() : gt(1.0) {}
        GV(int base_dat, int a1, int b1, int c1, double d1, int e1, int d_val, int d_dt, int f_val, int f_dt, double f_d, double g_val)
            : A(base_dat), EV(a1, b1, c1, d1, e1), DV(d_val, d_dt), FV(f_val, f_dt, f_d), gt(g_val) {
        }

        void showDat() {
            std::cout << "  [З virtual] Прямий доступ до dat = " << A::dat << std::endl;
            std::cout << "  EV::BV::A::dat = " << EV::BV::A::dat << std::endl;
            std::cout << "  DV::A::dat     = " << DV::A::dat << std::endl;
        }
    };

    void mainTask1() {
        std::cout << "=== ЗАВДАННЯ 1: ВІРТУАЛЬНЕ УСПАДКУВАННЯ (ЗА ЗРАЗКОМ) ===\n\n";

        int inputDat;
        std::cout << "Введіть початкове значення для поля dat: ";
        std::cin >> inputDat;

        G obj(5, inputDat, 7, 2.5, 10, 12, inputDat + 1, 14, inputDat + 2, 5.5, 99.9);
        GV objV(inputDat, 5, 20, 7, 2.5, 10, 12, 21, 14, 22, 5.5, 99.9);

        std::cout << "\n--- Розміри класів (Без віртуального успадкування) ---\n";
        std::cout << "Size for Base A: " << sizeof(A) << " bytes\n";
        std::cout << "Size for B:      " << sizeof(B) << " bytes\n";
        std::cout << "Size for C:      " << sizeof(C) << " bytes\n";
        std::cout << "Size for E:      " << sizeof(E) << " bytes\n";
        std::cout << "Size for G (об'єкт obj): " << sizeof(obj) << " bytes\n";

        std::cout << "\n--- Розміри класів (З віртуальним успадкуванням) ---\n";
        std::cout << "Size for BV:     " << sizeof(BV) << " bytes\n";
        std::cout << "Size for CV:     " << sizeof(CV) << " bytes\n";
        std::cout << "Size for EV:     " << sizeof(EV) << " bytes\n";
        std::cout << "Size for GV (об'єкт objV): " << sizeof(objV) << " bytes\n\n";

        std::cout << "--- Перевірка доступу до даних (showDat) ---\n";
        obj.showDat();
        std::cout << std::endl;
        objV.showDat();
    }
}

// ЗАДAЧА 2.15: АБСТРАКТНИЙ КЛАС ТА ПЛОЩА ПОВЕРХНІ
namespace SpaceTask2 {
    using namespace std;

    class Shape {
    protected:
        string name;
        double baseParam;
    public:
        Shape() : name("noname"), baseParam(0.0) {}
        Shape(string n, double bp) : name(n), baseParam(bp) {}
        virtual ~Shape() {}

        virtual double surfaceArea() const = 0;
        virtual string printName() const = 0;
    };

    class Parallelepiped : public Shape {
    private:
        double x, y;
    public:
        Parallelepiped(string n, double bp, double _x, double _y) : Shape(n, bp), x(_x), y(_y) {}

        virtual double surfaceArea() const override { return 6 * x * y; }
        virtual string printName() const override {
            return "Паралелепіпед " + name + " (Дод. параметр: " + to_string(baseParam) + ")";
        }
    };

    class Sphere : public Shape {
    private:
        double r;
    public:
        Sphere(string n, double bp, double _r) : Shape(n, bp), r(_r) {}

        virtual double surfaceArea() const override { return 4 * PI * r * r; }
        virtual string printName() const override {
            return "Куля " + name + " (Дод. параметр: " + to_string(baseParam) + ")";
        }
    };

    class Tetrahedron : public Shape {
    private:
        double a;
    public:
        Tetrahedron(string n, double bp, double _a) : Shape(n, bp), a(_a) {}

        virtual double surfaceArea() const override { return a * a * std::pow(PI, 3); }
        virtual string printName() const override {
            return "Тетраедр " + name + " (Дод. параметр: " + to_string(baseParam) + ")";
        }
    };

    string setNameShapes() {
        int r1 = rand() % 6;
        int r2 = rand() % 6;
        string n1[7] = { "Альфа", "Бета", "Гамма", "Омега", "Зета", "Дельта", "Сігма" };
        string n2[7] = { "-1", "-2", "-A", "-B", "-X", "-Pro", "-Max" };
        return n1[r1] + n2[r2];
    }

    void mainTask2() {
        cout << "=== ЗАВДАННЯ 2.15: ГЕОМЕТРИЧНІ ФІГУРИ (ЗА ЗРАЗКОМ) ===\n\n";

        Shape** masShapes;
        int n = 0, type = 1;
        double bp = 0.0;
        string name;

        do {
            cout << "Скільки фігур створити? (1-100): ";
            cin >> n;
        } while (n <= 0 || n > 100);

        masShapes = new Shape * [n];

        cout << "Для генерації випадкових фігур натисніть 1, для ручного введення — будь-яке інше число: ";
        int rn;
        cin >> rn;
        srand(static_cast<unsigned int>(time(NULL)));

        for (int i = 0; i < n; i++) {
            double p1 = 0, p2 = 0;
            if (rn == 1) {
                type = 1 + rand() % 3;
                bp = (rand() % 50) / 2.0;
                name = setNameShapes();
                p1 = 1 + (rand() % 10);
                p2 = 1 + (rand() % 10);
            }
            else {
                do {
                    cout << "\nОберіть тип фігури для елемента [" << i + 1 << "]:\n";
                    cout << "1 - Паралелепіпед\n";
                    cout << "2 - Куля\n";
                    cout << "3 - Тетраедр\n";
                    cout << "Ваш вибір: "; cin >> type;
                } while (type < 1 || type > 3);

                cout << "Введіть назву фігури: "; cin >> name;
                cout << "Введіть додатковий параметр базового класу: "; cin >> bp;

                if (type == 1) {
                    cout << "Введіть сторону x: "; cin >> p1;
                    cout << "Введіть сторону y: "; cin >> p2;
                }
                else if (type == 2) {
                    cout << "Введіть радіус r: "; cin >> p1;
                }
                else if (type == 3) {
                    cout << "Введіть ребро а: "; cin >> p1;
                }
            }

            switch (type) {
            case 1: masShapes[i] = new Parallelepiped(name, bp, p1, p2); break;
            case 2: masShapes[i] = new Sphere(name, bp, p1); break;
            case 3: masShapes[i] = new Tetrahedron(name, bp, p1); break;
            }
        }

        cout << "\n--- Список створених фігур та їхні площі: ---\n";
        double totalArea = 0.0;
        for (int i = 0; i < n; i++) {
            cout << masShapes[i]->printName() << " -> Площа: " << masShapes[i]->surfaceArea() << endl;
            totalArea += masShapes[i]->surfaceArea();
        }

        cout << "\nЗагальна сума площ усіх фігур: " << totalArea << endl;

        for (int i = 0; i < n; i++) { delete masShapes[i]; }
        delete[] masShapes;
    }
}

// ЗАДAЧА 3.15: МНОЖИННЕ УСПАДКУВАННЯ
namespace SpaceTask3 {
    using namespace std;

    class Ship {
    protected:
        string marka;
        float power;
        int numberOfWheels;
    public:
        Ship() : marka("Neoplan-Marine"), power(5.2f), numberOfWheels(6) {}
        Ship(string m, float p, int nw) : marka(m), power(p), numberOfWheels(nw) {}

        string getMarka() { return marka; }
        void setMarka(string m) { marka = m; }
        float getPower() { return power; }
        void setPower(float p) { power = p; }
        int getNumberOfWheels() { return numberOfWheels; }
        void setNumberOfWheels(int n) { numberOfWheels = n; }

        string toString() {
            return marka + "\t" + to_string(power) + "\t" + to_string(numberOfWheels) + "\t";
        }
    };

    class PassengerTransport {
    protected:
        int flightNumber;
        int numberOfPassengerSeats;
    public:
        PassengerTransport() : flightNumber(101), numberOfPassengerSeats(45) {}
        PassengerTransport(int f, int n) : flightNumber(f), numberOfPassengerSeats(n) {}

        int getFlightNumber() { return flightNumber; }
        void setFlightNumber(int f) { flightNumber = f; }
        int getNumberOfPassengerSeats() { return numberOfPassengerSeats; }
        void setnumberOfPassengerSeats(int n) { numberOfPassengerSeats = n; }

        string toString() {
            return to_string(flightNumber) + "\t" + to_string(numberOfPassengerSeats) + "\t";
        }
    };

    class PassengerShip : public Ship, public PassengerTransport {
    private:
        string shipRoute;
    public:
        PassengerShip() : shipRoute("Kyiv-Chernivtsi(Water)") {}
        PassengerShip(string m, float p, int nw, int f, int n, string sr)
            : Ship(m, p, nw), PassengerTransport(f, n), shipRoute(sr) {
        }

        string getShipRoute() { return shipRoute; }
        void setShipRoute(string sr) { shipRoute = sr; }

        string toString() {
            return Ship::toString() + PassengerTransport::toString() + shipRoute;
        }
    };

    void mainTask3() {
        cout << "=== ЗАВДАННЯ 3.15: ІЄРАРХІЯ КОРАБЛІВ (ЗА ЗРАЗКОМ) ===\n\n";

        PassengerShip def;
        PassengerShip odesaCh("Odesa-Express", 8.5f, 4, 707, 120, "Odesa-Chernivtsi");

        PassengerShip* pShip = new PassengerShip();
        pShip->setMarka("Yamaha-Marine");
        pShip->setPower(12.4f);
        pShip->setNumberOfWheels(2);
        pShip->setFlightNumber(808);
        pShip->setnumberOfPassengerSeats(50);
        pShip->setShipRoute("Mykolaiv-Chernivtsi");

        cout << "Марка\tПотужн.\tГвинти\tРейс\tМісця\tМаршрут\n";
        cout << "---------------------------------------------------------\n";
        cout << def.toString() << endl;
        cout << odesaCh.toString() << endl;
        cout << pShip->toString() << endl;

        delete pShip;
    }
}

// ГОЛОВНА ФУНКЦІЯ
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;

    do {

        std::cout << "=========================================================\n";
        std::cout << "          ЛАБОРАТОРНА РОБОТА N6. ВАРІАНТ 15\n";
        std::cout << "=========================================================\n";
        std::cout << "1. Завдання 1: Віртуальне успадкування (За схемою рис. 15)\n";
        std::cout << "2. Завдання 2: Геометричні фігури (Абстрактний клас)\n";
        std::cout << "3. Завдання 3: Пасажирський корабель (Множинне успадкування)\n";
        std::cout << "0. Вихід з програми\n";
        std::cout << "---------------------------------------------------------\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;
        std::cout << "=========================================================\n\n";

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            SpaceTask1::mainTask1();
            std::cout << "\nНатисніть Enter для повернення в меню...";
            std::cin.ignore(32767, '\n');
            std::cin.get();
            break;
        case 2:
            SpaceTask2::mainTask2();
            std::cout << "\nНатисніть Enter для повернення в меню...";
            std::cin.ignore(32767, '\n');
            std::cin.get();
            break;
        case 3:
            SpaceTask3::mainTask3();
            std::cout << "\nНатисніть Enter для повернення в меню...";
            std::cin.ignore(32767, '\n');
            std::cin.get();
            break;
        case 0:
            std::cout << "Вихід виконано. Гарного дня!\n";
            break;
        default:
            std::cout << "Некоректний вибір! Спробуйте ще раз.\n";
            Sleep(1500);
            break;
        }

    } while (choice != 0);

    return 0;
}