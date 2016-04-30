#ifndef HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED

#include <vector>

namespace gubg { 

    template <typename T>
        class Matrix
        {
            public:
                Matrix() = default;
                Matrix(size_t nr_rows, size_t nr_cols): nr_rows_(nr_rows), nr_cols_(nr_cols)
            {
                allocate_();
            }

                size_t nr_rows() const {return nr_rows_;}
                size_t nr_cols() const {return nr_cols_;}

            private:
                void allocate_()
                {
                    elements_.resize(nr_rows_*nr_cols_);
                }

                size_t nr_rows_ = 0;
                size_t nr_cols_ = 0;

                using Elements = std::vector<T>;
                Elements elements_;
        };

} 

#endif
