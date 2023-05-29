#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x; // координата x
    int y; // координата y
} Point;

typedef struct {
    int id;  // уникальный идентификатор объекта
    char* name; // имя объекта
    Point pos; // текущая позиция объекта
    int* path; // массив для сохранения пройденного пути
    int path_len; // длина пути
} Object;

// Генерация случайного числа в диапазоне [a, b]
int generateRandomNumber(int a, int b) {
    return a + rand() % (b - a + 1);
}

// Инициализация объекта
Object* initObject(int id, char* name) {
    srand(time(NULL)); // инициализировать генератор случайных чисел
    Object* obj = (Object*) malloc(sizeof(Object)); // выделить память под объект
    obj->id = id;
    obj->name = name;
    obj->pos.x = generateRandomNumber(0, 1000);
    obj->pos.y = generateRandomNumber(0, 1000);
    obj->path = (int*) malloc(sizeof(int) * 2); // выделить память под массив пути
    obj->path[0] = obj->pos.x;
    obj->path[1] = obj->pos.y;
    obj->path_len = 2;
    return obj;
}

// Движение объекта
void move(Object* obj) {
    obj->pos.x += generateRandomNumber(-10, 10);
    obj->pos.y += generateRandomNumber(-10, 10);
    // Проверяем, что объект не вышел за границы карты
    if (obj->pos.x < 0) obj->pos.x = 0;
    if (obj->pos.x > 1000) obj->pos.x = 1000;
    if (obj->pos.y < 0) obj->pos.y = 0;
    if (obj->pos.y > 1000) obj->pos.y = 1000;
    // Добавляем точку в массив пути
    obj->path = (int*) realloc(obj->path, sizeof(int) * (obj->path_len + 2));
    obj->path[obj->path_len] = obj->pos.x;
    obj->path[obj->path_len + 1] = obj->pos.y;
    obj->path_len += 2;
}

// Расстояние между двумя точками
double distance(Point p1, Point p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}

// Расстояние между объектами
double distanceTo(Object* obj1, Object* obj2) {
    return distance(obj1->pos, obj2->pos);
}

// Освобождение памяти, занятой под объект
void freeObject(Object* obj) {
    free(obj->name);
    free(obj->path);
    free(obj);
}

// Пример использования
int main() {
    Object* obj1 = initObject(1, "Object 1");
    Object* obj2 = initObject(2, "Object 2");

    for (int i = 0; i < 10000; i++) {
        move(obj1);
        move(obj2);
        double d = distanceTo(obj1, obj2);
        printf("%s is at (%d,%d), %s is at (%d,%d), distance = %f\n",
               obj1->name, obj1->pos.x, obj1->pos.y,
               obj2->name, obj2->pos.x, obj2->pos.y, d);
    }

    freeObject(obj1);
    freeObject(obj2);

    return 0;
}