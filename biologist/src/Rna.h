#ifndef BIOLOGIST_RNK_CONTAINER_H
#define BIOLOGIST_RNK_CONTAINER_H

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <cstddef>
#include <string>
#include <memory>


#define STD_SIZE 256 //!< Размер контейнера создаваемого по умолчанию.
#define STD_GROWTH_RATE 4 //!< Во сколько раз изменяется вместимость контейнера при перевыделении.

namespace biologist {
    /**
     * @class Rna
     * \brief Контейнер для нуклеотидов (2 битные данные)
     */
    class Rna {
        size_t _capacity_Size_t; //!< \var Размер массива контейнеров #_data
        size_t _length; //!< \var Количество нуклеотидов, хранящихся в массиве контейнеров
        size_t *_data; //!< \var Массив контейнеров для хранения нуклеотидов
    public:
        //! Набор возможных нуклеотидов
        enum class Nucleotide {
            A = 0, //!< Аденин
            G = 1, //!< Гуанин
            C = 2, //!< Цитозин
            T = 3, //!< Тимин
            U = 3  //!< Урацил
        };

        struct _Nucleotide_Reference {
        private:
            size_t *_datablock; //!< \var Указатель на конкретный контейнер с нуклеотидами
            size_t _place_bit; //!< \var Место в контейнере в битах

            void set(Nucleotide n); //!< Уставливает заданный нуклеотид

            Nucleotide get() const; //!< Считывает нуклеотид из контейнера

        public:
            /**
             * Конструктор объекта-ссылки на нуклеотид
             * @param datablock ссылка на конкретный контейнер, в котором хранится нуклеотид
             * @param place место нуклеотида в контейнере (2 бит)
             */
            _Nucleotide_Reference(size_t *datablock, size_t place);

            operator Nucleotide() const; //!< Приведение объекта-ссылки к типу нуклеотида

            operator char() const; //!< Приведение объекта-ссылки к символу (A,G,C,T)

            _Nucleotide_Reference &operator=(const Nucleotide right);

            _Nucleotide_Reference &operator=(const _Nucleotide_Reference &right);

            bool operator==(const _Nucleotide_Reference &right) const;

            bool operator!=(const _Nucleotide_Reference &right) const;

            //bool operator<(const _Nucleotide_Reference &right) const;


        };

        static size_t Size_TtoNucl(size_t a) {
            return a * sizeof(size_t) * 4;
        }

        static size_t NucltoSize_T(size_t a) {  //!< Перевод колчичества нуклеодидов, в размер контейнера
            return (((a) / (sizeof(size_t) * 4)) + (((a) % (sizeof(size_t) * 4)) != 0 ? 1 : 0));
        }

        /**
         * @return Вместимость данного объекта (в количестве нуклеотидов)
         */
        size_t getCapacity() const;

        /**
         * @return Количество занятых ячеек (нуклеотидов в цепочке) в данном объекте
         */
        size_t getLength() const;

        operator std::string();

        /**
         * Конструктор по-умолчанию. Создаёт пустой контейнер днк #Rna(size_t capacity_Nuc) с размером #STD_SIZE.
         */
        Rna();

        Rna(size_t capacity_Size_t, void *); //TODO нужен ли мне этот конструктор?

        explicit Rna(size_t capacity_Nuc);

        Rna(Nucleotide n, size_t length);

        Rna(Rna const &p);

        Rna(size_t capacity_Size_t, size_t length, size_t *data);

        ~Rna();

        bool operator==(Rna const &right) const;

        bool operator!=(Rna const &right) const;

        /**
         * Создание комплиментарной данной цепочки РНК
         * @return ссылку на комплементарную РНК
         */
        std::unique_ptr<Rna> operator~() const;

        Rna &operator=(Rna const &right);

        /**
         * Конкатенация двух цепочек РНК
         */
        std::unique_ptr<Rna> operator+(Rna const &right) const;

        /**
         * @throws std::out_of_range при доступе к невыделенной (< this->_capacity_size_t) памяти
         */
        _Nucleotide_Reference operator[](size_t const index);

        /**
         * @throws std::out_of_range при доступе к неиспользуемой (< this->_length) памяти
         */
        Nucleotide operator[](size_t const index) const;

        /**
         * Проверка двух цепочек РНК на комплементарность (A - G, C - T).
         * @param right цепочка для сравнения
         */
        bool isComplementary(Rna const &right) const;

        /**
         *  Создаёт новый объект, копируя нуклеотиды от начала до index.
         * \throws length_error Если изначальная цепочка меньше index
         * @param index номер нуклеотида, до которого копируется цепочка
         * @return Если index > _size, копирует все нуклеотиды из this в новый объект размера index + 1.
        */
        Rna &split(size_t index);

        /**
         * Вставляет n в конец цепочки РНК
         * @param n нуклеотид для вставки
         */
        void push(Nucleotide n);

        /**
         * Извлекает нуклеотид из конца цепочки
         * @return нуклеотид
         */
        Nucleotide pop();

        /**
         * Изменяет размер контейнера внутри объекта
         * \throws length_error Если новый размер < цепочки, хранящихся нуклеотидов (length)
         * @param new_size новый размер контейнера (в количестве нуклеотидов)
         * @return this
         */
        Rna &resize(size_t new_size);

    };

}
#endif //BIOLOGIST_RNK_CONTAINER_H
