
#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <assert.h> /* for assert */
#include <stdlib.h> /* for malloc/realloc/free */
#include <string.h> /* for memcpy/memmove */

/**
 * @brief cvector_vector_type - The vector type used in this library
 */
#define cvector_vector_type(type) type *

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
#define cvector_capacity(vec)                                                                                          \
    ((vec) ? ((size_t *) (vec))[-1] : (size_t) 0)                                                                      \

/**
 * @brief cvector_size - gets the current size of the vector
 * @param vec - the vector
 * @return the size as a size_t
 */
#define cvector_size(vec)                                                                                              \
    ((vec) ? ((size_t *) (vec))[-2] : (size_t) 0)                                                                      \

/**
 * @brief cvector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
#define cvector_empty(vec)                                                                                             \
  (cvector_size(vec) == 0)                                                                                             \

/**
 * @brief cvector_erase - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
#define cvector_erase(vec, i)                                                                                          \
    do {                                                                                                               \
        if (vec) {                                                                                                     \
            const size_t cv_sz = cvector_size(vec);                                                                    \
            if ((i) < cv_sz) {                                                                                         \
                cvector_set_size((vec), cv_sz - 1);                                                                    \
                memmove((vec) + (i), (vec) + (i) + 1, sizeof(*(vec)) * (cv_sz - 1 - (i)));                             \
            }                                                                                                          \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_free(vec)                                                                                              \
    do {                                                                                                               \
        if (vec) {                                                                                                     \
            free(((size_t *) (vec)) - 2);                                                                              \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
#define cvector_begin(vec)                                                                                             \
    (vec)                                                                                                              \

/**
 * @brief cvector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
#define cvector_end(vec)                                                                                               \
    ((vec) ? ((vec) + cvector_size(vec)) : NULL)                                                                       \

/* user request to use logarithmic growth algorithm */
#ifdef CVECTOR_LOGARITHMIC_GROWTH

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                                                                                  \
    do {                                                                                                               \
        const size_t cv_cap = cvector_capacity(vec);                                                                   \
        const size_t cv_sz = cvector_size(vec);                                                                        \
        if (cv_cap <= cv_sz) {                                                                                         \
            cvector_grow((vec), cv_cap ? (cv_cap << 1) : 1);                                                           \
        }                                                                                                              \
        vec[cv_sz] = (value);                                                                                          \
        cvector_set_size((vec), cv_sz + 1);                                                                            \
    } while (0)                                                                                                        \

/**
 * @brief cvector_insert - insert element at position pos to the vector
 * @param vec - the vector
 * @param pos - position in the vector where the new elements are inserted.
 * @param val - value to be copied (or moved) to the inserted elements.
 * @return void
 */
#define cvector_insert(vec, pos, val)                                                                                  \
    do {                                                                                                               \
        const size_t cv_cap = cvector_capacity(vec);                                                                   \
        const size_t cv_sz = cvector_size(vec);                                                                        \
        if (cv_cap <= cv_sz + 1) {                                                                                     \
            cvector_grow((vec), cv_cap ? (cv_cap << 1) : 1);                                                           \
        }                                                                                                              \
        if ((pos) < cv_sz) {                                                                                           \
            memmove((vec) + (pos) + 1, (vec) + (pos), sizeof(*(vec)) * ((cv_sz + 1) - (pos)));                         \
        }                                                                                                              \
        (vec)[(pos)] = (val);                                                                                          \
        cvector_set_size((vec), cv_sz + 1);                                                                            \
    } while (0)                                                                                                        \

#else

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                                                                                  \
    do {                                                                                                               \
        const size_t cv_cap = cvector_capacity(vec);                                                                   \
        const size_t cv_sz = cvector_size(vec);                                                                        \
        if (cv_cap <= cv_sz) {                                                                                         \
            cvector_grow((vec), cv_cap + 1);                                                                           \
        }                                                                                                              \
        vec[cv_sz] = (value);                                                                                          \
        cvector_set_size((vec), cv_sz + 1);                                                                            \
    } while (0)                                                                                                        \

/**
 * @brief cvector_insert - insert element at position pos to the vector
 * @param vec - the vector
 * @param pos - position in the vector where the new elements are inserted.
 * @param val - value to be copied (or moved) to the inserted elements.
 * @return void
 */
#define cvector_insert(vec, pos, val)                                                                                  \
    do {                                                                                                               \
        const size_t cv_cap = cvector_capacity(vec);                                                                   \
        const size_t cv_sz = cvector_size(vec);                                                                        \
        if (cv_cap <= cv_sz + 1) {                                                                                     \
            cvector_grow((vec), cv_cap + 1);                                                                           \
        }                                                                                                              \
        if (pos < cv_sz) {                                                                                             \
            memmove((vec) + (pos) + 1, (vec) + (pos), sizeof(*(vec)) * ((cv_sz + 1) - (pos)));                         \
        }                                                                                                              \
        (vec)[(pos)] = (val);                                                                                          \
        cvector_set_size((vec), cv_sz + 1);                                                                            \
    } while (0)                                                                                                        \

#endif /* CVECTOR_LOGARITHMIC_GROWTH */

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_pop_back(vec)                                                                                          \
    do {                                                                                                               \
        cvector_set_size((vec), cvector_size(vec) - 1);                                                                \
    } while (0)                                                                                                        \

/**
 * @brief cvector_copy - copy a vector
 * @param from - the original vector
 * @param to - destination to which the function copy to
 * @return void
 */
#define cvector_copy(from, to)                                                                                         \
    do {                                                                                                               \
        if (from) {                                                                                                    \
            const size_t cv_size = cvector_size(from);                                                                 \
            cvector_grow(to, cv_size);                                                                                 \
            cvector_set_size(to, cv_size);                                                                             \
            memcpy((to), (from), cv_size * sizeof(*(from)));                                                           \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define cvector_set_capacity(vec, size)                                                                                \
    do {                                                                                                               \
        if (vec) {                                                                                                     \
            ((size_t *) (vec))[-1] = (size);                                                                           \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define cvector_set_size(vec, size)                                                                                    \
    do {                                                                                                               \
        if (vec) {                                                                                                     \
            ((size_t *) (vec))[-2] = (size);                                                                           \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param count - the new capacity to set
 * @return void
 */
#define cvector_grow(vec, count)                                                                                       \
    do {                                                                                                               \
        const size_t cv_sz = (count) * sizeof(*(vec)) + (2 * sizeof(size_t));                                          \
        if (vec) {                                                                                                     \
            size_t * cv_p1 = ((size_t *) (vec)) - 2;                                                                   \
            size_t * cv_p2 = realloc(cv_p1, (cv_sz));                                                                  \
            assert(cv_p2);                                                                                             \
            (vec) = (void *) (cv_p2 + 2);                                                                              \
            cvector_set_capacity((vec), (count));                                                                      \
        } else {                                                                                                       \
            size_t * cv_p = malloc(cv_sz);                                                                             \
            assert(cv_p);                                                                                              \
            (vec) = (void *) (cv_p + 2);                                                                               \
            cvector_set_capacity((vec), (count));                                                                      \
            cvector_set_size((vec), 0);                                                                                \
        }                                                                                                              \
    } while (0)                                                                                                        \

#endif /* CVECTOR_H_ */
