// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

#include <cstddef>

class String {
private:
    size_t *_refCounter;
    size_t _capacity;
    char *_data;
    size_t CStringLen(const char* str) const;
public:
    /**
     * Конструктор по умолчанию
     */
    String();
    /**
     * Конструктор принимающий C-строку. Конструктор выполняет полное копирование строки.
     * @param str C-строка
     */
    explicit String(const char *str);
    /**
     * Копирует первые @p n символов (не считая NULL-терминатор) из строки @p str
     */
    String(const char *str, size_t n);
    /**
     * Заполняет строку символами @p c в количестве @p n штук
     */
    String(size_t n, char c);
    /**
     *  Конструктор копий. Полного копирования не происходит. Применяется техника reference counting.
     */
    String(const String &str);
    /**
     * Копирование части строки @p str начиная с позиции @p pos и охватывая @p len символов. Если @p len равняет #npos, то копируем до конца строки @p str. Если @p pos больше размера строки, то выбрасывается исключение @throws std::out_of_range("message");
     */
    String(const String &str, size_t pos, size_t len = npos);
    /**
     * Деструктор. Уменьшаем счетчик ссылок и если он равен нулю, то освобождаем динамически выделенную память, в противном случае, ничего не делаем.
     */
    virtual ~String();
    /**
     * @return возвращает текущий размер строки без учета NULL-терминатора
     */
    size_t size() const;
    /**
     * @return возвращает размер выделенной памяти
     */
    size_t capacity() const;
    /**
     *  изменение размера выделенной памяти. Если запрашиваемый размер @p n больше текущего, то перевыделяем память и копируем туда данные. Иначе ничего не делаем. Стоит отметить, что данный метод никак не влияет на размер строки и её содержимое.
     */
    void reserve(size_t n = 0);
    /**
     * Очищаем строку. Строка становится пустой (с длиной 0)
     */
    void clear();
    /**
     * @return @b true — если строка пустая, @b false — иначе.
     */
    bool empty() const;
    /**
     * По индексу @p pos возвращает ссылку на символ.
     * @throws  std::out_of_range("message") В случае выхода за пределы размера строки
     */
    char &at(size_t pos);
    /**
     * По индексу @p pos возвращает ссылку на символ. Если @p pos равняется длине строки, то метод должен вернуть константную ссылку на '\0'
     * @throws  std::out_of_range("message") В случае выхода за пределы размера строки
     */
    const char &at(size_t pos) const;
    /**
     * Оператор доступа к элементу по индексу. Возвращает ссылку на символ. Если pos больше либо равен длине строки, то будет undefined behaviour (неопределенное поведение).
     */
    char &operator[](size_t pos);
    /**
     *  Оператор доступа к элементу по индексу. Возвращает ссылку на символ. Если pos больше длины строки, то будет undefined behaviour (неопределенное поведение). Если pos равняется длине строки, то оператор должен вернуть константную ссылку на '\0'.
     */
    const char &operator[](size_t pos) const;
    /**
     * Возвращает ссылку на последний символ строки. Если строка пустая, то будет undefined behaviour.
     */
    char &back();
    /**
     * Возвращает константную ссылку на последний символ строки. Если строка пустая, то будет undefined behaviour.
     */
    const char &back() const;
    /**
     * Возвращает ссылку на первый символ строки. Если строка пустая, то будет undefined behaviour.
     */
    char &front();
    /**
     * Возвращает константную ссылку на первый символ строки. Если строка пустая, то будет undefined behaviour.
     */
    const char &front() const;
    // Выполняет конкатенацию строк. Возвращает ссылку на объект, который вызвал данный оператор.
    String &operator+=(const String &str);
    // Выполняет конкатенацию строки и C-строки. Возвращает ссылку на объект, который вызвал данный оператор.
    String &operator+=(const char *str);
    // Выполняет конкатенацию строки и символа. Возвращает ссылку на объект, который вызвал данный оператор.
    String &operator+=(char c);
    // Оператор присваивания. Полного копирования не происходит. Применяется техника reference counting.
    String &operator=(const String &str);
    // Оператор присваивания принимающий C-строку. Оператор выполняет полное копирование строки.
    String &operator=(const char *str);
    /**
     * Выполняет вставку строки str в позицию pos. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &insert(size_t pos, const String &str);
    /**
     * Выполняет вставку строки str в позицию pos. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &insert(size_t pos, const char *str);
    /**
     * Выполняет вставку в позицию pos символов c в количестве n штук. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &insert(size_t pos, size_t n, char c);
    /**
     * Выполняет удаление подстроки в строке начиная с позиции pos и охватывая len символов. Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &erase(size_t pos = 0, size_t len = npos);
    /**
     * Выполняет замену подстроки в строке начиная с позиции pos и охватывая len символов. Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &replace(size_t pos, size_t len, const String &str);
    /**
     * Выполняет замену подстроки в строке начиная с позиции pos и охватывая len символов. Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &replace(size_t pos, size_t len, const char *str);
    /**
     * Выполняет замену подстроки в строке начиная с позиции pos и охватывая len символов. Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");
     */
    String &replace(size_t pos, size_t len, size_t n, char c);
    /*
     * Обмен строками.
     */
    void swap(String &str);
    /**
     * Возвращает указатель на константные символы строки.
     */
    const char *data() const;

    size_t find(const String &str, size_t pos = 0) const;

    size_t find(const char *str, size_t pos = 0) const;

    size_t find(char c, size_t pos = 0) const;

    String substr(size_t pos = 0, size_t len = npos) const;
    /**
     *  Метод для сравнения строк. Применяем лексикографическое сравнение.
     */
    int compare(const String &str) const;
    /**
     *  Метод для сравнения строк. Применяем лексикографическое сравнение.
     */
    int compare(const char *str) const;
    /**
     * Статическая константа с максимальным значением size_t. Это значением может быть использовано в методах для параметра len, что означает "до конца строки". Также эта константа может быть использована в качестве возвращаемого значения для указания отсутствия совпадений
     */
    static const size_t npos = (size_t) -1;
    /**
    * Возвращает текущее количество ссылок на строку. Т.е. количество объектов, которые ссылаются на данную строку.
    */
    size_t countRef() const; 
};
#endif