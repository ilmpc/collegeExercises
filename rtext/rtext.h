#ifndef RTEXT_RTEXT_H
#define RTEXT_RTEXT_H

#include <cstdio>
#include <iostream>


namespace RText {
    /**
    * @param src исходная строка
    * @param dst строка на которую заменяем
    * @return количество замен
    */
    int replaceStrings(FILE *in, FILE *out, const char *src, const char *dst);

    int replaceStrings(std::ifstream &input, std::ostream &output, const std::string &src, const std::string &dst);
    /**
     * @param s_filename путь исходного файла
     * @param d_filename путь итогового
    * @param src исходная строка
    * @param dst строка на которую заменяем
    * @return количество замен
     */
    int replaceStrings(const std::string &s_filename, const std::string &d_filename, const std::string &src,
                       const std::string &dst);
}
#endif //RTEXT_RTEXT_H
