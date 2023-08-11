/**
 @file max_heap.h
 @author Abigail Sanders
 @brief This code creates a templeted Maximum Heap class
 This file was written for Homework 1 for PIC10C, UCLA

 */


#ifndef max_heap_h
#define max_heap_h


#include <utility>
#include <vector>
#include <stdexcept>


namespace pic10c {
    /**
     @class max_heap creates a templeted data structure that maintains its largest element (as defined by a compare_type) at the top of the structure.
     @tparam T is the type of element being stored in the max_heap
     @tparam compare_type is the type of comparison operator used to sort elements
     */

    template<typename T, typename compare_type = std::less<T>>
    class max_heap {

    private:
        std::vector<T> values; //stores a vector as a member
        compare_type pred; //stores a comparison operator as a member

    public:

        /**
         constructor : default initializes the member values. Initializes member pred to the compare type if it is provided. If it is not provided, it is assigned by default
         @param compare_type_provided is the compare type that the user passes when creating a maximum heap, defaults to std::less<T>
         */
        max_heap(const compare_type& compare_type_provided = compare_type{}) noexcept : values{}, pred(compare_type_provided) {}

        /**
         insert function places a new r-value reference element into the maximum heap structure
         @param value is the element added to the structure
         */
        void insert(const T&& value)
        {
            using std::swap; //enable ADL
            values.push_back(std::move(value)); //move r-value into the vector
            size_t current_index = values.size() - 1; //get the size_t index of the last element

            //while loop, moves new element up the maximum heap while its not sorted correctly with respect to its parent. terminating condition: at the top or in correct order with parent
            while ((current_index != 0) && (!pred(values[current_index], values[((current_index - 1) / 2)])))
            {
                swap(values[current_index], values[(current_index - 1) / 2]); //if current element is in wrong order with its parent, swap their values
                current_index = (current_index - 1) / 2; //swap parent & child indices
            }
        }

        /**
         insert function places a new l-value  element into the maximum heap structure
         @param value is the element added to the structure
         */
        void insert(const T& value)
        {
            using std::swap; //enable ADL
            values.push_back(value); //insert l-value into vector
            size_t current_index = values.size() - 1; //get the size_t index of the last element

            //while loop, moves new element up the maximum heap while its not sorted correctly with respect to its parent. terminating condition: at the top or in correct order with parent
            while ((current_index != 0) && (!pred(values[current_index], values[((current_index - 1) / 2)])))
            {
                swap(values[current_index], values[(current_index - 1) / 2]); //if current element is in wrong order with its parent, swap their values
                current_index = (current_index - 1) / 2; //swap parent & child indices
            }
        }

        /**
         size function finds the size of the maximum heap structure
         @return the size of the underlying vector maintaining the maximum heap structure
         */
        size_t size() const
        {
            return(values.size()); //size of vector = size of maximum heap
        }

        /**
         top function returns the largest element in the maximum heap
         @return refernce to the largest element in heap
         */
        const T& top() const
        {
            if (size() == 0) //if size is 0, don't access anything
            {
                throw(std::logic_error("top empty")); //throw an exception
            }
            return(values[0]); //the top value, defined by the compare_type is at index 0
        }

        /**
         pop function removes the maximum element of the maximum heap (as defined by the compare_type). The function maintains the maximum heap strucutre after the top element is removed
         */
        void pop()
        {
            using std::swap; //enable ADL
            if (size() == 0) //if the maximum heap is empty, do not want to remove anything
            {
                throw(std::logic_error("pop empty")); //throw an exception that heap is empty
            }

            else if (size() == 1) //if the maximum heap is size 1, just remove that element
            {
                values.pop_back();
            }

            else //when max_heap.size() is 2 or greater
            {
                swap(values[0], values[(size() - 1)]); //swap the top element with the last element
                values.pop_back(); //remove that element from the max_heap (prior "largest" element as defined by compare_type)
                size_t current_index = 0;
                size_t left = 2 * current_index + 1; //left child index of current element
                size_t right = 2 * current_index + 2; //right child index of current element

                //demote the temporary element at the top of the max heap (current_index = 0) to its proper space in the structure. Move element down the tree while it is not sorted correctly with respect to its children. Terminating condition: element does not have a left child
                while (left < size())
                {
                    if (!(right < size())) //make sure to not access a right child that is out of range. This control flow is for when the left child is the last element of max_heap
                    {
                        if (pred(values[current_index], values[left])) //if the parent and left child are sorted incorrectly
                        {
                            swap(values[current_index], values[left]); //swap the values
                            current_index = left; //swap the current index
                        }
                        else //if the left child is sorted correctly, break out of loop
                        {
                            break;
                        }
                    }

                    else //when the right and left child indices are in range
                    {
                        if (( pred(values[current_index], values[left]) ) || ( pred(values[current_index], values[right]) )) //if the element at the current_index is sorted incorrectly with either child
                        {
                            if (pred(values[left], values[right])) //if the left child is less priority than the right
                            {
                                swap(values[right], values[current_index]); //swap right child with current element
                                current_index = right; //swap indices
                            }
                            else //if the left child is equal or more priority than the right
                            {
                                swap(values[left], values[current_index]); //swap the left child with the current element
                                current_index = left; //swap the indices
                            }

                        }
                        else //if the current_element is not less priority than either child, exit the while loop
                        {
                            break;
                        }
                    }

                    left = 2 * current_index + 1; //update index of left child
                    right = 2 * current_index + 2; //update index of right child
                }
            }

        }





    };






}
#endif
