#include <iostream>
#include <cmath>
using namespace std;

class Cone {
private:
    int *radius, *height;

public:
    Cone() {
        cout << "Викликаємо конструктор..." << endl;
        radius = new int;
        height = new int;
        *radius = *height = 0;
    }

    Cone(int Radius, int Height) {
        cout << "Викликаємо конструктор з параметрами..." << endl;
        radius = new int;
        height = new int;
        *radius = Radius;
        *height = Height;
    }

    Cone(const Cone &obj) {
        cout << "Викликаємо конструктор копіювання..." << endl;
        radius = new int;
        height = new int;
        *this -> radius = *obj.radius;
        *this -> height = *obj.height;
    }

    ~Cone() {
        cout << "Викликаємо деструктор..." << endl;
        delete radius;
        delete height;
    }

    double GetRadius() const {
        return *radius;
    }

    double GetHeight() const {
        return *height;
    }

    void SetRadius(int Radius) const {
        while (Radius <= 0) {
            cout << "Некоректно значення радіуса! Введіть ще раз: ";
            cin >> Radius;
        }
        *radius = Radius;
    }

    void SetHeight(int Height) const {
        while (Height <= 0) {
            cout << "Некоректно значення висоти! Введіть ще раз: ";
            cin >> Height;
        }
        *height = Height;
    }

    void Print() const {
        cout << "Радіус: " << *radius << "\tВисота: " << *height << "\n\n";
    }

    double Volume() const {
        return (M_PI * *radius * *radius * *height) / 3;
    }

    double Area() const {
        double l;
        l = sqrt(*height * *height + *radius * *radius);     // твірна конуса
        return M_PI * *radius * (*radius + l); // повна площа поверхні конуса
    }
};

Cone operator+ (const Cone& obj1, const Cone& obj2) {
    int resRad, resHi;
    resRad = obj1.GetRadius() + obj2.GetRadius();
    resHi  = obj1.GetHeight() + obj2.GetHeight();
    Cone result(resRad, resHi);
    cout << "\nСума радіусів двох конусів: " << resRad << "\nСума висот    двох конусів: " << resHi << "\n\n";
    return result;
}

bool operator == (const Cone& obj1, const Cone& obj2) {
    return obj1.Volume() == obj2.Volume();
}

bool operator > (const Cone& obj1, const Cone& obj2) {
    return obj1.Volume() > obj2.Volume();
}

bool operator < (const Cone& obj1, const Cone& obj2) {
    return obj1.Volume() < obj2.Volume();
}

Cone Average(const Cone &obj1, const Cone &obj2) {
    double resAverRadCons, resAverHiCons;
    int resAverRad, resAverHi;
    resAverRadCons = (obj1.GetRadius() + (double)obj2.GetRadius())/2;
    resAverHiCons  = (obj1.GetHeight() + (double)obj2.GetHeight())/2;
    cout << "Середнє арифметичне радіусів конусів: " << resAverRadCons << "\nСереднє арифметичне висот конусів: " << resAverHiCons << "\n\n";
    resAverRad = (int)resAverRadCons;
    resAverHi = (int)resAverHiCons;
    Cone resultAver(resAverRad, resAverHi);
    return resultAver;
}

ostream& operator<<(ostream& os, const Cone& obj) {
    os << '(' << obj.GetRadius() << ',' << obj.GetHeight() << ')';
    return os;
}

istream& operator>>(istream& in, const Cone &obj) {
    int Radius, Height;
    cout << "Введіть радіус: ";
    in >> Radius;
    obj.SetRadius(Radius);
    cout << "Введіть  висоту: ";
    in >> Height;
    obj.SetHeight(Height);
    return in;
}

int main() {
    system("chcp 1251");

    int rad1, hi1, rad2, hi2;

    Cone obj1;
    cout << "Введіть радіус: ";
    cin >> rad1;
    obj1.SetRadius(rad1);
    cout << "Введіть висоту: ";
    cin >> hi1;
    obj1.SetHeight(hi1);
    obj1.Print();
    cout << "Об'єм конуса: " << obj1.Volume() << "\n";
    cout << "Площа повної поверхні конуса: " << obj1.Area() << "\n\n";

    Cone *obj2;
    obj2 = new Cone;
    cout << "Введіть радіус: ";
    cin >> rad2;
    obj2 -> SetRadius(rad2);
    cout << "Введіть висоту: ";
    cin >> hi2;
    obj2 -> SetHeight(hi2);
    obj2 -> Print();
    cout << "Об'єм конуса: " << obj2 -> Volume() << "\n";
    cout << "Площа повної поверхні конуса: " << obj2 -> Area() << "\n\n";


bool boolRes1 = obj1.Volume() >  obj2 -> Volume();
    bool boolRes2 = obj1.Volume() == obj2 -> Volume();

    if (boolRes2) cout << "Об'єм конуса 1 дорівнює об'єму конуса 2.\n";
    else cout << "Об'єм конуса 1 " << (boolRes1 ? "більший" : "менший") << ", ніж об'єм конуса 2.\n";

    Cone objSum = obj1 + *obj2;
    Cone objAver = Average(obj1, *obj2);

    Cone obj3(6,8);
    Cone *arrCone[] = {&obj1, obj2, &obj3};

    int k1, k2, kst, i;
    kst = sizeof(arrCone)/sizeof(*arrCone);
    Cone *arrConeTemp;

    /* Insertion Sort */
    cout << "\n/* Insertion Sort */\n";
    for (k1 = 1; k1 < kst; k1++) {
        arrConeTemp = *(arrCone+k1);
        k2 = k1-1;
        while (k2 >= 0 and (*arrConeTemp < *arrCone[k2])) {
            (arrCone[k2+1]) = arrCone[k2];
            k2--;
        }
        arrCone[k2+1] = arrConeTemp;
    }

    for (i = 0; i < kst; i++) {
        cout << *(arrCone[i]) << " - Volume: " << arrCone[i] -> Volume() << " \n";
    }

    int sumRadius = 0, sumHeight = 0;
    double resRadAver, resHiAver;

    for (i = 0; i < kst; i++) {
        sumRadius += arrCone[i] -> GetRadius();
        sumHeight += arrCone[i] -> GetHeight();
    }
    resRadAver = (double)sumRadius / kst;
    resHiAver  = (double)sumHeight / kst;

    cout << "\nСереднє арифметичне радіусів конусів у масиві: " << resRadAver << "\nСереднє арифметичне    висот конусів у масиві: " << resHiAver << "\n\n";

    Cone objTest;
    cin >> objTest;
    objTest.Print();

    cout <<  obj1     << " - obj1\n";
    cout << *obj2     << " - obj2\n";
    cout <<  obj3     << " - obj3\n";
    cout <<  objSum   << " - objSum\n";
    cout <<  objAver  << " - objAver\n";
    cout <<  objTest  << " - objTest\n";
    
    delete obj2;
    getchar();getchar();
    return 0;
}
