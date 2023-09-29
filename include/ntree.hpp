#pragma once

#include <vector>

namespace forest
{
    template <typename T>
    class ntree
    {
    private:

        ntree<T>* parent_;
        std::vector<ntree<T>*> children_;
        T data_;

    public:

        class recursive_iterator
        {
        private:

            ntree<T>* root_;
            ntree<T>* current_;
            std::vector<size_t> current_i;

        public:

            recursive_iterator(ntree* node) : current_(node), root_(node)
            {
                current_i.push_back(0);
            }

            T& operator*()
            {
                return current_->data_;
            }

            bool operator==(const recursive_iterator& it)
            {
                return current_ == it.current_;
            }

            bool operator!=(const recursive_iterator& it)
            {
                return current_ != it.current_;
            }

            recursive_iterator& operator++()
            {
                if (current_->children_.size() == 0)
                {
                    for (int i = current_i.size() - 1; i >= 0; i--)
                    {
                        if (current_ != root_)
                        {
                            if (current_i[current_i.size() - 2] == current_->parent_->children_.size() - 1)
                            {
                                current_i.pop_back();
                                current_ = current_->parent_;
                            }
                        }
                        else
                        {
                            current_ = nullptr;
                            return *this;
                        }
                    }
                    current_i.pop_back();
                    current_i.back()++;
                    current_i.push_back(0);
                    auto b = current_i[current_i.size() - 2];
                    current_ = current_->parent_->children_[b];
                    return *this;
                }
                else
                {
                    current_i.push_back(0);
                    current_ = current_->children_[current_i.back()];
                    return *this;
                }
            }

            recursive_iterator& operator++(int)
            {
                auto tmp = this;
                this++;
                return tmp;
            }

            recursive_iterator& operator+(int count)
            {
                for (int i = 0; i < count; i++)
                {
                    operator++();
                }
                return *this;
            }
        };

        recursive_iterator begin()
        {
            return recursive_iterator{ this };
        }

        recursive_iterator end()
        {
            return recursive_iterator{ nullptr };
        }

        ntree(const T& data) 
        {
            data_ = data;
            parent_ = nullptr;
        }

        ntree() {}
        ~ntree() {}

        ntree& operator[](int i)
        {
            return *children_[i];
        }

        void add(const T& child_data)
        {
            auto child = new ntree{ child_data };
            child->parent_ = this;
            children_.push_back(child);
        }

        T& operator*()
        {
            return data_;
        }
    };
}