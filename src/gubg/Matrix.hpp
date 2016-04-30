#ifndef HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED

#include <vector>

namespace gubg { 

    template <typename T>
        class Matrix
        {
            public:
                Matrix(size_t nr_row, size_t nr_col): elements_(nr_row*nr_col)
            {
            }

            private:
                using Elements = std::vector<T>;
                Elements elements_;
        };

} 

#endif
