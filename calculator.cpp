#include <iostream>
#include <string>

using namespace std;

// Функция для проверки, является ли символ оператором (+, -, *, /)
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Функция для выполнения операции над двумя числами
int applyOperator(int a, char op, int b)
{
    if (op == '+')
    {
        return a + b;
    }
    if (op == '-')
    {
        return a - b;
    }
    if (op == '*')
    {
        return a * b;
    }
    if (op == '/')
    {
        if (b == 0)
        {
            cout << "Ошибка: деление на ноль" << endl;
            return 0;
        }
        return a / b;
    }
    return 0;
}

int evaluateExpression(string expression)
{
    const int MAX_SIZE = 100;
    int numStack[MAX_SIZE];
    char opStack[MAX_SIZE];
    int numTop = -1;
    int opTop = -1;

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char c = expression[i];
        if (isdigit(c))
        {
            // Если символ - цифра, то собираем число
            int num = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                ++i;
            }
            numStack[++numTop] = num;               // Помещаем число в стек чисел
            --i;                // Возвращаемся назад, так как цикл for увеличивает i
        }
        else if (c == '(')
        {
            opStack[++opTop] = c;
        }
        else if (c == ')')  // При закрывающей скобке выполняем все операции внутри скобок
        {
            while (opTop >= 0 && opStack[opTop] != '(')
            {
                int a = numStack[numTop--]; // Получаем первое число
                int b = numStack[numTop--]; // Получаем второе число
                char op = opStack[opTop--]; // Получаем оператор
                numStack[++numTop] = applyOperator(a, op, b);       // Выполняем операцию и помещаем результат в стек чисел
            }
            if (opTop >= 0 && opStack[opTop] == '(')
            {
                opTop--;        // Удаляем открывающую скобку из стека операторов
            }
        }
        else if (isOperator(c))
        {
            while (opTop >= 0 && isOperator(opStack[opTop]) &&
                ((c == '+' || c == '-') && (opStack[opTop] == '*' || opStack[opTop] == '/')))
            {
                int a = numStack[numTop--];
                int b = numStack[numTop--];
                char op = opStack[opTop--];
                numStack[++numTop] = applyOperator(a, op, b);
            }
            opStack[++opTop] = c;
        }
    }

    while (opTop >= 0)
    {
        int a = numStack[numTop--];
        int b = numStack[numTop--];
        char op = opStack[opTop--];
        numStack[++numTop] = applyOperator(a, op, b);
    }

    return numStack[numTop];
}

int main()
{
    setlocale(LC_ALL, "RUS");
    string expression;
    cout << "Введите арифметическое выражение: ";
    cin >> expression;

    int result = evaluateExpression(expression);
    cout << "Результат: " << result << endl;

    /*Calculator
    Мы начинаем смотреть на каждую букву и знак в выражении один за другим
    Если мы видим число, например "5", мы кладем его в коробку numStack
    Если мы видим скобку "(" то мы кладем ее в коробку opStack
    Если мы видим скобку ")", это означает, что нужно сначала решить задачи внутри скобок
    Мы берем числа и операторы из коробок и считаем результат
    Если мы видим оператор (+, -, *, /), то мы проверяем нужно ли его выполнить сейчас или подождать
    Если да, мы считаем результат
    Мы  продолжаем этот процесс для каждой буквы и знака в выражении
    В конце когда мы обработали всё выражение, у нас остаются числа и операторы в коробках numStack и opStack
    Мы берем их и выполняем оставшиеся операции
    И вот результат – это то, что программа выведет на экран
    
    Переменные, которые помогают нам:
    Мы используем коробку numStack для хранения чисел из выражения
    Также у нас есть коробка opStack, в которую мы складываем операторы (это такие знаки, как +, -, *, /)
    Есть numTop и opTop – это как индексы вершины каждой коробки, чтобы мы знали, где находятся последние числа и операторы*/
}
